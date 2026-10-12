#pragma once

#include <memory>
#include <string>

class Gallery;
class User;

class GalleryService {
public:
    static std::shared_ptr<User> loadData(Gallery& gallery, const std::string& data_directory);
    static void configureGames(Gallery& gallery);
};
