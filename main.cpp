#include <iostream>
#include <memory>
#include <map>
#include "headers/Artist.h"
#include "headers/Tablou.h"

int main() {
    // artist
    auto artist = std::make_shared<Artist>(
        "Ion", "Popescu", "Română", 45, 1978, 0, "Art Nouveau", 2025, "ionpopescu", "ion@email.com"
    );
    // imagini
    artist->setImagini({"ion1.jpg", "ion2.jpg", "ion3.jpg"});
    // tablou
    std::map<std::string,int> culori = { {"roșu", 3}, {"albastru", 2}, {"galben", 1} };
    std::map<std::string,int> pensule = { {"rotundă", 2}, {"plată", 1} };
    std::pair<int,int> dimensiune = { 60, 80 }; // 60x80 cm

    auto tablou = std::make_shared<Tablou>(
        "Floarea Soarelui",
        "Ulei pe pânză",
        2020,
        true, // rar
        culori,
        pensule,
        dimensiune,
        artist
    );

    // tablou - artist
    artist->adaugaTablou(tablou);

    // profilul artistului - minimal
    std::cout << "\n---- PROFIL ARTIST - Detalii Minimale ----\n";
    artist->afiseaza_profil_artist(NivelDetaliu::Minimal);

    // profilul artistului - complet
    std::cout << "\n---- PROFIL ARTIST - Detalii Complete ----\n";
    artist->afiseaza_profil_artist(NivelDetaliu::Complet);

    // detalii tablou - minimal
    std::cout << "\n---- TABLOU - Detalii Minimale ----\n";
    tablou->afiseaza_tablou_zoom(NivelDetaliu::Minimal);

    // detalii tabloul - complet
    std::cout << "\n---- TABLOU - Detalii Complete ----\n";
    tablou->afiseaza_tablou_zoom(NivelDetaliu::Complet);

    return 0;
}
