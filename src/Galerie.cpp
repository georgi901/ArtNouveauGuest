#include <iostream>
#include "../headers/Galerie.h"
#include "../headers/Artist.h"
#include "../headers/Tablou.h"


void Galerie::afiseazaArtiști() const {
    std::cout << "\n----------------------------- Lista artiștilor --------------------------------\n";
    for (const auto& artist : artisti) {
        std::cout << "\n-------------------------------------------------------------------------------\n";
        std::cout << artist->getNume() << " " << artist->getPrenume()
          << " - " << artist->getTitlu() << " (" << artist->getVarsta() << " ani)\n";
    }
}

void Galerie::afiseazaTablouri() const {
    std::cout <<     "\n----------------------------- Lista tablourilor -------------------------------\n";
    for (const auto& tablou : tablouri) {
        std::cout << "\n-------------------------------------------------------------------------------\n";
        auto artist = tablou->getArtist();
        std::cout <<" - "<< tablou->getTitlu() <<" - "<< " de "
                  << (artist ? artist->getNume(): "Necunoscut") << " " << (artist ? artist->getPrenume(): "Necunoscut") <<"\n";
    }
}


std::shared_ptr<Artist> Galerie::cautaArtist(const std::string& num) const {
    for (const auto& artist : artisti) {
        std::string nume_complet = artist->getNume() + " " + artist->getPrenume();
        std::string nume_complet_inversat = artist->getPrenume() + " " + artist->getNume();

        if (artist->getNume() == num ||
            artist->getPrenume() == num ||
            nume_complet == num ||
            nume_complet_inversat == num) {
            return artist;
            }
    }
    return nullptr;
}


std::shared_ptr<Tablou> Galerie::cautaTablou(const std::string& titlu) const {
    for (const auto& tablou : tablouri) {
        if (tablou->getTitlu() == titlu) return tablou;
    }
    return nullptr;
}


std::ostream& operator<<(std::ostream& out, const Galerie& g) {
    out << "========================================================================================\n";
    out << "\n----------------------------------- GALERIE ---------------------------------------\n";
    out << "Galerie: " << g.nume << "\n";
    out << "Subiect: " << g.subiect << "\n";
    out << "An infiintare: " << g.an_infiintare << "\n";
    out << "========================================================================================\n";
    out << "-------------------------------------- ARTIȘTI ----------------------------------------\n";
    for (const auto& a : g.artisti) {
        out << "===========================================================\n";
        out << *a << "\n";
        out << "===========================================================\n";
    }
    out << "========================================================================================\n";
    out << "-------------------------------------- TABLOURI ---------------------------------------\n";
    for (const auto& t : g.tablouri) {
        out << "===========================================================\n";
        out << *t << "\n";
        out << "===========================================================\n";
    }
    out << "========================================================================================\n";
    return out;
}
