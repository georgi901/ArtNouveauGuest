/**
 * @file ArtQuiz.cpp
 * @brief Implementarea clasei ArtQuiz.
 *
 * Conține implementarea jocului de tip quiz cu întrebări despre
 * tablourile și artiștii din galerie.
 */

#include "../headers/ArtQuiz.h"

#include <algorithm>
#include <iostream>
#include <random>
#include <sstream>

#include "Artist.h"

ArtQuiz::ArtQuiz(const std::string& nume, Dificultate dif)
    : MiniJoc(nume, "Răspunde la întrebări despre tablourile din galerie!", dif)
    , intrebare_curenta(0)
    , raspunsuri_corecte(0)
    , raspunsuri_gresite(0) {
    std::cout << "ArtQuiz constructor: " << nume << std::endl;
}

ArtQuiz::ArtQuiz(const ArtQuiz& other)
    : MiniJoc(other)
    , tablouri_quiz(other.tablouri_quiz)
    , intrebari(other.intrebari)
    , intrebare_curenta(other.intrebare_curenta)
    , raspunsuri_corecte(other.raspunsuri_corecte)
    , raspunsuri_gresite(other.raspunsuri_gresite) {
    std::cout << "ArtQuiz copy constructor" << std::endl;
}

std::unique_ptr<MiniJoc> ArtQuiz::clone() const {
    return std::make_unique<ArtQuiz>(*this);
}

std::string ArtQuiz::getTipJoc() const {
    return "Art Quiz";
}

void ArtQuiz::adaugaTablou(std::shared_ptr<Tablou> tablou) {
    if (tablou) {
        tablouri_quiz.push_back(tablou);
    }
}

void ArtQuiz::genereazaIntrebari() {
    intrebari.clear();

    for (const auto& tablou : tablouri_quiz) {
        auto artist = tablou->getArtist();

        Intrebare q1;
        q1.text = "Cine a pictat tabloul '" + tablou->getTitlu() + "'?";
        q1.raspuns_corect = artist ? artist->getNume() : "Necunoscut";
        q1.puncte = 10;
        intrebari.push_back(q1);

        Intrebare q2;
        q2.text = "În ce an a fost realizat tabloul '" + tablou->getTitlu() + "'?";
        q2.raspuns_corect = std::to_string(tablou->getAnRealizare());
        q2.puncte = 15;
        intrebari.push_back(q2);

        Intrebare q3;
        q3.text = "Ce tehnică a fost folosită pentru '" + tablou->getTitlu() + "'?";
        q3.raspuns_corect = tablou->getTehnica();
        q3.puncte = 20;
        intrebari.push_back(q3);

        Intrebare q4;
        q4.text = "Tabloul '" + tablou->getTitlu() + "' este considerat rar? (da/nu)";
        q4.raspuns_corect = tablou->este_rar() ? "da" : "nu";
        q4.puncte = 10;
        intrebari.push_back(q4);
    }

    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(intrebari.begin(), intrebari.end(), g);

    // Limitează numărul de întrebări în funcție de dificultate
    size_t max_intrebari = intrebari.size();
    switch (dificultate) {
        case Dificultate::Usor:
            max_intrebari = 3;
            break;
        case Dificultate::Mediu:
            max_intrebari = 5;
            break;
        case Dificultate::Greu:
            max_intrebari = 7;
            break;
    }

    if (intrebari.size() > max_intrebari) {
        intrebari.resize(max_intrebari);
    }

    std::cout << "Au fost generate " << intrebari.size() << " întrebări." << std::endl;
}

void ArtQuiz::afiseazaIntrebareCurenta() const {
    if (intrebare_curenta >= static_cast<int>(intrebari.size())) {
        std::cout << "Nu mai sunt întrebări!" << std::endl;
        return;
    }

    const auto& q = intrebari[intrebare_curenta];
    std::cout << "\n|==========================================" << std::endl;
    std::cout << "Întrebarea " << (intrebare_curenta + 1) << "/" << intrebari.size() << std::endl;
    std::cout << "Puncte: " << q.puncte << std::endl;
    std::cout << "==========================================" << std::endl;
    std::cout << q.text << std::endl;
    std::cout << "Răspunsul tău: ";
}

bool ArtQuiz::raspunde(const std::string& raspuns) {
    if (intrebare_curenta >= static_cast<int>(intrebari.size())) {
        return false;
    }

    const auto& q = intrebari[intrebare_curenta];

    // Compară răspunsurile
    std::string raspuns_lower = raspuns;
    std::string corect_lower = q.raspuns_corect;

    std::transform(raspuns_lower.begin(), raspuns_lower.end(), raspuns_lower.begin(), ::tolower);
    std::transform(corect_lower.begin(), corect_lower.end(), corect_lower.begin(), ::tolower);

    // Verifică dacă răspunsul conține cuvântul cheie
    bool corect = (raspuns_lower.find(corect_lower) != std::string::npos) ||
                  (corect_lower.find(raspuns_lower) != std::string::npos && !raspuns_lower.empty());

    if (corect) {
        raspunsuri_corecte++;
        std::cout << "Corect! Răspunsul era: " << q.raspuns_corect << std::endl;
    } else {
        raspunsuri_gresite++;
        std::cout << "Greșit! Răspunsul corect era: " << q.raspuns_corect << std::endl;
    }

    return corect;
}

bool ArtQuiz::areIntrebariRamase() const {
    return intrebare_curenta < static_cast<int>(intrebari.size());
}

void ArtQuiz::urmatoraIntrebare() {
    intrebare_curenta++;
}

void ArtQuiz::initializeaza_implementare() {
    intrebare_curenta = 0;
    raspunsuri_corecte = 0;
    raspunsuri_gresite = 0;

    genereazaIntrebari();

    std::cout << "Art Quiz inițializat!" << std::endl;
    std::cout << "Număr întrebări: " << intrebari.size() << std::endl;
}

int ArtQuiz::calculeaza_puncte_implementare() {
    int puncte_totale = 0;

    if (!intrebari.empty()) {
        int puncte_per_intrebare = puncte_maxime / intrebari.size();
        puncte_totale = raspunsuri_corecte * puncte_per_intrebare;
    }

    if (dificultate == Dificultate::Greu) {
        puncte_totale -= raspunsuri_gresite * 5;
    }

    puncte_totale = std::max(0, std::min(puncte_totale, puncte_maxime));

    std::cout << "Răspunsuri corecte: " << raspunsuri_corecte << "/" << intrebari.size() << std::endl;
    std::cout << "Răspunsuri greșite: " << raspunsuri_gresite << std::endl;

    return puncte_totale;
}

void ArtQuiz::afiseaza_reguli_implementare() const {
    std::cout << "ART QUIZ - Reguli:" << std::endl;
    std::cout << "1. Vei primi întrebări despre tablourile din galerie." << std::endl;
    std::cout << "2. Întrebările pot fi despre artist, an, tehnică, etc." << std::endl;
    std::cout << "3. Scrie răspunsul și apasă Enter." << std::endl;
    std::cout << "4. Fiecare răspuns corect îți aduce puncte." << std::endl;
    std::cout << "5. La dificultate mare, răspunsurile greșite scad din punctaj." << std::endl;
}