#include "../headers/QuickArtLook.h"
#include "../headers/MiniJoc.h"
#include <iostream>
#include <algorithm>
#include <random>

QuickArtLook::QuickArtLook(const std::string& nume, Dificultate dif)
    : MiniJoc(nume, "Asociază tablourile cu artiștii corecți!", dif),
      perechi_corecte(0),
      perechi_gresite(0),
      timp_ramas(0)
{
    switch(dif) {
        case Dificultate::Usor:  timp_ramas = 60; break;
        case Dificultate::Mediu: timp_ramas = 45; break;
        case Dificultate::Greu:  timp_ramas = 30; break;
    }

    std::cout << " QuickArtLook constructor: " << nume << std::endl;
}

QuickArtLook::QuickArtLook(const QuickArtLook& other)
    : MiniJoc(other),
      perechi(other.perechi),
      perechi_corecte(other.perechi_corecte),
      perechi_gresite(other.perechi_gresite),
      timp_ramas(other.timp_ramas)
{
    std::cout << "[DEBUG] QuickArtLook copy constructor" << std::endl;
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

    switch(dificultate) {
        case Dificultate::Usor:  timp_ramas = 60; break;
        case Dificultate::Mediu: timp_ramas = 45; break;
        case Dificultate::Greu:  timp_ramas = 30; break;
    }

    amestecaPerechile();

    std::cout << "Quick Art Look inițializat!" << std::endl;
    std::cout << "Timp disponibil: " << timp_ramas << " secunde" << std::endl;
    std::cout << "Perechi de ghicit: " << perechi.size() << std::endl;
}

int QuickArtLook::calculeaza_puncte_implementare() {
    if (perechi.empty()) {
        return 0;
    }

    // Puncte bazate pe răspunsuri corecte
    double procent_corect = static_cast<double>(perechi_corecte) / perechi.size() * 100.0;
    int puncte = static_cast<int>((procent_corect / 100.0) * puncte_maxime);

    // Penalizare pentru răspunsuri greșite
    int penalizare = perechi_gresite * 10;
    puncte -= penalizare;

    // Bonus pentru timp rămas
    int bonus_timp = timp_ramas / 2;
    puncte += bonus_timp;

    puncte = std::max(0, std::min(puncte, puncte_maxime));

    std::cout << "Corecte: " << perechi_corecte << "/" << perechi.size() << std::endl;
    std::cout << "Greșite: " << perechi_gresite << std::endl;
    std::cout << "Bonus timp: +" << bonus_timp << std::endl;

    return puncte;
}

void QuickArtLook::afiseaza_reguli_implementare() const {
    std::cout << "QUICK ART LOOK - Reguli:" << std::endl;
    std::cout << "1. Vei vedea o listă de tablouri și o listă de artiști." << std::endl;
    std::cout << "2. Trebuie să asociezi fiecare tablou cu artistul corect." << std::endl;
    std::cout << "3. Scrie titlul tabloului și numele artistului." << std::endl;
    std::cout << "4. Ai timp limitat!" << std::endl;
    std::cout << "5. Răspunsurile greșite scad din punctaj." << std::endl;
    std::cout << "Timp disponibil: " << timp_ramas << " secunde" << std::endl;
}
