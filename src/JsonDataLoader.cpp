#include "../headers/JsonDataLoader.h"

#include <fstream>
#include <map>
#include <nlohmann/json.hpp>
#include <vector>

#include "../headers/Artist.h"
#include "../headers/Exceptions.h"
#include "../headers/Gallery.h"
#include "../headers/Painting.h"
#include "../headers/User.h"

namespace {

using json = nlohmann::json;

json readJsonFile(const std::string& file_path) {
    std::ifstream input(file_path);
    if (!input.is_open()) {
        throw DataLoadingException(file_path, "file");
    }

    try {
        json data;
        input >> data;
        return data;
    } catch (const json::exception&) {
        throw DataLoadingException(file_path, "parse");
    }
}

}  // namespace

void JsonDataLoader::loadArtists(const std::string& file_path, Gallery& gallery) {
    const auto data = readJsonFile(file_path);

    try {
        for (const auto& artist_json : data) {
            auto artist = std::make_shared<Artist>(
                artist_json.at("name").get<std::string>(),
                artist_json.at("first_name").get<std::string>(),
                artist_json.at("nationality").get<std::string>(),
                artist_json.at("age").get<int>(), artist_json.at("birth_year").get<int>(),
                artist_json.at("death_year").get<int>(), artist_json.at("period").get<std::string>(),
                artist_json.at("registration_date").get<std::string>(),
                artist_json.value("username", ""), artist_json.value("email", ""),
                std::vector<std::string>{},
                artist_json.contains("representative")
                    ? artist_json.at("representative").value("name", "")
                    : "",
                artist_json.contains("representative")
                    ? artist_json.at("representative").value("username", "")
                    : "",
                artist_json.contains("representative")
                    ? artist_json.at("representative").value("email", "")
                    : "",
                std::vector<std::string>{});

            if (artist_json.contains("images")) {
                for (const auto& image : artist_json.at("images")) {
                    artist->addImage(image.get<std::string>());
                }
            }

            gallery.addArtist(artist);
        }
    } catch (const json::exception&) {
        throw DataLoadingException(file_path, "parse");
    }
}

void JsonDataLoader::loadPaintings(const std::string& file_path, Gallery& gallery) {
    const auto data = readJsonFile(file_path);

    try {
        for (const auto& painting_json : data) {
            std::map<std::string, int> colors;
            if (painting_json.contains("colors")) {
                for (const auto& [key, value] : painting_json.at("colors").items()) {
                    colors[key] = value.get<int>();
                }
            }

            std::map<std::string, int> brushes;
            if (painting_json.contains("brushes")) {
                for (const auto& [key, value] : painting_json.at("brushes").items()) {
                    brushes[key] = value.get<int>();
                }
            }

            const auto& dimensions = painting_json.at("dimensions");
            auto artist = gallery.findArtist(painting_json.at("artist").get<std::string>());
            auto painting = std::make_shared<Painting>(
                painting_json.at("title").get<std::string>(),
                painting_json.at("technique").get<std::string>(),
                painting_json.at("creation_year").get<int>(), painting_json.at("rare").get<bool>(),
                colors, brushes,
                std::make_pair(dimensions.at(0).get<int>(), dimensions.at(1).get<int>()), artist,
                painting_json.value("collected", false));

            if (painting_json.contains("images")) {
                for (const auto& image : painting_json.at("images")) {
                    painting->addImage(image.get<std::string>());
                }
            }

            gallery.addPainting(painting);
            if (artist) {
                artist->addPainting(painting);
            }
        }
    } catch (const json::exception&) {
        throw DataLoadingException(file_path, "parse");
    }
}

std::shared_ptr<User> JsonDataLoader::loadUser(const std::string& file_path) {
    const auto data = readJsonFile(file_path);

    try {
        if (!data.is_array() || data.empty()) {
            throw DataLoadingException(file_path, "parse");
        }

        const auto& user_json = data.at(0);
        return std::make_shared<User>(
            user_json.at("name").get<std::string>(),
            user_json.at("username").get<std::string>(),
            user_json.at("email").get<std::string>(), user_json.at("age").get<int>(),
            user_json.at("registration_date").get<std::string>());
    } catch (const DataLoadingException&) {
        throw;
    } catch (const json::exception&) {
        throw DataLoadingException(file_path, "parse");
    }
}
