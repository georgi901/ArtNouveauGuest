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

    return registru;
}

void JocFactory::initializeazaTipuriImplicite() {

    if (initializat_) {
        return;
    }

    initializat_ = true;

    auto& registru = obtineRegistru();


    registru["ArtisticDelight"] = [](Dificultate d) {
        return std::make_unique<ArtisticDelight>("Artistic Delight", d);
    };

    registru["QuickArtLook"] = [](Dificultate d) {
        return std::make_unique<QuickArtLook>("Quick Art Look", d);
    };

    registru["ArtQuiz"] = [](Dificultate d) {
        return std::make_unique<ArtQuiz>("Art Quiz", d);
    };

    registru["ArtPuzzle"] = [](Dificultate d) {
        return std::make_unique<ArtPuzzle>("Art Puzzle", d);
    };

    std::cout << "[JocFactory] Tipuri implicite înregistrate: " << registru.size() << " tipuri disponibile.\n";
}

std::unique_ptr<MiniJoc> JocFactory::creeazaJoc(const std::string& tip, Dificultate dificultate) {
    if (!initializat_) {
        initializeazaTipuriImplicite();
    }
    auto& registru = obtineRegistru();

    auto it = registru.find(tip);
    if (it == registru.end()) {
        throw JocInvalidException("Tip de joc necunoscut: " + tip);
    }

    std::cout << "[JocFactory] Se creează jocul: " << tip << "\n";
    return it->second(dificultate);
}

void JocFactory::inregistreazaJoc(const std::string& tip, FunctieCreator creator) {
    if (!initializat_) {
        initializeazaTipuriImplicite();
    }
    auto& registru = obtineRegistru();
    registru[tip] = std::move(creator);
    std::cout << "[JocFactory] Tip nou de joc înregistrat: " << tip << "\n";
}

std::vector<std::string> JocFactory::obtineTipuriDisponibile() {
    if (!initializat_) {
        initializeazaTipuriImplicite();
    }
    std::vector<std::string> tipuri;
    for (const auto& pereche : obtineRegistru()) {
        tipuri.push_back(pereche.first);
    }
    return tipuri;
}

bool JocFactory::esteTipInregistrat(const std::string& tip) {
    if (!initializat_) {
        initializeazaTipuriImplicite();
    }
    auto& registru = obtineRegistru();
    return registru.find(tip) != registru.end();
}
