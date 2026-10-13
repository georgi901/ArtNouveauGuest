#pragma once

/**
 * @file ArtQuiz.h
 * @brief Defines the ArtQuiz class - an art knowledge quiz game.
 *
 * This file contains the ArtQuiz class, which implements a mini-game based on a
 * quiz about paintings and artists.
 */

#include <memory>
#include <vector>

#include "MiniGame.h"
#include "Painting.h"

/**
 * @struct Question
 * @brief Structure representing a quiz question.
 */
struct Question {
    std::string text;
    std::string correct_answer;
    std::vector<std::string> variante;  // possible answer variants
    int points = 0;                     ///< Points awarded for a correct answer
};

/**
 * @class ArtQuiz
 * @brief Quiz game about paintings from the gallery.
 *
 * Derived from MiniGame, this class implements a question-based game that tests
 * knowledge about:
 * - Painting authors
 * - Creation year
 * - Techniques used
 * - Painting rarity
 *
 * The number of questions varies by difficulty:
 * - Easy: 3 questions
 * - Medium: 5 questions
 * - Hard: 7 questions (with penalties for wrong answers)
 *
 * @code
 * auto quiz = std::make_unique<ArtQuiz>("Quiz Art Nouveau", Difficulty::Medium);
 * quiz->addPainting(painting);
 * quiz->initialize();
 * while (quiz->hasRemainingQuestions()) {
 *     quiz->displayCurrentQuestion();
 *     quiz->answer(answer);
 *     quiz->nextQuestion();
 * }
 * @endcode
 */
class ArtQuiz : public MiniGame {
private:
    std::vector<std::shared_ptr<Painting>> quiz_paintings;
    std::vector<Question> questions;
    int current_question = 0;
    int correct_answers = 0;
    int wrong_answers = 0;

protected:
    void initializeImplementation() override;
    int calculatePointsImplementation() override;
    void displayRulesImplementation() const override;

public:
    ArtQuiz(const std::string& name, Difficulty dif);
    ArtQuiz(const ArtQuiz& other);
    ~ArtQuiz() override = default;

    std::unique_ptr<MiniGame> clone() const override;
    std::string getGameType() const override;

    // Specific functions
    void addPainting(std::shared_ptr<Painting> painting);
    void generateQuestions();
    void displayCurrentQuestion() const;
    bool answer(const std::string& response);
    bool hasRemainingQuestions() const;
    void nextQuestion();

    // Getteri
    int getCorrectAnswers() const {
        return correct_answers;
    }
    int getWrongAnswers() const {
        return wrong_answers;
    }
    int getRemainingQuestions() const {
        return static_cast<int>(questions.size()) - current_question;
    }
    std::string getCurrentQuestionText() const;
};
