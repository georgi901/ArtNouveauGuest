/**
 * @file Utilizator.h
 * @brief Definește clasa Utilizator pentru vizitatorii galeriei.
 *
 * Acest fișier conține clasa Utilizator care modelează un vizitator
 * al galeriei, cu colecție personală de tablouri și sistem de puncte.
 */

#ifndef ARTNOUVEAUGUEST_UTILIZATOR_H
#define ARTNOUVEAUGUEST_UTILIZATOR_H

#pragma once
#include <iostream>
#include <limits>
#include <memory>
#include <string>
#include <vector>

#include "Artist.h"
#include "Tablou.h"

/**
 * @class Utilizator
 * @brief Reprezintă un vizitator/utilizator al galeriei de artă.
 *
 * Clasa gestionează:
 * - Informații personale (nume, username, email, vârstă)
 * - Colecție personală de tablouri
 * - Sistem de puncte pentru activități
 * - Istoric de activități în galerie
 *
 * Utilizatorul poate acumula puncte prin jocuri și le poate folosi
 * pentru a cumpăra tablouri în colecția personală.
 *
 * @code
 * Utilizator user("Ion Popescu", "ion_p", "ion@email.com", 25, "2024-01-15");
 * user.adaugaPuncte(100);
 * user.cumparaTablou(tablou, 50);
 * user.afiseazaColectie();
 * @endcode
 */
class Utilizator {
private:
    const std::string nume;
    const std::string username;
    const std::string email;
    const int varsta;
    const std::string data_inregistrare;
    std::vector<std::string> istoric_activitati;
    std::vector<std::shared_ptr<Tablou>> colectie;
    void adaugaActivitate(const std::string& activitate);
    int puncte;

public:
    Utilizator(const std::string& n, const std::string& u, const std::string& e, int v, const std::string& d);
    ~Utilizator() = default;
    void adaugaTablou(const std::shared_ptr<Tablou>& tablou);
    std::shared_ptr<Tablou> cautaTablou(const std::string& titlu) const;
    void afiseazaColectie() const;

    friend std::ostream& operator<<(std::ostream& out, const Utilizator& u);
    friend std::istream& operator>>(std::istream& in, Utilizator& u) {
        size_t n;
        std::cout << "Câte tablouri vrei să adaugi în colecție? ";
        in >> n;
        in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        for (size_t i = 0; i < n; ++i) {
            std::string titlu;
            std::cout << "Titlu tablou " << i + 1 << ": ";
            std::getline(in, titlu);

            std::shared_ptr<Tablou> tablou_gasit = nullptr;
            for (const auto& artist : Artist::getListaArtistilor()) {
                auto t = artist->cautaTablou(titlu);
                if (t) {
                    tablou_gasit = t;
                    break;
                }
            }

            if (tablou_gasit) {
                u.adaugaTablou(tablou_gasit);
                std::cout << "Tabloul \"" << titlu << "\" a fost adăugat în colecție.\n";
            } else {
                std::cout << "Tabloul \"" << titlu << "\" nu a fost găsit.\n";
            }
        }
        return in;
    }

    void adaugaPuncte(int p) {
        puncte += p;
    }
    int getPuncte() const {
        return puncte;
    }
    void cumparaTablou(std::shared_ptr<Tablou> tablou, int cost);
};

#endif  // ARTNOUVEAUGUEST_UTILIZATOR_H