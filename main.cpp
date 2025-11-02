#include <iostream>
#include <memory>
#include <map>
#include "headers/Artist.h"
#include "headers/Tablou.h"

int main() {
    // creare artist
    auto artist = std::make_shared<Artist>(
        "Ion", "Popescu", "Română", 45, 1978, 2007 , "Impresionism", 2025 ,
        "ionppescu", "ion@galerie.ro" );

    // creare tablou
    std::map<std::string,int> culori = {{"Albastru", 3}, {"Roșu", 2}};
    std::map<std::string,int> pensule = {{"Rotundă", 2}, {"Plat", 1}};
    auto tablou = std::make_shared<Tablou>(
        "Răsărit", "Ulei pe pânză", 2001, true, culori, pensule, std::make_pair(50,70), artist
    );

    // legare tablou la artist
    artist->adaugaTablou(tablou);

    // citire date suplimentare de la tastatură
    std::cout << "\nCompletează date suplimentare pentru artist:\n";
    std::cin >> *artist;

    std::cout << "\nCompletează date suplimentare pentru tablou:\n";
    std::cin >> *tablou;

    // afisare folosind operatorul <<
    std::cout << "\n--- Artist (implicit Complet) ---\n";
    std::cout << *artist;

    std::cout << "\n--- Tablou (implicit Complet) ---\n";
    std::cout << *tablou;

    // afisare folosind metodele statice
    std::cout << "\n--- Artist (Minimal) ---\n";
    Artist::afiseaza_artist(std::cout, *artist, NivelDetaliu::Minimal);

    std::cout << "\n--- Artist (Complet) ---\n";
    Artist::afiseaza_artist(std::cout, *artist, NivelDetaliu::Complet);

    std::cout << "\n--- Tablou (Minimal) ---\n";
    Tablou::afiseaza_tablou(std::cout, *tablou, NivelDetaliu::Minimal);

    std::cout << "\n--- Tablou (Complet) ---\n";
    Tablou::afiseaza_tablou(std::cout, *tablou, NivelDetaliu::Complet);

    // verificare metode utile
    std::cout << "\nNumăr tablouri ale artistului: " << artist->nrTablouri() << "\n";
    std::cout << "Număr tablouri colecționate: " << artist->nrTablouriColectionate() << "\n";
    std::cout << "Număr tablouri rare: " << artist->nrTablouriRare() << "\n";

    std::cout << "\nTitlu artist: " << artist->getTitlu() << "\n";
    std::cout << "Scor popularitate: " << artist->calculeaza_scor_stelute() << " ★\n";

    return 0;
}