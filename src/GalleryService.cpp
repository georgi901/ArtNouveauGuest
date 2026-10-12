#include "../headers/GalleryService.h"

#include <iostream>
#include <memory>

#include "../headers/ArtPuzzle.h"
#include "../headers/ArtQuiz.h"
#include "../headers/ArtisticDelight.h"
#include "../headers/Gallery.h"
#include "../headers/JsonDataLoader.h"
#include "../headers/QuickArtLook.h"
#include "../headers/User.h"

std::shared_ptr<User> GalleryService::loadData(Gallery& gallery,
                                               const std::string& data_directory) {
    std::cout << "\n========================================\n";
    std::cout << "  LOADING DATA FROM JSON FILES\n";
    std::cout << "========================================\n";

    std::cout << "→ Loading artists from 'artists.json'...\n";
    JsonDataLoader::loadArtists(data_directory + "/artists.json", gallery);
    std::cout << "    Artists loaded successfully!\n\n";

    std::cout << "→ Loading paintings from 'paintings.json'...\n";
    JsonDataLoader::loadPaintings(data_directory + "/paintings.json", gallery);
    std::cout << "    Paintings loaded successfully!\n\n";

    std::cout << "→ Loading user from 'users.json'...\n";
    auto user = JsonDataLoader::loadUser(data_directory + "/users.json");
    std::cout << "    User loaded successfully!\n";

    std::cout << "========================================\n";
    std::cout << "    ALL DATA LOADED\n";
    std::cout << "========================================\n";
    return user;
}

void GalleryService::configureGames(Gallery& gallery) {
    auto artistic_delight_game =
        std::make_shared<ArtisticDelight>("Artistic Delight", Difficulty::Medium);
    if (auto zodiac_painting = gallery.findPainting("Zodiac")) {
        artistic_delight_game->setPainting(zodiac_painting);
    }
    gallery.addGame(artistic_delight_game);

    auto quick_art_look_game = std::make_shared<QuickArtLook>("Quick Art Look", Difficulty::Easy);
    for (const auto& painting : gallery.getPaintings()) {
        if (auto artist = painting->getArtist()) {
            quick_art_look_game->addPair(painting, artist);
        }
    }
    gallery.addGame(quick_art_look_game);

    auto art_quiz_game = std::make_shared<ArtQuiz>("Art Quiz", Difficulty::Hard);
    for (const auto& painting : gallery.getPaintings()) {
        art_quiz_game->addPainting(painting);
    }
    gallery.addGame(art_quiz_game);

    auto art_puzzle_game = std::make_shared<ArtPuzzle>("Art Puzzle", Difficulty::Easy);
    art_puzzle_game->setPainting(gallery.findPainting("The Kiss"));
    gallery.addGame(art_puzzle_game);

    std::cout << " Games created successfully!\n";
}
