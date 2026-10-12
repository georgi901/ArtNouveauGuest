#include "../headers/SfmlApplication.h"

#include <SFML/Graphics.hpp>
#include <algorithm>
#include <array>
#include <filesystem>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "../headers/ArtPuzzle.h"
#include "../headers/ArtQuiz.h"
#include "../headers/ArtisticDelight.h"
#include "../headers/Exceptions.h"
#include "../headers/Gallery.h"
#include "../headers/GalleryService.h"
#include "../headers/Painting.h"
#include "../headers/QuickArtLook.h"
#include "../headers/User.h"
#include "../headers/UserProgressStore.h"

namespace {

constexpr float logical_width = 1280.0F;
constexpr float logical_height = 720.0F;

enum class Screen {
    Menu,
    Gallery,
    Details,
    Collection,
    QuickArtLook,
    ArtQuiz,
    ArtisticDelight,
    ArtPuzzle
};

bool loadFont(sf::Font& font) {
    const std::array<std::filesystem::path, 4> candidates{
        std::filesystem::path("assets/fonts/DejaVuSans.ttf"),
        std::filesystem::path("assets/fonts/Roboto-Regular.ttf"),
        std::filesystem::path("/System/Library/Fonts/Supplemental/Arial.ttf"),
        std::filesystem::path("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf"),
    };

    for (const auto& candidate : candidates) {
        if (std::filesystem::exists(candidate) && font.loadFromFile(candidate.string())) {
            return true;
        }
    }
    return false;
}

void drawText(sf::RenderWindow& window, const sf::Font& font, const std::string& content, float x,
              float y, unsigned int size, sf::Color color = sf::Color::White) {
    sf::Text text(content, font, size);
    text.setPosition(x, y);
    text.setFillColor(color);
    window.draw(text);
}

void drawPanel(sf::RenderWindow& window, sf::Vector2f position, sf::Vector2f size,
               sf::Color color) {
    sf::RectangleShape panel(size);
    panel.setPosition(position);
    panel.setFillColor(color);
    window.draw(panel);
}

std::string artistName(const std::shared_ptr<Painting>& painting) {
    const auto artist = painting->getArtist();
    return artist ? artist->getName() + " " + artist->getFirstName() : "Unknown artist";
}

void updateView(sf::RenderWindow& window, sf::View& view) {
    const auto window_size = window.getSize();
    if (window_size.x == 0 || window_size.y == 0) {
        return;
    }

    const float window_ratio =
        static_cast<float>(window_size.x) / static_cast<float>(window_size.y);
    const float logical_ratio = logical_width / logical_height;
    float viewport_width = 1.0F;
    float viewport_height = 1.0F;
    float viewport_left = 0.0F;
    float viewport_top = 0.0F;

    if (window_ratio > logical_ratio) {
        viewport_width = logical_ratio / window_ratio;
        viewport_left = (1.0F - viewport_width) / 2.0F;
    } else if (window_ratio < logical_ratio) {
        viewport_height = window_ratio / logical_ratio;
        viewport_top = (1.0F - viewport_height) / 2.0F;
    }

    view.setViewport({viewport_left, viewport_top, viewport_width, viewport_height});
}

}  // namespace

