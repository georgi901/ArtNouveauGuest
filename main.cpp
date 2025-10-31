#include "headers/Artist.h"
#include "headers/Tablou.h"
#include <iostream>
#include <vector>


int main() {
    std::vector<std::string> activitati_artist = {"Expoziție la Paris 2023", "Lansare colecție personală online"};
    std::vector<std::string> activitati_reprezentant = {"Restaurare tablou celebru", "Expoziție comemorativă la muzeu"};
    std::vector<std::string> poze_artist = {"profil_mucha.jpg", "premiu_expo_paris.jpg", "diploma_muzeu.jpg", "premiu_anual.jpg"};

    Artist a1("Alphonse", "Mucha", "Ceh", 79, 1860, 1939, "Art Nouveau", 12, 8, 3, 1900,
              "", "", {}, "Fundația Mucha", "", "", activitati_reprezentant);
    a1.setImagini(poze_artist);

    Artist a2("Luca", "Popescu", "Român", 35, 1989, 0, "Modernism Digital", 7, 3, 1, 2015,
              "lucap", "luca.popescu@gmail.com", activitati_artist);
    a2.setImagini({"profil_luca.jpg", "premiu_local.jpg"});

    std::cout << "\n=== Test bibliografie ===\n";
    a1.afiseaza_bibliografie();
    a2.afiseaza_bibliografie();

    std::cout << "\n=== Test profil ===\n";
    a1.afiseaza_informatii_artist();
    a2.afiseaza_informatii_artist();

    std::cout << "\n=== Test imagini ===\n";
    a1.afiseaza_imagini();
    a2.afiseaza_imagini();

    return 0;
}
