/**
 * @file ArtQuiz.cpp
 * @brief Implementation of the ArtQuiz class.
 *
 * Contains the implementation of the quiz game with questions about
 * paintings and artists from the gallery.
 */

#include "../headers/ArtQuiz.h"

#include <algorithm>
#include <cctype>
#include <iostream>
#include <random>
#include <sstream>

#include "Artist.h"

ArtQuiz::ArtQuiz(const std::string& name, Difficulty dif)
    : MiniGame(name, "Answer questions about paintings from the gallery!", dif)
    , quiz_paintings()
    , questions()
    , current_question(0)
    , correct_answers(0)
    , wrong_answers(0) {
    std::cout << "ArtQuiz constructor: " << name << std::endl;
}

ArtQuiz::ArtQuiz(const ArtQuiz& other)
    : MiniGame(other)
    , quiz_paintings()
    , questions(other.questions)
    , current_question(other.current_question)
    , correct_answers(other.correct_answers)
    , wrong_answers(other.wrong_answers) {
    std::cout << "ArtQuiz copy constructor" << std::endl;
}

std::unique_ptr<MiniGame> ArtQuiz::clone() const {
    return std::make_unique<ArtQuiz>(*this);
}

std::string ArtQuiz::getGameType() const {
    return "Art Quiz";
}

void ArtQuiz::addPainting(std::shared_ptr<Painting> painting) {
    if (painting) {
        quiz_paintings.push_back(painting);
    }
}

void ArtQuiz::generateQuestions() {
    questions.clear();

    for (const auto& painting : quiz_paintings) {
        auto artist = painting->getArtist();

        Question q1;
        q1.text = "Who painted the painting '" + painting->getTitle() + "'?";
        q1.correct_answer = artist ? artist->getName() : "Unknown";
        q1.points = 10;
        questions.push_back(q1);

        Question q2;
        q2.text = "In what year was the painting '" + painting->getTitle() + "' created?";
        q2.correct_answer = std::to_string(painting->getCreationYear());
        q2.points = 15;
        questions.push_back(q2);

        Question q3;
        q3.text = "What technique was used for '" + painting->getTitle() + "'?";
        q3.correct_answer = painting->getTechnique();
        q3.points = 20;
        questions.push_back(q3);

        Question q4;
        q4.text = "Is the painting '" + painting->getTitle() + "' considered rare? (yes/no)";
        q4.correct_answer = painting->isRare() ? "yes" : "no";
        q4.points = 10;
        questions.push_back(q4);
    }

    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(questions.begin(), questions.end(), g);

    // Limit the number of questions based on difficulty
    size_t maximum_questions = questions.size();
    switch (difficulty) {
        case Difficulty::Easy:
            maximum_questions = 3;
            break;
        case Difficulty::Medium:
            maximum_questions = 5;
            break;
        case Difficulty::Hard:
            maximum_questions = 7;
            break;
        default:
            maximum_questions = 3;
            break;
    }

    if (questions.size() > maximum_questions) {
        questions.resize(maximum_questions);
    }

    std::cout << "Generated " << questions.size() << " questions." << std::endl;
}

void ArtQuiz::displayCurrentQuestion() const {
    if (current_question >= static_cast<int>(questions.size())) {
        std::cout << "No questions left!" << std::endl;
        return;
    }

    const auto& q = questions[static_cast<std::size_t>(current_question)];
    std::cout << "\n|==========================================" << std::endl;
    std::cout << "Question " << (current_question + 1) << "/" << questions.size() << std::endl;
    std::cout << "Points: " << q.points << std::endl;
    std::cout << "==========================================" << std::endl;
    std::cout << q.text << std::endl;
    std::cout << "Your answer: ";
}

bool ArtQuiz::answer(const std::string& response) {
    if (current_question >= static_cast<int>(questions.size())) {
        return false;
    }

    const auto& q = questions[static_cast<std::size_t>(current_question)];

    // Compare answers
    std::string lowercase_answer = response;
    std::string lowercase_correct_answer = q.correct_answer;

    std::transform(lowercase_answer.begin(), lowercase_answer.end(), lowercase_answer.begin(),
                   [](unsigned char character) { return static_cast<char>(std::tolower(character)); });
    std::transform(lowercase_correct_answer.begin(), lowercase_correct_answer.end(),
                   lowercase_correct_answer.begin(),
                   [](unsigned char character) { return static_cast<char>(std::tolower(character)); });

    // Check whether the answer contains the key word
    bool correct = (lowercase_answer.find(lowercase_correct_answer) != std::string::npos) ||
                   (lowercase_correct_answer.find(lowercase_answer) != std::string::npos &&
                    !lowercase_answer.empty());

    if (correct) {
        correct_answers++;
        std::cout << "Correct! The answer was: " << q.correct_answer << std::endl;
    } else {
        wrong_answers++;
        std::cout << "Wrong! The correct answer was: " << q.correct_answer << std::endl;
    }

    return correct;
}

bool ArtQuiz::hasRemainingQuestions() const {
    return current_question < static_cast<int>(questions.size());
}

void ArtQuiz::nextQuestion() {
    current_question++;
}

std::string ArtQuiz::getCurrentQuestionText() const {
    if (!hasRemainingQuestions()) {
        return "No questions left.";
    }
    return questions[static_cast<std::size_t>(current_question)].text;
}

void ArtQuiz::initializeImplementation() {
    current_question = 0;
    correct_answers = 0;
    wrong_answers = 0;

    generateQuestions();

    std::cout << "Art Quiz initialized!" << std::endl;
    std::cout << "Question count: " << questions.size() << std::endl;
}

int ArtQuiz::calculatePointsImplementation() {
    int total_points = 0;

    if (!questions.empty()) {
        int points_per_question = maximum_points / static_cast<int>(questions.size());
        total_points = correct_answers * points_per_question;
    }

    if (difficulty == Difficulty::Hard) {
        total_points -= wrong_answers * 5;
    }

    total_points = std::max(0, std::min(total_points, maximum_points));

    std::cout << "Correct answers: " << correct_answers << "/" << questions.size() << std::endl;
    std::cout << "Wrong answers: " << wrong_answers << std::endl;

    return total_points;
}

void ArtQuiz::displayRulesImplementation() const {
    std::cout << "ART QUIZ - Rules:" << std::endl;
    std::cout << "1. You will receive questions about paintings from the gallery." << std::endl;
    std::cout << "2. Questions may concern the artist, year, technique, etc." << std::endl;
    std::cout << "3. Type your answer and press Enter." << std::endl;
    std::cout << "4. Each correct answer gives you points." << std::endl;
    std::cout << "5. At higher difficulty, wrong answers reduce your score." << std::endl;
}