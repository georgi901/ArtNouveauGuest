#include "../headers/UserProgressStore.h"

#include <cstdlib>
#include <fstream>
#include <nlohmann/json.hpp>
#include <stdexcept>

#include "../headers/Gallery.h"
#include "../headers/Painting.h"
#include "../headers/User.h"

namespace {

using json = nlohmann::json;
constexpr int current_schema_version = 1;

json readProgress(const std::filesystem::path& path) {
    std::ifstream input(path);
    if (!input.is_open()) {
        throw std::runtime_error("Unable to open progress file");
    }

    try {
        json data;
        input >> data;
        return data;
    } catch (const json::exception&) {
        throw std::runtime_error("Invalid progress JSON");
    }
}

void applyProgress(const json& data, User& user, const Gallery& gallery) {
    if (data.at("schema_version").get<int>() != current_schema_version) {
        throw std::runtime_error("Unsupported progress schema version");
    }

    const int points = data.at("points").get<int>();
    if (points < 0) {
        throw std::runtime_error("Progress points cannot be negative");
    }
    user.addPoints(points);

    for (const auto& title : data.at("collection")) {
        const auto painting = gallery.findPainting(title.get<std::string>());
        if (painting && !user.findPainting(painting->getTitle())) {
            user.addPainting(painting);
        }
    }
}

}  // namespace

std::filesystem::path UserProgressStore::defaultPath() {
#ifdef _WIN32
    if (const char* app_data = std::getenv("APPDATA")) {
        return std::filesystem::path(app_data) / "ArtNouveauGuest" / "user-progress.json";
    }
#elif __APPLE__
    if (const char* home = std::getenv("HOME")) {
        return std::filesystem::path(home) / "Library" / "Application Support" / "ArtNouveauGuest" /
               "user-progress.json";
    }
#else
    if (const char* xdg_data_home = std::getenv("XDG_DATA_HOME")) {
        return std::filesystem::path(xdg_data_home) / "ArtNouveauGuest" / "user-progress.json";
    }
    if (const char* home = std::getenv("HOME")) {
        return std::filesystem::path(home) / ".local" / "share" / "ArtNouveauGuest" /
               "user-progress.json";
    }
#endif
    return std::filesystem::path("user-progress.json");
}

std::filesystem::path UserProgressStore::pathFromEnvironment() {
    if (const char* override_path = std::getenv("ARTNOUVEAU_SAVE_PATH")) {
        if (*override_path != '\0') {
            return override_path;
        }
    }
    return defaultPath();
}

void UserProgressStore::load(User& user, const Gallery& gallery,
                             const std::filesystem::path& path) {
    if (!std::filesystem::exists(path)) {
        return;
    }

    try {
        applyProgress(readProgress(path), user, gallery);
        return;
    } catch (const std::exception&) {
        const auto backup = path.string() + ".bak";
        if (!std::filesystem::exists(backup)) {
            throw;
        }
        applyProgress(readProgress(backup), user, gallery);
    }
}

void UserProgressStore::save(const User& user, const std::filesystem::path& path) {
    const auto parent = path.parent_path();
    if (!parent.empty()) {
        std::filesystem::create_directories(parent);
    }

    json data{
        {"schema_version", current_schema_version},
        {"points", user.getPoints()},
        {"collection", json::array()},
    };
    for (const auto& painting : user.getCollection()) {
        if (painting) {
            data["collection"].push_back(painting->getTitle());
        }
    }

    const auto temporary = path.string() + ".tmp";
    {
        std::ofstream output(temporary, std::ios::trunc);
        if (!output.is_open()) {
            throw std::runtime_error("Unable to create temporary progress file");
        }
        output << data.dump(2) << '\n';
        if (!output) {
            throw std::runtime_error("Unable to write progress file");
        }
    }

    const auto backup = path.string() + ".bak";
    if (std::filesystem::exists(path)) {
        std::filesystem::copy_file(path, backup, std::filesystem::copy_options::overwrite_existing);
    }
    std::filesystem::rename(temporary, path);
}
