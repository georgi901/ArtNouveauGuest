#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>
#include <filesystem>
#include <fstream>
#include <memory>
#include <string>

#include "../headers/ArtPuzzle.h"
#include "../headers/ArtQuiz.h"
#include "../headers/ArtisticDelight.h"
#include "../headers/Collection.h"
#include "../headers/Exceptions.h"
#include "../headers/Gallery.h"
#include "../headers/GameFactory.h"
#include "../headers/JsonDataLoader.h"
#include "../headers/QuickArtLook.h"
#include "../headers/User.h"
#include "../headers/UserProgressStore.h"

namespace {

std::shared_ptr<Artist> makeArtist() {
    return std::make_shared<Artist>("Mucha", "Alfons", "Czech", 79, 1860, 1939, "Art Nouveau");
}

std::shared_ptr<Painting> makePainting(const std::shared_ptr<Artist>& artist, bool rare = true) {
    return std::make_shared<Painting>(
        "Zodiac", "Lithography", 1896, rare, std::map<std::string, int>{{"red", 2}},
        std::map<std::string, int>{{"flat", 1}}, std::make_pair(65, 45), artist);
}

}  // namespace

TEST_CASE("Artist and gallery find related objects", "[domain]") {
    auto artist = makeArtist();
    auto painting = makePainting(artist);
    artist->addPainting(painting);

    Gallery gallery("Test Gallery", "Art Nouveau", 1895);
    gallery.addArtist(artist);
    gallery.addPainting(painting);

    REQUIRE(gallery.findArtist("Mucha") == artist);
    REQUIRE(gallery.findArtist("Alfons Mucha") == artist);
    REQUIRE(gallery.findPainting("Zodiac") == painting);
    REQUIRE(artist->findPainting("Zodiac") == painting);
    REQUIRE(artist->paintingCount() == 1);
    REQUIRE(painting->getArtist() == artist);
}

TEST_CASE("Collection supports add, find, filter, sort, and remove", "[collection]") {
    auto first = std::make_shared<Artist>("B", "Artist", "Test", 30, 1990, 0, "Modern");
    auto second = std::make_shared<Artist>("A", "Artist", "Test", 31, 1989, 0, "Modern");

    Collection<Artist> artists;
    artists.add(nullptr);
    artists.add(first);
    artists.add(second);

    REQUIRE(artists.size() == 2);
    REQUIRE(artists.findByPredicate([](const Artist& artist) { return artist.getName() == "A"; }) ==
            second);
    REQUIRE(artists.filter([](const Artist& artist) { return artist.getAge() > 30; }).size() == 1);

    artists.sort(
        [](const Artist& left, const Artist& right) { return left.getName() < right.getName(); });
    REQUIRE(artists.get(0) == second);
    REQUIRE(artists.remove(first));
    REQUIRE_FALSE(artists.remove(first));
    REQUIRE_THROWS_AS(artists.get(5), std::out_of_range);
}

TEST_CASE("User purchases paintings and enforces points and availability", "[user]") {
    auto painting = makePainting(makeArtist());
    User user("Visitor", "visitor", "visitor@example.com", 25, "2026-01-01");

    user.addPoints(100);
    user.buyPainting(painting, 40);

    REQUIRE(user.getPoints() == 60);
    REQUIRE(user.findPainting("Zodiac") == painting);
    REQUIRE(painting->isCollected());
    REQUIRE_THROWS_AS(user.buyPainting(painting, 10), PaintingUnavailableException);

    auto another_painting = makePainting(makeArtist(), false);
    REQUIRE_THROWS_AS(user.buyPainting(another_painting, 70), InsufficientPointsException);
}

TEST_CASE("Custom exceptions expose structured details", "[exceptions]") {
    InsufficientPointsException points_error(10, 35);
    REQUIRE(points_error.getAvailablePoints() == 10);
    REQUIRE(points_error.getRequiredPoints() == 35);
    REQUIRE(points_error.getMissingPoints() == 25);

    PaintingUnavailableException painting_error("Zodiac");
    REQUIRE(painting_error.getTitle() == "Zodiac");

    InvalidGameException game_error("Unknown");
    REQUIRE(game_error.getGameName() == "Unknown");

    DataLoadingException file_error("missing.json", "file");
    REQUIRE(file_error.getDetails() == "missing.json");
    REQUIRE(file_error.getErrorType() == "file");
    REQUIRE(std::string(file_error.what()).find("Cannot open file") != std::string::npos);
}

TEST_CASE("JsonDataLoader loads the bundled data", "[loader]") {
    Gallery gallery("Loaded Gallery", "Art Nouveau", 1895);

    JsonDataLoader::loadArtists(std::string(TEST_DATA_DIR) + "/artists.json", gallery);
    JsonDataLoader::loadPaintings(std::string(TEST_DATA_DIR) + "/paintings.json", gallery);
    auto user = JsonDataLoader::loadUser(std::string(TEST_DATA_DIR) + "/users.json");

    REQUIRE(gallery.getArtists().size() == 7);
    REQUIRE(gallery.getPaintings().size() == 8);
    REQUIRE(user);
}

