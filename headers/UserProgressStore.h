#pragma once

#include <filesystem>

class Gallery;
class User;

class UserProgressStore {
public:
    static std::filesystem::path defaultPath();
    static std::filesystem::path pathFromEnvironment();
    static void load(User& user, const Gallery& gallery, const std::filesystem::path& path);
    static void save(const User& user, const std::filesystem::path& path);
};
