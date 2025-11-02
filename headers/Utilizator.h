#ifndef ARTNOUVEAUGUEST_UTILIZATOR_H
#define ARTNOUVEAUGUEST_UTILIZATOR_H

#pragma once
#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <limits>
#include "Tablou.h"
#include "Artist.h"

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
            std::cout << "Titlu tablou " << i+1 << ": ";
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


};

#endif //ARTNOUVEAUGUEST_UTILIZATOR_H