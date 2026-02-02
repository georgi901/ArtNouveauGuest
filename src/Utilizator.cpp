/**
 * @file Utilizator.cpp
 * @brief Implementarea clasei Utilizator.
 *
 * Conține implementarea metodelor pentru gestionarea utilizatorilor,
 * colecțiilor de tablouri și sistemului de puncte.
 */

#include "../headers/Utilizator.h"

#include <iostream>

#include "../headers/Exceptii.h"
#include "../headers/Galerie.h"
#include "../headers/Tablou.h"

Utilizator::Utilizator(const std::string& n, const std::string& u, const std::string& e, int v, const std::string& d)
    : nume(n), username(u), email(e), varsta(v), data_inregistrare(d), puncte(0) {
}

void Utilizator::adaugaTablou(const std::shared_ptr<Tablou>& tablou) {
    if (!tablou) {
        return;
    }
    colectie.push_back(tablou);
    tablou->set_colectionat(true);
    adaugaActivitate("A adăugat tabloul " + tablou->getTitlu());
}

std::shared_ptr<Tablou> Utilizator::cautaTablou(const std::string& titlu) const {
    for (const auto& t : colectie) {
        if (t->getTitlu() == titlu)
            return t;
    }
    return nullptr;
}

void Utilizator::afiseazaColectie() const {
    std::cout << "\n--------------------- Colecția lui " << nume << " ----------------------\n";
    for (const auto& t : colectie) {
        std::cout << *t << "\n";
    }
}

void Utilizator::adaugaActivitate(const std::string& activitate) {
    istoric_activitati.push_back(activitate);
}

std::ostream& operator<<(std::ostream& out, const Utilizator& u) {
    out << "\n------------------------------- PROFIL UTILIZATOR --------------------------------\n";
    out << "Nume: " << u.nume << "\n";
    out << "Username: " << u.username << "\n";
    out << "Email: " << u.email << "\n";
    out << "Varsta: " << u.varsta << "\n";
    out << "Data inregistrare: " << u.data_inregistrare << "\n";
    out << "Puncte: " << u.puncte << "\n";
    out << "Tablouri in colectie: " << u.colectie.size() << "\n";

    if (!u.istoric_activitati.empty()) {
        out << "\nIstoric activitati:\n";
        for (const auto& act : u.istoric_activitati)
            out << "  - " << act << "\n";
    }
    return out;
}

void Utilizator::cumparaTablou(std::shared_ptr<Tablou> tablou, int cost) {
    if (!tablou) {
        throw TablouIndisponibilException("(tablou null)");
    }

    if (puncte < cost) {
        throw PuncteInsuficienteException(puncte, cost);
    }

    if (tablou->este_colectionat()) {
        throw TablouIndisponibilException(tablou->getTitlu());
    }

    puncte -= cost;
    adaugaTablou(tablou);
    adaugaActivitate("A cumpărat tabloul " + tablou->getTitlu() + " pentru " + std::to_string(cost) + " puncte");
}
