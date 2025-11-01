#include "../headers/Artist.h"
#include "../headers/Tablou.h"
#include <iostream>
#include <vector>


Artist::Artist(const std::string& nume,
               const std::string& prenume,
               const std::string& nationalitate,
               int varsta,
               int an_nastere,
               int an_deces,
               const std::string& perioada_artistica,
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
      data_inscriere(data_inscriere),
      username(username),
      email(email),
      istoric(istoric),
      pers_reprezentant(pers_reprezentant),
      username_reprezentant(username_reprezentant),
      email_reprezentant(email_reprezentant),
      istoric_reprezentant(istoric_reprezentant)
{}



void Artist::adaugaTablou(const std::shared_ptr<Tablou>& tablou) {
    tablouri.push_back(tablou);
    tablou->setArtist(shared_from_this());
}

const std::vector<std::shared_ptr<Tablou>>& Artist::getTablouri() const {
    return tablouri;
}

int Artist::nrTablouri() const { return static_cast<int>(tablouri.size()); }

int Artist::nrTablouriColectionate() const {
    int count = 0;
    for (auto& t : tablouri) if (t->este_colectionat()) count++;
    return count;
}

int Artist::nrTablouriRare() const {
    int count = 0;
    for (auto& t : tablouri) if (t->este_rar()) count++;
    return count;
}

std::vector<std::shared_ptr<Tablou>> Artist::getTablouriRare() const {
    std::vector<std::shared_ptr<Tablou>> rez;
    for(auto& t : tablouri) if(t->este_rar()) rez.push_back(t);
    return rez;
}

std::vector<std::shared_ptr<Tablou>> Artist::getTablouriColectionate() const {
    std::vector<std::shared_ptr<Tablou>> rez;
    for(auto& t : tablouri) if(t->este_colectionat()) rez.push_back(t);
    return rez;
}

double Artist::calculeaza_scor_stelute() const {
    int total = nrTablouri();
    if (total == 0) return 0.0;

    int colectate = nrTablouriColectionate();
    int rare = nrTablouriRare();

    double scor_baza = static_cast<double>(colectate) / total;
    double raritate = (rare > 0) ? 0.5 : 0.0;
    double scor_final = std::min(5.0, scor_baza * 4 + raritate);

    return static_cast<int>(std::round(scor_final));
}

std::string Artist::getTitlu() const {
    double scor = calculeaza_scor_stelute();
    if(scor < 1) return "Novice";
    else if(scor < 2) return "Aspirant";
    else if(scor < 3) return "Talentat";
    else if(scor < 4) return "Expert";
    else return "Maestru";
}

void Tablou::afiseaza_imagini(NivelDetaliu nivel) const {
    if(imagini_tablou.empty()) {
        std::cout << "Nu există imagini pentru acest artist.\n";
        return;
    }

    if(nivel == NivelDetaliu::Minimal) {
        std::cout << "Poză cu artistul: " << imagini_tablou[0] << "\n";
    }
    else if(nivel == NivelDetaliu::Complet) {
        std::cout << "Imagini cu artistul:\n";
        for(size_t i = 0; i < imagini_tablou.size(); ++i) {
            std::cout << "  " << imagini_tablou[i] << "\n";
        }
    }
}

void Artist::afiseaza_profil_artist(NivelDetaliu nivel) const {
    std::cout << "--- PROFIL ARTIST ---\n";
    std::cout << "Nume complet: " << nume << " " << prenume << "\n";
    std::cout << "Naționalitate: " << nationalitate << "\n";

    if (nivel == NivelDetaliu::Minimal) {
        std::cout << "Perioadă artistică: " << perioada_artistica << "\n";
        std::cout << "Artistul a evoluat în cadrul acestei perioade prin explorarea stilurilor și tehnicilor specifice.\n";
        std::cout << "Status: ";
        if (an_deces == 0) {
            std::cout << "În viață (" << varsta << " ani)\n";
            std::cout << "Are un profil activ.\n";
        }
        else {
            std::cout << "Decedat (" << an_nastere << " - " << an_deces << ")\n";
            std::cout << "Tablourile din galerie au fost adăugate de către un reprezentant: " << pers_reprezentant << "\n";
        }
        std::cout << "\n---- IMAGINE ARTIST ----\n";
        afiseaza_imagini(nivel);
        return;
    }

    if (an_deces == 0) {
        std::cout << "Status: ";
        std::cout << "În viață (" << varsta << " ani)\n";
        std::cout << "Are un profil activ.\n";
        std::cout << nume << " s-a născut în " << an_nastere << " și este încă în viață.\n";
        std::cout << "  • Username: " << username << "\n";
        std::cout << "  • Email: " << email << "\n";
        if (!istoric.empty()) {
            std::cout << "  • Istoric activități:\n"; // vreau sa leg cumva de activitatile pe care le efectueaza in galerie
            for (const auto& act : istoric)
                std::cout << "    - " << act << "\n";
        }
    } else {
        std::cout << "Status: ";
        std::cout << "Decedat (" << an_nastere << " - " << an_deces << ")\n";
        std::cout << "Tablourile din galerie au fost adăugate de către un reprezentant: " << pers_reprezentant << "\n";
        std::cout << nume << " a trăit între " << an_nastere << " și " << an_deces << ".\n";
        if (!pers_reprezentant.empty()) {
            std::cout << "Persoană reprezentantă: " << pers_reprezentant << "\n";
            std::cout << "Username: " << username_reprezentant << "\n";
            std::cout << "Email: " << email_reprezentant << "\n";
        }
        if (!istoric_reprezentant.empty()) {
            std::cout << "Istoric activități reprezentant:\n";// la fel
            for (const auto& act : istoric_reprezentant)
                std::cout << "    - " << act << "\n";
        }
    }
    std::cout << "Perioadă artistică: " << perioada_artistica << "\n";
    std::cout << "Artistul a evoluat în cadrul acestei perioade prin explorarea stilurilor și tehnicilor specifice.\n";

    std::cout << "\n------ GALERIE ȘI POPULARITATE ------\n";
    std::cout << "Total tablouri: " << nrTablouri() << "\n";
    std::cout << "Tablouri colecționate: " << nrTablouriColectionate() << "\n";
    std::cout << "Tablouri rare: " << nrTablouriRare() << "\n";
    std::cout << "Data înscrierii în galerie: " << data_inscriere << "\n";

    double scor = calculeaza_scor_stelute();
    std::cout << "Scor popularitate: " << scor << " ★\n";
    std::cout << "Titlu atribuit: " << getTitlu() << "\n";

    std::cout << "\n---- IMAGINI ARTIST ----\n";
    afiseaza_imagini(nivel);

    std::cout << "------------------------------------\n";
    if (!tablouri.empty()) {
        std::cout << "\n--- TABLOURI ALE ARTISTULUI ---\n";
        for (const auto& t : tablouri) {
            t->afiseaza_imagini(nivel);
        }
    }
}


