/**
 * @file JocFactory.cpp
 * @brief Implementarea design pattern-ului Factory pentru mini-jocuri.
 */

#include "../headers/JocFactory.h"

#include <iostream>

#include "../headers/ArtPuzzle.h"
#include "../headers/ArtQuiz.h"
#include "../headers/ArtisticDelight.h"
#include "../headers/Exceptii.h"
#include "../headers/QuickArtLook.h"

// Inițializare membru static
bool JocFactory::initializat_ = false;

std::map<std::string, JocFactory::FunctieCreator>& JocFactory::obtineRegistru() {
    // Variabilă locală statică - construită la prima utilizare
    static std::map<std::string, FunctieCreator> registru;

    // Inițializează tipurile implicite la primul acces
    if (!initializat_) {
        initializeazaTipuriImplicite();
    }

    return registru;
}

void JocFactory::initializeazaTipuriImplicite() {
    if (initializat_) {
        return;
    }

    // IMPORTANT: Setăm flag-ul ÎNAINTE de a accesa registrul pentru a preveni recursie infinită
    initializat_ = true;

    auto& registru = obtineRegistru();

    // Înregistrează ArtisticDelight
    registru["ArtisticDelight"] = [](Dificultate d) {
        return std::make_unique<ArtisticDelight>("Artistic Delight", d);
    };

    // Înregistrează QuickArtLook
    registru["QuickArtLook"] = [](Dificultate d) { return std::make_unique<QuickArtLook>("Quick Art Look", d); };

    // Înregistrează ArtQuiz
    registru["ArtQuiz"] = [](Dificultate d) { return std::make_unique<ArtQuiz>("Art Quiz", d); };

    // Înregistrează ArtPuzzle
    registru["ArtPuzzle"] = [](Dificultate d) { return std::make_unique<ArtPuzzle>("Art Puzzle", d); };

    std::cout << "[JocFactory] Tipuri implicite înregistrate: " << registru.size() << " tipuri disponibile.\n";
}

std::unique_ptr<MiniJoc> JocFactory::creeazaJoc(const std::string& tip, Dificultate dificultate) {
    auto& registru = obtineRegistru();

    auto it = registru.find(tip);
    if (it == registru.end()) {
        throw JocInvalidException("Tip de joc necunoscut: " + tip);
    }

    std::cout << "[JocFactory] Se creează jocul: " << tip << "\n";
    return it->second(dificultate);
}

void JocFactory::inregistreazaJoc(const std::string& tip, FunctieCreator creator) {
    auto& registru = obtineRegistru();
    registru[tip] = std::move(creator);
    std::cout << "[JocFactory] Tip nou de joc înregistrat: " << tip << "\n";
}

std::vector<std::string> JocFactory::obtineTipuriDisponibile() {
    std::vector<std::string> tipuri;
    for (const auto& pereche : obtineRegistru()) {
        tipuri.push_back(pereche.first);
    }
    return tipuri;
}

bool JocFactory::esteTipInregistrat(const std::string& tip) {
    auto& registru = obtineRegistru();
    return registru.find(tip) != registru.end();
}
