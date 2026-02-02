/**
 * @file MiniJoc.cpp
 * @brief Implementarea clasei abstracte MiniJoc.
 *
 * Conține implementarea metodelor de bază pentru sistemul de mini-jocuri,
 * folosind pattern-ul NVI (Non-Virtual Interface).
 */

#include "../headers/MiniJoc.h"

#include <iomanip>
#include <iostream>

/// Numărul total de jocuri jucate în sesiune
int MiniJoc::total_jocuri_jucate = 0;
/// Totalul punctelor acordate în toate jocurile
int MiniJoc::total_puncte_acordate = 0;

std::ostream& operator<<(std::ostream& os, const Dificultate& dif) {
    switch (dif) {
        case Dificultate::Usor:
            return os << "Usor";
        case Dificultate::Mediu:
            return os << "Mediu";
        case Dificultate::Greu:
            return os << "Greu";
        default:
            return os << "Necunoscut";
    }
}

MiniJoc::MiniJoc(const std::string& nume_joc, const std::string& descriere, Dificultate dificultate)
    : nume_joc(nume_joc), descriere(descriere), dificultate(dificultate), puncte_obtinute(0), finalizat(false) {
    switch (dificultate) {
        case Dificultate::Usor:
            puncte_maxime = 100;
            break;
        case Dificultate::Mediu:
            puncte_maxime = 200;
            break;
        case Dificultate::Greu:
            puncte_maxime = 300;
            break;
    }

    std::cout << "MiniJoc constructor: " << nume_joc << std::endl;
}

MiniJoc::MiniJoc(const MiniJoc& other)
    : nume_joc(other.nume_joc)
    , descriere(other.descriere)
    , dificultate(other.dificultate)
    , puncte_obtinute(other.puncte_obtinute)
    , puncte_maxime(other.puncte_maxime)
    , finalizat(other.finalizat) {
    std::cout << "MiniJoc copy constructor: " << nume_joc << std::endl;
}

MiniJoc& MiniJoc::operator=(const MiniJoc& other) {
    if (this != &other) {
        nume_joc = other.nume_joc;
        descriere = other.descriere;
        dificultate = other.dificultate;
        puncte_obtinute = other.puncte_obtinute;
        puncte_maxime = other.puncte_maxime;
        finalizat = other.finalizat;
    }
    std::cout << "[DEBUG] MiniJoc operator=: " << nume_joc << std::endl;
    return *this;
}

void MiniJoc::initializeaza() {
    std::cout << "\n=== Inițializare joc: " << nume_joc << " ===" << std::endl;
    std::cout << "Dificultate: " << dificultate << std::endl;
    std::cout << "Puncte maxime: " << puncte_maxime << std::endl;

    initializeaza_implementare();

    total_jocuri_jucate++;
    finalizat = false;
    puncte_obtinute = 0;

    std::cout << "Joc pregătit! Succes!" << std::endl;
}

int MiniJoc::calculeazaPuncte() {
    std::cout << "\n--- Calculare puncte ---" << std::endl;

    puncte_obtinute = calculeaza_puncte_implementare();

    total_puncte_acordate += puncte_obtinute;
    finalizat = true;

    std::cout << "Puncte obținute: " << puncte_obtinute << "/" << puncte_maxime << std::endl;

    return puncte_obtinute;
}
void MiniJoc::afiseazaRegulile() const {
    std::cout << "\n=== REGULI: " << nume_joc << " ===" << std::endl;
    std::cout << "Dificultate: " << dificultate << " | Puncte maxime: " << puncte_maxime << std::endl;
    std::cout << "---" << std::endl;

    afiseaza_reguli_implementare();

    std::cout << "---\n" << std::endl;
}

int MiniJoc::getTotalJocuri() {
    return total_jocuri_jucate;
}

int MiniJoc::getTotalPuncte() {
    return total_puncte_acordate;
}

void MiniJoc::afiseazaStatistici() {
    std::cout << "\n--- STATISTICI GLOBALE ---" << std::endl;
    std::cout << "Total jocuri jucate: " << total_jocuri_jucate << std::endl;
    std::cout << "Total puncte acordate: " << total_puncte_acordate << std::endl;

    if (total_jocuri_jucate > 0) {
        double medie = static_cast<double>(total_puncte_acordate) / total_jocuri_jucate;
        std::cout << "Medie puncte/joc: " << std::fixed << std::setprecision(2) << medie << std::endl;
    }
    std::cout << std::endl;
}

void MiniJoc::reseteazaStatistici() {
    total_jocuri_jucate = 0;
    total_puncte_acordate = 0;
    std::cout << "[INFO] Statistici resetate." << std::endl;
}

std::ostream& operator<<(std::ostream& os, const MiniJoc& joc) {
    os << joc.nume_joc << " (" << joc.getTipJoc() << ")"
       << " - " << joc.dificultate << " - " << joc.puncte_obtinute << "/" << joc.puncte_maxime << " puncte"
       << " - " << (joc.finalizat ? "Finalizat" : "Nefinalizat");
    return os;
}