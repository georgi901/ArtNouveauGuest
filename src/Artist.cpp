#include "../headers/Artist.h"
#include <iostream>
#include <vector>


Artist::Artist(const std::string& nume,
               const std::string& prenume,
               const std::string& nationalitate,
               int varsta,
               int an_nastere,
               int an_deces,
               const std::string& perioada_artistica,
               int nr_tablouri,
               int nr_tablouri_colectionate,
               int nr_tablouri_rare,
               int data_inscriere,
               const std::string& username,
               const std::string& email,
               const std::vector<std::string>& istoric,
               const std::string& pers_reprezentant,
               const std::string& username_reprezentant,
               const std::string& email_reprezentant,
               const std::vector<std::string>& istoric_reprezentant)
    : nume(nume),
      prenume(prenume),
      nationalitate(nationalitate),
      varsta(varsta),
      an_nastere(an_nastere),
      an_deces(an_deces),
      perioada_artistica(perioada_artistica),
      nr_tablouri(nr_tablouri),
      nr_tablouri_colectionate(nr_tablouri_colectionate),
      nr_tablouri_rare(nr_tablouri_rare),
      data_inscriere(data_inscriere),
      username(username),
      email(email),
      istoric(istoric),
      pers_reprezentant(pers_reprezentant),
      username_reprezentant(username_reprezentant),
      email_reprezentant(email_reprezentant),
      istoric_reprezentant(istoric_reprezentant)
{}

Artist::~Artist() = default;

void Artist::afiseaza_bibliografie() const {
    std::string raspuns, titlu;
    double scor;

    std::cout << " Biografie:\n";
    std::cout << nume << " " << prenume << ", " << nationalitate << ", ";
    if (an_deces <= 0)
        std::cout << "născut în " << an_nastere << ", încă trăiește.\n";
    else
        std::cout << "a trăit între " << an_nastere << " și " << an_deces << ".\n";

    std::cout << "Vrei să citești mai mult? (da/nu): ";
    std::cin >> raspuns;
    if (raspuns != "da") return;

    std::cout << "\n Perioada artistică:\n";
    std::cout << "Această perioadă este: " << perioada_artistica << ".\n";
    std::cout << "Artistul a evoluat în cadrul acestei perioade prin explorarea stilurilor și tehnicilor specifice.\n";

    std::cout << "Vrei să citești mai mult? (da/nu): ";
    std::cin >> raspuns;
    if (raspuns != "da") return;

    std::cout << "\n Galerie și popularitate:\n";
    std::cout << "Număr total de tablouri în galerie: " << nr_tablouri << "\n";
    std::cout << "Număr de tablouri colectate de utilizatori: " << nr_tablouri_colectionate << "\n";
    std::cout << "Număr tablouri rare: " << nr_tablouri_rare << "\n";
    std::cout << "Data înscrierii în galerie: " << data_inscriere << "\n";

    scor = calculeaza_scor_stelute();
    std::cout << "Popularitatea artistului: " << scor << " ★\n";

    if (scor < 1) titlu = "Novice";
    else if (scor < 2) titlu = "Aspirant";
    else if (scor < 3) titlu = "Talentat";
    else if (scor < 4) titlu = "Expert";
    else titlu = "Maestru";

    std::cout << "Titlu atribuit: " << titlu << "\n";
}


void Artist::afiseaza_informatii_artist() const {
    std::cout << "=== PROFIL ARTIST ===\n";
    std::cout << "Nume complet: " << nume << " " << prenume << "\n";
    std::cout << "Naționalitate: " << nationalitate << "\n";
    std::cout << "Perioadă artistică: " << perioada_artistica << "\n";

    if (an_deces == 0) {
        std::cout << "\nStatus: În viață (" << varsta << " ani)\n";
        std::cout << "Profil activ:\n";
        std::cout << "  • Username: " << username << "\n";
        std::cout << "  • Email: " << email << "\n";
        std::cout << "  • Istoric activități:\n";
        for (const auto& activitate : istoric)
            std::cout << "    - " << activitate << "\n";
    } else {
        std::cout << "\nStatus: Decedat (" << an_nastere << " - " << an_deces << ")\n";
        std::cout << "Tablourile din galerie au fost adăugate de către: " << pers_reprezentant << "\n";
        std::cout << "Email contact: " << email_reprezentant << "\n";
        std::cout << "Istoric activități:\n";
        for (const auto& activitate : istoric_reprezentant)
            std::cout << "    - " << activitate << "\n";
    }

    std::cout << "\nTotal tablouri încărcate: " << nr_tablouri
              << " | Tablouri colecționate: " << nr_tablouri_colectionate << "\n";
    std::cout << "Scor popularitate: " << calculeaza_scor_stelute() << " ★\n";
}

double Artist::calculeaza_scor_stelute() const {
    if (nr_tablouri == 0) return 0.0;
    double scor_baza = static_cast<double>(nr_tablouri_colectionate) / nr_tablouri;
    double raritate = (nr_tablouri_rare > 0) ? 0.5 : 0.0;
    return std::min(5.0, scor_baza * 4 + raritate);
}

void Artist::afiseaza_imagini() const {
    if (imagini_artist.empty()) {
        std::cout << "Nu există imagini pentru acest artist.\n";
        return;
    }

    std::string raspuns;

    std::cout << " Poză cu artistul " << nume << "\n";
    std::cout << imagini_artist[0] << "\n";
    if (imagini_artist.size() > 1) {
        std::cout << "Te interesează și pozele cu premiile și diplomele artistului? (da/nu): ";
        std::cin >> raspuns;
        if (raspuns != "da") return;

        for (size_t i = 1; i < imagini_artist.size() && i <= 3; ++i) {
            std::cout << imagini_artist[i] << "\n";
        }
    }
}
