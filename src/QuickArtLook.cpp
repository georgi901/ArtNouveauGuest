#include "../headers/QuickArtLook.h"
#include "../headers/MiniJoc.h"
#include <iostream>
#include <algorithm>
#include <random>

QuickArtLook::QuickArtLook(const std::string& nume, Dificultate dif)
    : MiniJoc(nume, "Asociază tablourile cu artiștii corecți!", dif),
      perechi_corecte(0),
      perechi_gresite(0)
{
    std::cout << "QuickArtLook constructor: " << nume << std::endl;
}

QuickArtLook::QuickArtLook(const QuickArtLook& other)
    : MiniJoc(other),
      perechi(other.perechi),
      perechi_corecte(other.perechi_corecte),
      perechi_gresite(other.perechi_gresite)
{
    std::cout << " QuickArtLook copy constructor" << std::endl;
}

std::unique_ptr<MiniJoc> QuickArtLook::clone() const {
    return std::make_unique<QuickArtLook>(*this);
}

std::string QuickArtLook::getTipJoc() const {
    return "Quick Art Look";
}

void QuickArtLook::adaugaPereche(std::shared_ptr<Tablou> tablou, std::shared_ptr<Artist> artist) {
    perechi.push_back({tablou, artist});
    std::cout << "Pereche adăugată: " << tablou->getTitlu() << " - " << artist->getNume() << std::endl;
}

void QuickArtLook::afiseazaTablele() const {
    std::cout << "\n=== TABLOURI ===\n";
    for (size_t i = 0; i < perechi.size(); i++) {
        std::cout << i + 1 << ". " << perechi[i].first->getTitlu() << std::endl;
    }
}

void QuickArtLook::afiseazaArtisti() const {
    std::cout << "\n=== ARTIȘTI ===\n";

    // Creează o listă amestecată de artiști
    std::vector<std::string> nume_artisti;
    for (const auto& pereche : perechi) {
        nume_artisti.push_back(pereche.second->getNume() + " " + pereche.second->getPrenume());
    }

    // Amestecă pentru a nu fi în aceeași ordine
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(nume_artisti.begin(), nume_artisti.end(), g);

    for (size_t i = 0; i < nume_artisti.size(); i++) {
        std::cout << char('A' + i) << ". " << nume_artisti[i] << std::endl;
    }
}

bool QuickArtLook::verificaPereche(const std::string& titlu_tablou, const std::string& nume_artist) {
    for (const auto& pereche : perechi) {
        if (pereche.first->getTitlu() == titlu_tablou) {
            std::string nume_complet = pereche.second->getNume() + " " + pereche.second->getPrenume();
            std::string nume_complet_inv = pereche.second->getPrenume() + " " + pereche.second->getNume();

            if (nume_artist == pereche.second->getNume() ||
                nume_artist == nume_complet ||
                nume_artist == nume_complet_inv) {
                perechi_corecte++;
                std::cout << "✓ Corect! " << titlu_tablou << " este de " << nume_complet << std::endl;
                return true;
            } else {
                perechi_gresite++;
                std::cout << "✗ Greșit! " << titlu_tablou << " nu este de " << nume_artist << std::endl;
                return false;
            }
        }
    }

    std::cout << "Tabloul '" << titlu_tablou << "' nu a fost găsit." << std::endl;
    return false;
}

void QuickArtLook::amestecaPerechile() {
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(perechi.begin(), perechi.end(), g);
    std::cout << "Perechile au fost amestecate!" << std::endl;
}

void QuickArtLook::initializeaza_implementare() {
    perechi_corecte = 0;
    perechi_gresite = 0;

    amestecaPerechile();

    size_t max_perechi = 3;
    switch(dificultate) {
        case Dificultate::Usor:  max_perechi = 3; break;
        case Dificultate::Mediu: max_perechi = 5; break;
        case Dificultate::Greu:  max_perechi = 8; break;
    }

    if (perechi.size() > max_perechi) {
        perechi.resize(max_perechi);
    }

    std::cout << "Quick Art Look initializat!" << std::endl;
    std::cout << "Perechi de ghicit: " << perechi.size() << std::endl;
}

int QuickArtLook::calculeaza_puncte_implementare() {
    if (perechi.empty()) {
        return 0;
    }

    double procent_corect = static_cast<double>(perechi_corecte) / perechi.size() * 100.0;
    int puncte = static_cast<int>((procent_corect / 100.0) * puncte_maxime);

    int penalizare = perechi_gresite * 10;
    puncte -= penalizare;

    puncte = std::max(0, std::min(puncte, puncte_maxime));

    std::cout << "Corecte: " << perechi_corecte << "/" << perechi.size() << std::endl;
    std::cout << "Gresite: " << perechi_gresite << " (penalizare: -" << penalizare << ")" << std::endl;

    return puncte;
}

void QuickArtLook::afiseaza_reguli_implementare() const {
    size_t max_perechi = 3;
    switch(dificultate) {
        case Dificultate::Usor:  max_perechi = 3; break;
        case Dificultate::Mediu: max_perechi = 5; break;
        case Dificultate::Greu:  max_perechi = 8; break;
    }
    std::cout << "QUICK ART LOOK - Reguli:" << std::endl;
    std::cout << "1. Vei vedea o lista de tablouri si o lista de artisti." << std::endl;
    std::cout << "2. Trebuie sa asociezi fiecare tablou cu artistul corect." << std::endl;
    std::cout << "3. Scrie titlul tabloului si numele artistului." << std::endl;
    std::cout << "4. Raspunsurile gresite scad din punctaj." << std::endl;
    std::cout << "Perechi de ghicit: " <<  max_perechi << std::endl;
}