#pragma once

#include <memory>
#include <string>

class Gallery;
class User;

class JsonDataLoader {
public:
    static void loadArtists(const std::string& file_path, Gallery& gallery);
    static void loadPaintings(const std::string& file_path, Gallery& gallery);
    static std::shared_ptr<User> loadUser(const std::string& file_path);
};