TEST_CASE("JsonDataLoader reports missing files", "[loader]") {
    Gallery gallery;

    REQUIRE_THROWS_AS(
        JsonDataLoader::loadArtists(std::string(TEST_DATA_DIR) + "/missing.json", gallery),
        DataLoadingException);
}

TEST_CASE("UserProgressStore saves, loads, and recovers from a backup", "[persistence]") {
    const auto path =
        std::filesystem::temp_directory_path() / "art_nouveau_guest_progress_test.json";
    std::filesystem::remove(path);
    std::filesystem::remove(path.string() + ".bak");
    std::filesystem::remove(path.string() + ".tmp");

    auto artist = makeArtist();
    auto painting = makePainting(artist);
    Gallery gallery("Persistence Gallery", "Art Nouveau", 1895);
    gallery.addArtist(artist);
    gallery.addPainting(painting);

    User first("Visitor", "visitor", "visitor@example.com", 25, "2026-01-01");
    first.addPoints(75);
    first.addPainting(painting);
    UserProgressStore::save(first, path);

    User loaded("Visitor", "visitor", "visitor@example.com", 25, "2026-01-01");
    UserProgressStore::load(loaded, gallery, path);
    REQUIRE(loaded.getPoints() == 75);
    REQUIRE(loaded.findPainting("Zodiac") == painting);

    first.addPoints(10);
    UserProgressStore::save(first, path);
    {
        std::ofstream corrupted(path, std::ios::trunc);
        corrupted << "{ invalid json";
    }

    User recovered("Visitor", "visitor", "visitor@example.com", 25, "2026-01-01");
    UserProgressStore::load(recovered, gallery, path);
    REQUIRE(recovered.getPoints() == 75);

    std::filesystem::remove(path);
    std::filesystem::remove(path.string() + ".bak");
    std::filesystem::remove(path.string() + ".tmp");
}

TEST_CASE("Game factory creates all built-in games", "[factory]") {
    REQUIRE(GameFactory::isTypeRegistered("ArtisticDelight"));
    REQUIRE(GameFactory::isTypeRegistered("QuickArtLook"));
    REQUIRE(GameFactory::isTypeRegistered("ArtQuiz"));
    REQUIRE(GameFactory::isTypeRegistered("ArtPuzzle"));
    REQUIRE_FALSE(GameFactory::isTypeRegistered("Unknown"));

    auto game = GameFactory::createGame("ArtQuiz", Difficulty::Medium);
    REQUIRE(game);
    REQUIRE(game->getGameType() == "Art Quiz");
    REQUIRE(game->getDifficulty() == Difficulty::Medium);
    REQUIRE_THROWS_AS(GameFactory::createGame("Unknown", Difficulty::Easy), InvalidGameException);
}

TEST_CASE("QuickArtLook validates matching pairs", "[games]") {
    auto artist = makeArtist();
    auto painting = makePainting(artist);
    QuickArtLook game("Quick Art Look", Difficulty::Easy);

    game.addPair(painting, artist);
    REQUIRE(game.getTotalPairs() == 1);
    REQUIRE(game.verifyPair("Zodiac", "Mucha"));
    REQUIRE_FALSE(game.verifyPair("Zodiac", "Wrong Artist"));
    REQUIRE(game.getCorrectPairs() == 1);
    REQUIRE(game.getWrongPairs() == 1);
}

TEST_CASE("ArtisticDelight tracks colors and attempts", "[games]") {
    auto painting = makePainting(makeArtist());
    ArtisticDelight game("Artistic Delight", Difficulty::Easy);
    game.setPainting(painting);
    game.initialize();

    REQUIRE(game.getAttemptsRemaining() == 10);
    game.paint("red");

    REQUIRE(game.getAttemptsRemaining() == 9);
    REQUIRE(game.getUsedColors().size() == 1);
    REQUIRE(game.getSimilarityScore() == Catch::Approx(100.0));
}

TEST_CASE("ArtQuiz and ArtPuzzle expose stable difficulty contracts", "[games]") {
    auto artist = makeArtist();
    auto painting = makePainting(artist);

    ArtQuiz quiz("Art Quiz", Difficulty::Easy);
    quiz.addPainting(painting);
    quiz.initialize();
    REQUIRE(quiz.getRemainingQuestions() == 3);
    REQUIRE(quiz.hasRemainingQuestions());
    quiz.nextQuestion();
    REQUIRE(quiz.getRemainingQuestions() == 2);

    ArtPuzzle puzzle("Art Puzzle", Difficulty::Medium);
    REQUIRE(puzzle.getFragmentCount() == 9);
    REQUIRE(puzzle.getMovesMade() == 0);
    REQUIRE_FALSE(puzzle.moveFragment(-1, 0));
    REQUIRE_FALSE(puzzle.isSolved());
}
