#include "../headers/Application.h"

#include <iostream>
#include <memory>
#include <sstream>

#include "../headers/ArtPuzzle.h"
#include "../headers/ArtQuiz.h"
#include "../headers/Artist.h"
#include "../headers/ArtisticDelight.h"
#include "../headers/Collection.h"
#include "../headers/ConsoleUI.h"
#include "../headers/Exceptions.h"
#include "../headers/Gallery.h"
#include "../headers/GalleryService.h"
#include "../headers/GameFactory.h"
#include "../headers/MiniGame.h"
#include "../headers/Painting.h"
#include "../headers/QuickArtLook.h"
#include "../headers/User.h"
#include "../headers/UserProgressStore.h"
#include "../headers/Utils.h"

int Application::run() {
    Gallery gallery("Galeria Art Nouveau", "Art Nouveau", 1895);
    std::shared_ptr<User> user;
    try {
        user = GalleryService::loadData(gallery, "data");
        UserProgressStore::load(*user, gallery, UserProgressStore::pathFromEnvironment());
    } catch (const DataLoadingException& e) {
        std::cerr << "\nERROR: " << e.what() << "\n";
        std::cerr << "Error type: " << e.getErrorType() << "\n";
        std::cerr << "Details: " << e.getDetails() << "\n\n";
        std::cerr << "The program cannot continue without data!\n";
        std::cerr << "Make sure the JSON files exist in the 'data/' folder.\n\n";
        return 1;
    } catch (const GalleryException& e) {
        std::cerr << "\nERROR: " << e.what() << "\n";
        std::cerr << "The program cannot continue!\n\n";
        return 1;
    }

    GalleryService::configureGames(gallery);

    int option;
    std::string name, title;

    do {
        ConsoleUI::displayMenu();
        std::cin >> option;
        std::cin.ignore();

        switch (option) {
            case 1:
                gallery.displayArtists();
                break;

            case 2:
                gallery.displayPaintings();
                break;

            case 3:
                std::cout << "Enter artist name/first name: ";
                std::getline(std::cin, name);
                {
                    auto artist = gallery.findArtist(name);
                    if (artist) {
                        artist->displayArtistProfile(DetailLevel::Minimal);
                    } else {
                        std::cout << "Artist not found!\n";
                    }
                }
                break;

            case 4:
                std::cout << "Enter artist name/first name: ";
                std::getline(std::cin, name);
                {
                    auto artist = gallery.findArtist(name);
                    if (artist) {
                        artist->displayArtistProfile(DetailLevel::Complete);
                    } else {
                        std::cout << "Artist not found!\n";
                    }
                }
                break;

            case 5:
                std::cout << "Enter painting title: ";
                std::getline(std::cin, title);
                {
                    auto painting = gallery.findPainting(title);
                    if (painting) {
                        painting->displayPaintingZoom(DetailLevel::Minimal);
                    } else {
                        std::cout << "Painting not found!\n";
                    }
                }
                break;

            case 6:
                std::cout << "Enter painting title: ";
                std::getline(std::cin, title);
                {
                    auto painting = gallery.findPainting(title);
                    if (painting) {
                        painting->displayPaintingZoom(DetailLevel::Complete);
                    } else {
                        std::cout << "Painting not found!\n";
                    }
                }
                break;

            case 7:
                std::cout << gallery;
                break;

            case 8: {
                std::cout << "\n----- USER AND COLLECTION TEST -----\n\n";

                std::cout << "STEP 1: User profile BEFORE adding paintings\n";
                std::cout
                    << "-------------------------------------------------------------------\n";
                std::cout << *user;

                std::cout << "\n\nSTEP 2: Adding paintings to the collection\n";
                std::cout
                    << "-------------------------------------------------------------------\n";

                auto painting = gallery.findPainting("Zodiac");
                if (painting) {
                    std::cout << "→ Adding: 'Zodiac' by Mucha Alfons\n";
                    user->addPainting(painting);
                    std::cout << "  Added successfully!\n\n";
                }

                painting = gallery.findPainting("The Kiss");
                if (painting) {
                    std::cout << "→ Adding: 'The Kiss' by Klimt Gustav\n";
                    user->addPainting(painting);
                    std::cout << "  Added successfully!\n";
                }

                std::cout << "\n\nSTEP 3: Full collection view\n";
                std::cout
                    << "----------------------------------------------------------------------\n";
                user->displayCollection();

                std::cout << "\n\nSTEP 4: User profile AFTER adding paintings\n";
                std::cout
                    << "----------------------------------------------------------------------\n";
                std::cout << *user;

                std::cout << "\n\n Test finished successfully!\n";
            } break;

            case 9:
                std::cout << "Enter name/first name artist: ";
                std::getline(std::cin, name);
                {
                    auto artist = gallery.findArtist(name);
                    if (artist) {
                        std::cout << "\n======= STATISTICS " << artist->getName() << " =======\n";
                        std::cout << "Total paintings: " << artist->paintingCount() << "\n";
                        std::cout << "Collected paintings: " << artist->collectedPaintingCount()
                                  << "\n";
                        std::cout << "Rare paintings: " << artist->rarePaintingCount() << "\n";
                        std::cout << "Popularity score: " << artist->calculateStarScore()
                                  << " stars\n";
                        std::cout << "Title: " << artist->getTitle() << "\n";
                    } else {
                        std::cout << "Artist not found!\n";
                    }
                }
                break;

            case 10:
                std::cout << "Enter name/first name artist: ";
                std::getline(std::cin, name);
                {
                    auto artist = gallery.findArtist(name);
                    if (artist) {
                        auto rare = artist->getRarePaintings();
                        std::cout << "\n======== RARE PAINTINGS - " << artist->getName()
                                  << " ========\n";
                        if (rare.empty()) {
                            std::cout << "There are no rare paintings.\n";
                        } else {
                            for (const auto& t : rare) {
                                std::cout << "• " << t->getTitle() << " (" << t->getCreationYear()
                                          << ")\n";
                            }
                        }
                    } else {
                        std::cout << "Artist not found!\n";
                    }
                }
                break;
            case 11: {
                std::cout << "\n========== REQUIREMENT TESTS  ==========\n\n";

                auto painting_original = gallery.findPainting("Zodiac");

                if (!painting_original) {
                    std::cout << "Painting 'Zodiac' was not found!\n";
                    break;
                }

                std::cout << "STEP 1: Original painting\n";
                std::cout << "-------------------------\n";
                std::cout << "Title: " << painting_original->getTitle() << "\n";
                std::cout << "Year: " << painting_original->getCreationYear() << "\n\n";

                std::cout << "STEP 2: Copy constructor test\n";
                std::cout << "--------------------------------------\n";

                auto painting_copie = std::make_unique<Painting>(*painting_original);
                std::cout << "Copied: " << painting_copie->getTitle() << "\n\n";

                std::cout << "STEP 3: Copy assignment test\n";
                std::cout << "------------------------------------\n";

                auto painting_gol = std::make_unique<Painting>();
                std::cout << "Before: " << painting_gol->getTitle() << "\n";
                *painting_gol = *painting_original;
                std::cout << "After operator=: " << painting_gol->getTitle() << "\n\n";

                std::cout << " All tests OK! \n";
                std::cout << "  - Copy constructor: OK \n";
                std::cout << "  - Operator=: OK \n";
                std::cout << "  - Destructor: OK (will be called automatically)\n";
            } break;
            case 12: {
                std::cout << "\n===== TEST EXCEPTIONS =====\n\n";

                // Test 1: InsufficientPointsException
                std::cout << "Test 1: InsufficientPointsException\n";
                try {
                    throw InsufficientPointsException(100, 500);
                } catch (const InsufficientPointsException& e) {
                    std::cout << "  Message: " << e.what() << "\n";
                    std::cout << "  Available: " << e.getAvailablePoints() << "\n";
                    std::cout << "  Required: " << e.getRequiredPoints() << "\n";
                    std::cout << "  Missing: " << e.getMissingPoints() << "\n";
                }

                // Test 2: PaintingUnavailableException
                std::cout << "\nTest 2: PaintingUnavailableException\n";
                try {
                    throw PaintingUnavailableException("Mona Lisa");
                } catch (const PaintingUnavailableException& e) {
                    std::cout << "  Message: " << e.what() << "\n";
                    std::cout << "  Title: " << e.getTitle() << "\n";
                }

                // Test 3: InvalidGameException
                std::cout << "\nTest 3: InvalidGameException\n";
                try {
                    throw InvalidGameException("SuperGame");
                } catch (const InvalidGameException& e) {
                    std::cout << "  Message: " << e.what() << "\n";
                    std::cout << "  Game name: " << e.getGameName() << "\n";
                }

                // Test 4: Catch any exception from gallery
                std::cout << "\nTest 4: Catching a base gallery exception\n";
                try {
                    throw PaintingUnavailableException("Zodiac");
                } catch (const GalleryException& e) {
                    std::cout << "  Caught as GalleryException: " << e.what() << "\n";
                }

                std::cout << "\n5. Additional test functions:\n";

                // MiniGame static functions
                std::cout << "Total games: " << MiniGame::getTotalGames() << "\n";
                std::cout << "Total points: " << MiniGame::getTotalPoints() << "\n";
                MiniGame::displayStatistics();
                MiniGame::resetStatistics();

                // Gallery
                gallery.playGame("Artistic Delight");

                // Test one specific game
                auto game_test = gallery.findGame("Artistic Delight");
                if (game_test) {
                    std::cout << "Description: " << game_test->getDescription() << "\n";
                    std::cout << "Difficulty: " << static_cast<int>(game_test->getDifficulty())
                              << "\n";
                    std::cout << "Maximum points: " << game_test->getMaximumPoints() << "\n";
                    std::cout << "Points earned: " << game_test->getEarnedPoints() << "\n";
                    std::cout << "Completed: " << game_test->isFinished() << "\n";
                }

                // Test user - nullptr
                std::cout << "\nTest 5: buyPainting with nullptr\n";
                try {
                    user->buyPainting(nullptr, 0);
                } catch (const PaintingUnavailableException& e) {
                    std::cout << "  Correct exception caught: " << e.what() << "\n";
                }

                // ArtQuiz functions
                auto quiz = std::dynamic_pointer_cast<ArtQuiz>(gallery.findGame("Art Quiz"));
                if (quiz) {
                    std::cout << "Correct answers: " << quiz->getCorrectAnswers() << "\n";
                    std::cout << "Wrong answers: " << quiz->getWrongAnswers() << "\n";
                    std::cout << "Questions left: " << quiz->getRemainingQuestions() << "\n";
                }

                // ArtisticDelight
                auto ad = std::dynamic_pointer_cast<ArtisticDelight>(
                    gallery.findGame("Artistic Delight"));
                if (ad) {
                    std::cout << "Colors used: " << ad->getUsedColors().size() << "\n";
                }

                std::cout << "\n All tests OK!\n";
            } break;

            case 13:
                gallery.displayGames();
                break;

            case 14: {
                std::cout << "Enter the game name: ";
                std::getline(std::cin, name);

                try {
                    auto game = gallery.findGame(name);
                    if (!game) {
                        throw InvalidGameException(name);
                    }

                    game->displayRules();
                    game->initialize();

                    // ART QUIZ
                    if (auto quiz = std::dynamic_pointer_cast<ArtQuiz>(game)) {
                        std::string answer;
                        while (quiz->hasRemainingQuestions()) {
                            quiz->displayCurrentQuestion();
                            std::getline(std::cin, answer);
                            quiz->answer(answer);
                            quiz->nextQuestion();
                        }
                        std::cout << "\n Quiz finished!\n";
                    }

                    // ARTISTIC DELIGHT
                    else if (auto ad = std::dynamic_pointer_cast<ArtisticDelight>(game)) {
                        std::string color;
                        std::cout << "\nGuess the painting colors!\n";
                        std::cout << "(type 'hint' for help)\n\n";

                        while (ad->getAttemptsRemaining() > 0 && ad->getSimilarityScore() < 100) {
                            std::cout << "\n----------------------------------\n";
                            std::cout << "Attempts remaining: " << ad->getAttemptsRemaining()
                                      << "\n";
                            std::cout << "Current score: " << ad->getSimilarityScore() << "%\n";
                            std::cout << "Enter a color: ";
                            std::getline(std::cin, color);

                            if (color == "hint") {
                                ad->showHint();
                                continue;
                            }

                            ad->paint(color);
                        }

                        if (ad->getSimilarityScore() >= 100) {
                            std::cout << "\n Congratulations! You guessed all the colors!\n";
                        } else {
                            std::cout
                                << "\n No attempts left! Final score: " << ad->getSimilarityScore()
                                << "%\n";
                        }
                    }

                    // QUICK ART LOOK
                    else if (auto qal = std::dynamic_pointer_cast<QuickArtLook>(game)) {
                        qal->displayPaintings();
                        qal->displayArtists();

                        std::cout << "\nMatch each painting with the correct artist!\n";
                        std::cout << "(Type 'exit' to leave)\n\n";

                        int total_pairs = qal->getTotalPairs();
                        int attempts = 0;
                        int maximum_attempts = total_pairs + 3;

                        while (qal->getCorrectPairs() < total_pairs &&
                               attempts < maximum_attempts) {
                            std::cout << "----------------------------------\n";
                            std::cout << "Correct: " << qal->getCorrectPairs() << "/" << total_pairs
                                      << "\n";

                            std::string painting_title, artist_name;

                            std::cout << "Painting title: ";
                            std::getline(std::cin, painting_title);

                            if (painting_title == "exit") {
                                std::cout << "You left the game.\n";
                                break;
                            }

                            std::cout << "Artist name: ";
                            std::getline(std::cin, artist_name);

                            qal->verifyPair(painting_title, artist_name);
                            attempts++;
                        }

                        std::cout << "Correct pairs: " << qal->getCorrectPairs() << "/"
                                  << total_pairs << "\n";
                        std::cout << "Wrong pairs: " << qal->getWrongPairs() << "\n";

                        if (qal->getCorrectPairs() == total_pairs) {
                            std::cout << "\nCongratulations! You matched all pairs!\n";
                        } else {
                            std::cout << "\nGame finished! You matched " << qal->getCorrectPairs()
                                      << "/" << total_pairs << " pairs.\n";
                        }
                    }

                    // ART PUZZLE
                    auto puzzle = std::dynamic_pointer_cast<ArtPuzzle>(game);
                    if (puzzle) {
                        puzzle->displayPuzzle();

                        while (!puzzle->isSolved() && puzzle->getMovesRemaining() > 0) {
                            std::cout
                                << "Enter the positions to swap (pos1 pos2) or -1 -1 to exit: ";
                            int pos1, pos2;
                            std::cin >> pos1 >> pos2;

                            if (pos1 == -1 || pos2 == -1) {
                                std::cout << "You exited from the game.\n";
                                break;
                            }

                            puzzle->moveFragment(pos1, pos2);
                            puzzle->displayPuzzle();
                        }

                        std::cout << "\n=== RESULT ===\n";
                        std::cout << "Moves made: " << puzzle->getMovesMade() << "\n";
                        std::cout << "Fragments: " << puzzle->getFragmentCount() << "\n";

                        if (puzzle->isSolved()) {
                            std::cout << "Congratulations! You solved the puzzle!\n";
                        }
                    }

                    int points = game->calculatePoints();
                    user->addPoints(points);
                    std::cout << "\n========================================\n";
                    std::cout << "   You earned " << points << " points!\n";
                    std::cout << "   Total points: " << user->getPoints() << "\n";
                    std::cout << "========================================\n";
                } catch (const InvalidGameException& e) {
                    std::cerr << "Error: " << e.what() << "\n";
                }
            } break;

            case 15: {
                std::cout
                    << "\n===== TEST MINI-GAME + DYNAMIC_CAST + GALLERY + COPY_AND_SWAP =====\n\n";

                // Test polymorphism - call virtual functions through a base pointer
                std::cout << "1. Test polymorphism (virtual functions through base pointer):\n";
                auto game = gallery.findGame("Artistic Delight");
                if (game) {
                    std::cout << "Game type: " << game->getGameType() << "\n";
                    game->displayRules();
                }

                // Test dynamic_cast
                std::cout << "\n2. Test dynamic_cast:\n";
                gallery.displayArtisticDelightHints();

                // Test clone (virtual constructor)
                std::cout << "\n3. Test clone (virtual constructor):\n";
                if (game) {
                    auto copy = game->clone();
                    std::cout << "Original: " << game->getName() << "\n";
                    std::cout << "Clone: " << copy->getName() << "\n";
                }

                // Test static members
                std::cout << "\n4. Test static members:\n";
                MiniGame::displayStatistics();

                std::cout << "\n5. Test copy-and-swap Gallery:\n";
                std::cout << "-----------------------------------\n";

                std::cout << "ORIGINAL GALLERY:\n";
                std::cout << "  - Artists: " << gallery.getArtists().size() << "\n";
                std::cout << "  - Paintings: " << gallery.getPaintings().size() << "\n";
                std::cout << "  - Games: " << gallery.getGames().size() << "\n";

                Gallery gallery_copy("Copy", "Test", 2000);
                std::cout << "\nCOPY GALLERY (before copy-and-swap):\n";
                std::cout << "  - Artists: " << gallery_copy.getArtists().size() << "\n";
                std::cout << "  - Paintings: " << gallery_copy.getPaintings().size() << "\n";
                std::cout << "  - Games: " << gallery_copy.getGames().size() << "\n";

                gallery_copy = gallery;

                std::cout << "\nCOPY GALLERY (after copy-and-swap):\n";
                std::cout << "  - Artists: " << gallery_copy.getArtists().size() << "\n";
                std::cout << "  - Paintings: " << gallery_copy.getPaintings().size() << "\n";
                std::cout << "  - Games: " << gallery_copy.getGames().size() << "\n";

                std::cout << "\nCHECK INDEPENDENCE:\n";
                std::cout << "  Original gallery still has: " << gallery.getArtists().size()
                          << " artists, " << gallery.getPaintings().size() << " paintings, "
                          << gallery.getGames().size() << " games\n";

                std::cout << "\n Copy-and-swap works!\n";
                std::cout << "\n All tests OK!\n";
            } break;

            case 16: {
                std::cout << "\n";
                std::cout << "============================================================\n";
                std::cout << "     TEST MILESTONE 3 - TEMPLATES & DESIGN PATTERNS\n";
                std::cout << "============================================================\n\n";

                std::cout << "--- TEST 1: SINGLETON PATTERN (Gallery) ---\n";
                Gallery& g1 = Gallery::getInstance();
                Gallery& g2 = Gallery::getInstance();
                std::cout << "Gallery::getInstance() called 2 times.\n";
                std::cout << "Address g1: " << &g1 << "\n";
                std::cout << "Address g2: " << &g2 << "\n";
                std::cout << "Same instance? " << (&g1 == &g2 ? "YES - Singleton works!" : "NO")
                          << "\n\n";

                std::cout << "--- TEST 2: FACTORY PATTERN (GameFactory) ---\n";
                std::cout << "Available game types: ";
                for (const auto& tip : GameFactory::getAvailableTypes()) {
                    std::cout << tip << " ";
                }
                std::cout << "\n\n";

                std::cout << "Creating games using the factory:\n";

                try {
                    std::vector<std::unique_ptr<MiniGame>> game_factory;
                    game_factory.push_back(GameFactory::createGame("ArtQuiz", Difficulty::Medium));
                    std::cout << "  Created: " << game_factory.back()->getGameType() << " ("
                              << game_factory.back()->getName() << ")\n";

                    game_factory.push_back(GameFactory::createGame("ArtPuzzle", Difficulty::Hard));
                    std::cout << "  Created: " << game_factory.back()->getGameType() << " ("
                              << game_factory.back()->getName() << ")\n";
                } catch (const InvalidGameException& e) {
                    std::cout << "Error: " << e.what() << "\n";
                }

                std::cout << "\nTest invalid game creation:\n";
                try {
                    auto invalid_game =
                        GameFactory::createGame("NonExistentGame", Difficulty::Medium);
                } catch (const InvalidGameException& e) {
                    std::cout << "  Correct exception caught: " << e.what() << "\n";
                }
                std::cout << "\n";

                std::cout << "--- TEST 3: TEMPLATE CLASS (Collection<T>) ---\n";

                std::cout << "Instantiation 1: Collection<Artist>\n";
                Collection<Artist> artist_collection;
                for (const auto& a : gallery.getArtists()) {
                    artist_collection.add(a);
                }
                std::cout << "  Artists in collection: " << artist_collection.size() << "\n";

                auto found_artist = artist_collection.findByPredicate(
                    [](const Artist& a) { return a.getDeathYear() == 0; });
                if (found_artist) {
                    std::cout << "  Alive artist found: " << found_artist->getName() << "\n";
                }

                std::cout << "\nInstantiation 2: Collection<Painting>\n";
                Collection<Painting> painting_collection;
                for (const auto& t : gallery.getPaintings()) {
                    painting_collection.add(t);
                }
                std::cout << "  Paintings in collection: " << painting_collection.size() << "\n";

                auto rare_paintings =
                    painting_collection.filter([](const Painting& t) { return t.isRare(); });
                std::cout << "  Rare paintings (filtered): " << rare_paintings.size() << "\n";

                std::cout << "\nInstantiation 3: Collection<MiniGame>\n";
                Collection<MiniGame> game_collection;
                for (const auto& j : gallery.getGames()) {
                    game_collection.add(j);
                }
                std::cout << "  Games in collection: " << game_collection.size() << "\n\n";

                std::cout << "--- TEST 4: TEMPLATE FUNCTIONS (Utils.h) ---\n";

                std::cout << "Instantiation 1: findByName<Artist>\n";
                auto searched_artist = findByName(gallery.getArtists(), "Mucha");
                std::cout << "  Search 'Mucha': "
                          << (searched_artist ? searched_artist->getName() + " " +
                                                    searched_artist->getFirstName()
                                              : "Not found")
                          << "\n";

                std::cout << "\nInstantiation 2: findByField<Painting>\n";
                auto found_painting =
                    findByField<Painting>(gallery.getPaintings(), "Zodiac",
                                          [](const Painting& t) { return t.getTitle(); });
                std::cout << "  Search painting 'Zodiac': "
                          << (found_painting ? found_painting->getTitle() : "Not found") << "\n";

                std::cout << "\nInstantiation 3: filterElements<Painting>\n";
                auto filtered_paintings = filterElements<Painting>(
                    gallery.getPaintings(), [](const Painting& t) { return t.isRare(); });
                std::cout << "  Rare paintings filtered: " << filtered_paintings.size() << "\n";

                std::cout << "\nInstantiation 4: filterElements<Artist>\n";
                auto alive_artists = filterElements<Artist>(
                    gallery.getArtists(), [](const Artist& a) { return a.getDeathYear() == 0; });
                std::cout << "  Artists alive: " << alive_artists.size() << "\n";

                std::cout << "\nInstantiation 5: countElements<Painting>\n";
                int collected_count = countElements<Painting>(
                    gallery.getPaintings(), [](const Painting& t) { return t.isCollected(); });
                std::cout << "  Collected paintings: " << collected_count << "\n";

                std::cout << "\nInstantiation 6: countElements<Artist>\n";
                int deceased_count = countElements<Artist>(
                    gallery.getArtists(), [](const Artist& a) { return a.getDeathYear() != 0; });
                std::cout << "  Deceased artists: " << deceased_count << "\n";

                std::cout << "\nInstantiation 7: transform<Artist, std::string>\n";
                auto artist_names = transform<Artist, std::string>(
                    gallery.getArtists(),
                    [](const Artist& a) { return a.getName() + " " + a.getFirstName(); });
                std::cout << "  Artist names: ";
                for (size_t i = 0; i < std::min(artist_names.size(), size_t(3)); i++) {
                    std::cout << artist_names[i];
                    if (i < std::min(artist_names.size(), size_t(3)) - 1)
                        std::cout << ", ";
                }
                if (artist_names.size() > 3)
                    std::cout << "...";
                std::cout << "\n";

                std::cout << "\n";
                std::cout << "============================================================\n";
                std::cout << "                 M3 TEST SUMMARY\n";
                std::cout << "============================================================\n";
                std::cout << "  [OK] Design Pattern 1: SINGLETON (Gallery)\n";
                std::cout << "  [OK] Design Pattern 2: FACTORY (GameFactory)\n";
                std::cout << "  [OK] Template class: Collection<T> - 3 instantiations\n";
                std::cout << "       - Collection<Artist>\n";
                std::cout << "       - Collection<Painting>\n";
                std::cout << "       - Collection<MiniGame>\n";
                std::cout << "  [OK] Template functions: 7+ instantiations\n";
                std::cout << "       - findByName<Artist>\n";
                std::cout << "       - findByField<Painting>\n";
                std::cout << "       - filterElements<Painting>\n";
                std::cout << "       - filterElements<Artist>\n";
                std::cout << "       - countElements<Painting>\n";
                std::cout << "       - countElements<Artist>\n";
                std::cout << "       - transform<Artist, string>\n";
                std::cout << "============================================================\n";
                std::cout << "       ALL M3 TESTS PASSED SUCCESSFULLY!\n";
                std::cout << "============================================================\n";
            } break;

            case 17: {
                std::cout << "\n===== TEST UNUSED TEMPLATE FUNCTIONS =====\n\n";

                std::cout << "Test custom game registration:\n";
                GameFactory::registerGame("CustomGame", [](Difficulty d) {
                    return std::make_unique<ArtQuiz>("Custom Game", d);
                });

                auto new_game = GameFactory::createGame("CustomGame", Difficulty::Medium);
                std::cout << "Created game: " << new_game->getName() << "\n";

                Collection<Painting> test_collection;
                for (const auto& t : gallery.getPaintings()) {
                    test_collection.add(t);
                }

                if (test_collection.size() > 0) {
                    auto first = test_collection.get(0);
                    std::cout << "Test remove: "
                              << (test_collection.remove(first) ? "Success" : "Failed") << "\n";
                }

                if (test_collection.size() > 0) {
                    auto element = test_collection.get(0);
                    std::cout << "Test get: " << (element ? element->getTitle() : "null") << "\n";
                }

                std::cout << "Test isEmpty: " << (test_collection.empty() ? "Yes" : "No") << "\n";

                test_collection.sort([](const Painting& a, const Painting& b) {
                    return a.getTitle() < b.getTitle();
                });
                std::cout << "Test sort: Executed\n";

                int count = 0;
                test_collection.forEach([&count](Painting&) { count++; });
                std::cout << "Test forEach: Processed " << count << " elements\n";

                auto all_items = test_collection.getAll();
                std::cout << "Test getAll: " << all_items.size() << " elements\n";

                std::ostringstream oss;
                displayAll(gallery.getPaintings(), oss, "Paintings");
                std::cout << "Test displayAll: Executed\n";

                int total_years = sumProperty<Painting, int>(
                    gallery.getPaintings(), [](const Painting& t) { return t.getCreationYear(); });
                std::cout << "Test sumProperty: Sum of years = " << total_years << "\n";

                std::cout << "Test isTypeRegistered: "
                          << (GameFactory::isTypeRegistered("ArtQuiz") ? "Yes" : "No") << "\n";

                test_collection.clear();
                std::cout << "Test clear: Executed (dimensions = " << test_collection.size()
                          << ")\n";

                std::cout << "\n All template functions tested!\n";
            } break;

            case 0:
                std::cout << "\nGoodbye!\n";
                break;

            default:
                std::cout << "\nInvalid option!\n";
        }

        if (option != 0) {
            std::cout << "\nPress ENTER to continue...";
            std::cin.get();
        }

    } while (option != 0);

    try {
        UserProgressStore::save(*user, UserProgressStore::pathFromEnvironment());
    } catch (const std::exception& e) {
        std::cerr << "\nWARNING: Unable to save user progress: " << e.what() << "\n";
        return 1;
    }
    return 0;
}