int SfmlApplication::run() {
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Art Nouveau Guest");
    window.setVerticalSyncEnabled(true);

    sf::View view(sf::Vector2f(logical_width / 2.0F, logical_height / 2.0F),
                  sf::Vector2f(logical_width, logical_height));
    updateView(window, view);

    Gallery gallery("Art Nouveau Gallery", "Art Nouveau", 1895);
    std::shared_ptr<User> user;
    try {
        user = GalleryService::loadData(gallery, "data");
        UserProgressStore::load(*user, gallery, UserProgressStore::pathFromEnvironment());
        GalleryService::configureGames(gallery);
    } catch (const GalleryException& exception) {
        std::cerr << "Unable to initialize the graphical application: " << exception.what() << '\n';
        return 1;
    } catch (const std::exception& exception) {
        std::cerr << "Unable to initialize the graphical application: " << exception.what() << '\n';
        return 1;
    }

    sf::Font font;
    const bool has_font = loadFont(font);
    Screen screen = Screen::Menu;
    std::size_t selected_index = 0;
    std::shared_ptr<Painting> selected_painting;
    std::shared_ptr<QuickArtLook> quick_art_look;
    std::size_t selected_artist = 0;
    std::string game_feedback;
    std::string quiz_input;
    std::string color_input;
    int puzzle_first = 0;
    int puzzle_second = 1;
    const std::vector<std::string> menu_items{"Gallery",  "Collection",       "Quick Art Look",
                                              "Art Quiz", "Artistic Delight", "Art Puzzle",
                                              "Exit"};

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::Resized) {
                window.setView(view);
                updateView(window, view);
            } else if (event.type == sf::Event::TextEntered &&
                       (screen == Screen::ArtQuiz || screen == Screen::ArtisticDelight)) {
                auto& input = screen == Screen::ArtQuiz ? quiz_input : color_input;
                if (input.size() < 80 && event.text.unicode >= 32 && event.text.unicode < 127) {
                    input += static_cast<char>(event.text.unicode);
                }
            } else if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape) {
                    if (screen == Screen::Menu) {
                        window.close();
                    } else {
                        screen = Screen::Menu;
                        selected_index = 0;
                    }
                } else if (event.key.code == sf::Keyboard::Up ||
                           event.key.code == sf::Keyboard::Down) {
                    if (screen == Screen::ArtPuzzle) {
                        auto puzzle =
                            std::dynamic_pointer_cast<ArtPuzzle>(gallery.findGame("Art Puzzle"));
                        if (puzzle && puzzle->getFragmentCount() > 0) {
                            const auto count = puzzle->getFragmentCount();
                            puzzle_first = event.key.code == sf::Keyboard::Up
                                               ? (puzzle_first + count - 1) % count
                                               : (puzzle_first + 1) % count;
                        }
                        continue;
                    }
                    const auto item_count =
                        screen == Screen::Menu         ? menu_items.size()
                        : screen == Screen::Gallery    ? gallery.getPaintings().size()
                        : screen == Screen::Collection ? user->getCollection().size()
                        : screen == Screen::QuickArtLook && quick_art_look
                            ? static_cast<std::size_t>(quick_art_look->getTotalPairs())
                            : 0;
                    if (item_count > 0) {
                        selected_index = event.key.code == sf::Keyboard::Up
                                             ? (selected_index + item_count - 1) % item_count
                                             : (selected_index + 1) % item_count;
                    }
                } else if (event.key.code == sf::Keyboard::Enter) {
                    if (screen == Screen::Menu) {
                        if (selected_index == 0) {
                            screen = Screen::Gallery;
                            selected_index = 0;
                        } else if (selected_index == 1) {
                            screen = Screen::Collection;
                            selected_index = 0;
                        } else if (selected_index == 2) {
                            quick_art_look = std::dynamic_pointer_cast<QuickArtLook>(
                                gallery.findGame("Quick Art Look"));
                            if (quick_art_look) {
                                quick_art_look->initialize();
                                selected_index = 0;
                                selected_artist = 0;
                                game_feedback.clear();
                                screen = Screen::QuickArtLook;
                            }
                        } else if (selected_index == 3) {
                            auto quiz =
                                std::dynamic_pointer_cast<ArtQuiz>(gallery.findGame("Art Quiz"));
                            if (quiz) {
                                quiz->initialize();
                                quiz_input.clear();
                                game_feedback.clear();
                                screen = Screen::ArtQuiz;
                            }
                        } else if (selected_index == 4) {
                            auto delight = std::dynamic_pointer_cast<ArtisticDelight>(
                                gallery.findGame("Artistic Delight"));
                            if (delight) {
                                delight->initialize();
                                color_input.clear();
                                game_feedback.clear();
                                screen = Screen::ArtisticDelight;
                            }
                        } else if (selected_index == 5) {
                            auto puzzle = std::dynamic_pointer_cast<ArtPuzzle>(
                                gallery.findGame("Art Puzzle"));
                            if (puzzle) {
                                puzzle->initialize();
                                puzzle_first = 0;
                                puzzle_second = 1;
                                game_feedback.clear();
                                screen = Screen::ArtPuzzle;
                            }
                        } else {
                            window.close();
                        }
                    } else if (screen == Screen::Gallery && !gallery.getPaintings().empty()) {
                        selected_painting = gallery.getPaintings()[selected_index];
                        screen = Screen::Details;
                    } else if (screen == Screen::QuickArtLook && quick_art_look) {
                        const auto painting_index = static_cast<int>(selected_index);
                        const auto correct = quick_art_look->verifyPair(
                            quick_art_look->getPaintingTitle(painting_index),
                            quick_art_look->getArtistName(static_cast<int>(selected_artist)));
                        game_feedback = correct ? "Correct match!" : "Not a match.";
                    } else if (screen == Screen::ArtQuiz) {
                        auto quiz =
                            std::dynamic_pointer_cast<ArtQuiz>(gallery.findGame("Art Quiz"));
                        if (quiz && quiz->hasRemainingQuestions()) {
                            const bool correct = quiz->answer(quiz_input);
                            game_feedback = correct ? "Correct answer!" : "Incorrect answer.";
                            quiz->nextQuestion();
                            quiz_input.clear();
                        }
                    } else if (screen == Screen::ArtisticDelight) {
                        auto delight = std::dynamic_pointer_cast<ArtisticDelight>(
                            gallery.findGame("Artistic Delight"));
                        if (delight && !color_input.empty() &&
                            delight->getAttemptsRemaining() > 0) {
                            delight->paint(color_input);
                            game_feedback = delight->getSimilarityScore() >= 100.0
                                                ? "All colors found!"
                                                : "Color recorded.";
                            color_input.clear();
                        }
                    } else if (screen == Screen::ArtPuzzle) {
                        auto puzzle =
                            std::dynamic_pointer_cast<ArtPuzzle>(gallery.findGame("Art Puzzle"));
                        if (puzzle) {
                            game_feedback = puzzle->moveFragment(puzzle_first, puzzle_second)
                                                ? "Fragments swapped."
                                                : "Invalid move.";
                        }
                    }
                } else if (screen == Screen::ArtQuiz && event.key.code == sf::Keyboard::BackSpace &&
                           !quiz_input.empty()) {
                    quiz_input.pop_back();
                } else if (screen == Screen::ArtisticDelight &&
                           event.key.code == sf::Keyboard::BackSpace && !color_input.empty()) {
                    color_input.pop_back();
                } else if (screen == Screen::ArtisticDelight && event.key.code == sf::Keyboard::H) {
                    auto delight = std::dynamic_pointer_cast<ArtisticDelight>(
                        gallery.findGame("Artistic Delight"));
                    if (delight) {
                        delight->showHint();
                        game_feedback = "Hint printed to the console.";
                    }
                } else if (screen == Screen::ArtPuzzle) {
                    auto puzzle =
                        std::dynamic_pointer_cast<ArtPuzzle>(gallery.findGame("Art Puzzle"));
                    if (puzzle) {
                        const auto count = puzzle->getFragmentCount();
                        if (count > 0 && event.key.code == sf::Keyboard::Up) {
                            puzzle_first = (puzzle_first + count - 1) % count;
                        } else if (count > 0 && event.key.code == sf::Keyboard::Down) {
                            puzzle_first = (puzzle_first + 1) % count;
                        } else if (count > 0 && event.key.code == sf::Keyboard::Left) {
                            puzzle_second = (puzzle_second + count - 1) % count;
                        } else if (count > 0 && event.key.code == sf::Keyboard::Right) {
                            puzzle_second = (puzzle_second + 1) % count;
                        }
                    }
                } else if (screen == Screen::QuickArtLook &&
                           (event.key.code == sf::Keyboard::Left ||
                            event.key.code == sf::Keyboard::Right) &&
                           quick_art_look) {
                    const auto artist_count =
                        static_cast<std::size_t>(quick_art_look->getTotalPairs());
                    if (artist_count > 0) {
                        selected_artist = event.key.code == sf::Keyboard::Left
                                              ? (selected_artist + artist_count - 1) % artist_count
                                              : (selected_artist + 1) % artist_count;
                    }
                }
            }
        }
        window.clear(sf::Color(28, 24, 35));
        window.setView(view);
        drawPanel(window, {42.0F, 34.0F}, {1196.0F, 652.0F}, sf::Color(45, 37, 55));

        if (has_font) {
            drawText(window, font, "ART NOUVEAU GUEST", 80.0F, 62.0F, 38, sf::Color(244, 205, 119));
            drawText(window, font, "Interactive gallery", 84.0F, 112.0F, 19,
                     sf::Color(190, 181, 202));
        }

        if (screen == Screen::Menu) {
            for (std::size_t index = 0; index < menu_items.size(); ++index) {
                const float y = 170.0F + static_cast<float>(index) * 62.0F;
                const auto color =
                    index == selected_index ? sf::Color(113, 76, 117) : sf::Color(67, 55, 79);
                drawPanel(window, {100.0F, y}, {470.0F, 48.0F}, color);
                if (has_font) {
                    drawText(window, font, menu_items[index], 130.0F, y + 10.0F, 21);
                }
            }
            if (has_font) {
                drawText(window, font, "Use Up/Down and Enter. Escape exits.", 100.0F, 640.0F, 17,
                         sf::Color(190, 181, 202));
                drawText(window, font, "Points: " + std::to_string(user->getPoints()), 880.0F,
                         112.0F, 20, sf::Color(244, 205, 119));
            }
        } else if (screen == Screen::Gallery || screen == Screen::Collection) {
            const auto& paintings =
                screen == Screen::Gallery ? gallery.getPaintings() : user->getCollection();
            if (has_font) {
                drawText(window, font, screen == Screen::Gallery ? "Gallery" : "My Collection",
                         100.0F, 178.0F, 30);
            }
            for (std::size_t index = 0; index < paintings.size(); ++index) {
                const float y = 220.0F + static_cast<float>(index) * 52.0F;
                const auto color =
                    index == selected_index ? sf::Color(113, 76, 117) : sf::Color(67, 55, 79);
                drawPanel(window, {100.0F, y}, {980.0F, 42.0F}, color);
                if (has_font) {
                    drawText(window, font, paintings[index]->getTitle(), 125.0F, y + 8.0F, 18);
                    drawText(window, font, artistName(paintings[index]), 620.0F, y + 9.0F, 17,
                             sf::Color(210, 201, 216));
                }
            }
            if (has_font) {
                drawText(window, font, "Enter: details   Escape: back", 100.0F, 635.0F, 18,
                         sf::Color(190, 181, 202));
            }
        } else if (screen == Screen::Details && selected_painting) {
            drawPanel(window, {100.0F, 190.0F}, {980.0F, 360.0F}, sf::Color(67, 55, 79));
            if (has_font) {
                drawText(window, font, selected_painting->getTitle(), 140.0F, 230.0F, 34,
                         sf::Color(244, 205, 119));
                drawText(window, font, "Artist: " + artistName(selected_painting), 140.0F, 300.0F,
                         23);
                drawText(window, font, "Technique: " + selected_painting->getTechnique(), 140.0F,
                         345.0F, 21);
                drawText(window, font,
                         "Year: " + std::to_string(selected_painting->getCreationYear()), 140.0F,
                         390.0F, 21);
                drawText(window, font, selected_painting->isRare() ? "Rare work" : "Standard work",
                         140.0F, 435.0F, 21,
                         selected_painting->isRare() ? sf::Color(244, 205, 119)
                                                     : sf::Color(210, 201, 216));
                drawText(window, font, "Escape: back", 100.0F, 635.0F, 18,
                         sf::Color(190, 181, 202));
            }
        } else if (screen == Screen::QuickArtLook && quick_art_look) {
            const auto pair_count = quick_art_look->getTotalPairs();
            if (has_font) {
                drawText(window, font, "QUICK ART LOOK", 100.0F, 178.0F, 30,
                         sf::Color(244, 205, 119));
                drawText(window, font, "Match the painting with its artist", 100.0F, 220.0F, 20);
            }

            if (pair_count > 0) {
                const auto painting_index = static_cast<int>(selected_index);
                const auto artist_index = static_cast<int>(selected_artist);
                drawPanel(window, {100.0F, 285.0F}, {470.0F, 130.0F}, sf::Color(113, 76, 117));
                drawPanel(window, {650.0F, 285.0F}, {430.0F, 130.0F}, sf::Color(67, 55, 79));
                if (has_font) {
                    drawText(window, font, "Painting", 130.0F, 305.0F, 18,
                             sf::Color(210, 201, 216));
                    drawText(window, font, quick_art_look->getPaintingTitle(painting_index), 130.0F,
                             345.0F, 25);
                    drawText(window, font, "Selected artist", 680.0F, 305.0F, 18,
                             sf::Color(210, 201, 216));
                    drawText(window, font, quick_art_look->getArtistName(artist_index), 680.0F,
                             345.0F, 25);
                    drawText(window, font,
                             "Painting " + std::to_string(painting_index + 1) + "/" +
                                 std::to_string(pair_count),
                             100.0F, 465.0F, 20);
                    drawText(window, font,
                             "Correct: " + std::to_string(quick_art_look->getCorrectPairs()) +
                                 "   Wrong: " + std::to_string(quick_art_look->getWrongPairs()),
                             100.0F, 505.0F, 20);
                    drawText(window, font, game_feedback, 100.0F, 555.0F, 22,
                             game_feedback == "Correct match!" ? sf::Color(130, 220, 150)
                                                               : sf::Color(240, 130, 130));
                    drawText(window, font, "Up/Down: painting  Left/Right: artist  Enter: check",
                             100.0F, 610.0F, 17, sf::Color(190, 181, 202));
                    drawText(window, font, "Escape: back", 100.0F, 640.0F, 17,
                             sf::Color(190, 181, 202));
                }
            }
        } else if (screen == Screen::ArtQuiz) {
            const auto quiz = std::dynamic_pointer_cast<ArtQuiz>(gallery.findGame("Art Quiz"));
            if (has_font && quiz) {
                drawText(window, font, "ART QUIZ", 100.0F, 178.0F, 30, sf::Color(244, 205, 119));
                drawText(window, font,
                         "Question " + std::to_string(quiz->getCorrectAnswers() +
                                                      quiz->getWrongAnswers() + 1),
                         100.0F, 230.0F, 20);
                drawPanel(window, {100.0F, 285.0F}, {980.0F, 145.0F}, sf::Color(67, 55, 79));
                drawText(window, font, quiz->getCurrentQuestionText(), 135.0F, 330.0F, 24);
                drawPanel(window, {100.0F, 475.0F}, {980.0F, 56.0F}, sf::Color(113, 76, 117));
                drawText(window, font, quiz_input + "_", 125.0F, 490.0F, 23);
                drawText(window, font,
                         "Correct: " + std::to_string(quiz->getCorrectAnswers()) +
                             "   Wrong: " + std::to_string(quiz->getWrongAnswers()),
                         100.0F, 570.0F, 20);
                drawText(window, font, game_feedback, 100.0F, 610.0F, 21,
                         game_feedback == "Correct answer!" ? sf::Color(130, 220, 150)
                                                            : sf::Color(240, 130, 130));
                drawText(window, font, "Type answer  Enter: submit  Backspace: erase  Escape: back",
                         100.0F, 650.0F, 16, sf::Color(190, 181, 202));
            }
        } else if (screen == Screen::ArtisticDelight) {
            const auto delight =
                std::dynamic_pointer_cast<ArtisticDelight>(gallery.findGame("Artistic Delight"));
            if (has_font && delight) {
                drawText(window, font, "ARTISTIC DELIGHT", 100.0F, 178.0F, 30,
                         sf::Color(244, 205, 119));
                drawText(window, font, "Guess the colors of the painting", 100.0F, 225.0F, 20);
                drawPanel(window, {100.0F, 285.0F}, {980.0F, 110.0F}, sf::Color(67, 55, 79));
                drawText(window, font,
                         "Similarity: " + std::to_string(delight->getSimilarityScore()) + "%",
                         135.0F, 315.0F, 25);
                drawText(window, font,
                         "Attempts remaining: " + std::to_string(delight->getAttemptsRemaining()),
                         135.0F, 355.0F, 22);
                drawPanel(window, {100.0F, 445.0F}, {980.0F, 56.0F}, sf::Color(113, 76, 117));
                drawText(window, font, color_input + "_", 125.0F, 460.0F, 23);
                drawText(window, font, game_feedback, 100.0F, 545.0F, 21,
                         game_feedback == "All colors found!" ? sf::Color(130, 220, 150)
                                                              : sf::Color(210, 201, 216));
                drawText(window, font, "Type color  Enter: submit  H: hint  Escape: back", 100.0F,
                         625.0F, 17, sf::Color(190, 181, 202));
            }
        } else if (screen == Screen::ArtPuzzle) {
            const auto puzzle =
                std::dynamic_pointer_cast<ArtPuzzle>(gallery.findGame("Art Puzzle"));
            if (has_font && puzzle) {
                drawText(window, font, "ART PUZZLE", 100.0F, 178.0F, 30, sf::Color(244, 205, 119));
                drawText(window, font,
                         "Moves: " + std::to_string(puzzle->getMovesMade()) + " / " +
                             std::to_string(puzzle->getMovesMade() + puzzle->getMovesRemaining()),
                         100.0F, 225.0F, 20);
                const int dimension = puzzle->getFragmentCount() == 4   ? 2
                                      : puzzle->getFragmentCount() == 9 ? 3
                                                                        : 4;
                for (int index = 0; index < puzzle->getFragmentCount(); ++index) {
                    const float x = 180.0F + static_cast<float>(index % dimension) * 150.0F;
                    const float y = 285.0F + static_cast<float>(index / dimension) * 100.0F;
                    const auto selected = index == puzzle_first || index == puzzle_second;
                    drawPanel(window, {x, y}, {110.0F, 70.0F},
                              selected ? sf::Color(113, 76, 117) : sf::Color(67, 55, 79));
                    drawText(window, font, std::to_string(puzzle->getFragmentAt(index)), x + 43.0F,
                             y + 18.0F, 28);
                }
                drawText(window, font,
                         "First: " + std::to_string(puzzle_first) +
                             "   Second: " + std::to_string(puzzle_second),
                         100.0F, 590.0F, 20);
                drawText(window, font, game_feedback, 100.0F, 625.0F, 20);
                drawText(window, font, "Up/Down first  Left/Right second  Enter swap  Escape back",
                         100.0F, 660.0F, 16, sf::Color(190, 181, 202));
            }
        }

        window.display();
    }

    try {
        UserProgressStore::save(*user, UserProgressStore::pathFromEnvironment());
    } catch (const std::exception& exception) {
        std::cerr << "Unable to save user progress: " << exception.what() << '\n';
        return 1;
    }
    return 0;
}
