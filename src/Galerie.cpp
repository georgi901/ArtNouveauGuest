#include <iostream>
#include "../headers/Galerie.h"
#include "../headers/Artist.h"
#include "../headers/Tablou.h"
#include "../headers/Exceptii.h"
#include "../headers/ArtisticDelight.h"
#include "../headers/QuickArtLook.h"
#include "../headers/ArtQuiz.h"
#include <nlohmann/json.hpp>
#include <fstream>

using json = nlohmann::json;

void Galerie::incarcaArtistiDinFisier(const std::string &caleFisier) {

    std::ifstream fin(caleFisier);

    if (!fin.is_open()) {
        throw IncarcareDataException(caleFisier, "fisier");
    }
    json data;
    try {
        fin >> data;
    } catch (const json::parse_error &e) {
        throw IncarcareDataException(caleFisier, "parsare");
    }

    for (const auto &artistJson: data) {
        std::string nume = artistJson["nume"];
        std::string prenume = artistJson["prenume"];
        std::string nationalitate = artistJson["nationalitate"];
        int varsta = artistJson["varsta"];
        int anNastere = artistJson["an_nastere"];
        int anDeces = artistJson["an_deces"];
        std::string perioada = artistJson["perioada"];
        std::string dataInscriere = artistJson["data_inscriere"];

        //date pentru artist în viață
        std::string username = "";
        std::string email = "";
        if (artistJson.contains("username")) {
            username = artistJson["username"];
        }
        if (artistJson.contains("email")) {
            email = artistJson["email"];
        }

        //date reprezentant (pentru artiști decedați)
        std::string persReprezentant = "";
        std::string usernameRepr = "";
        std::string emailRepr = "";
        if (artistJson.contains("reprezentant")) {
            persReprezentant = artistJson["reprezentant"]["nume"];
            usernameRepr = artistJson["reprezentant"]["username"];
            emailRepr = artistJson["reprezentant"]["email"];
        }

        auto artist = std::make_shared<Artist>(
            nume, prenume, nationalitate, varsta, anNastere, anDeces,
            perioada, dataInscriere,
            username, email, std::vector<std::string>{},
            persReprezentant, usernameRepr, emailRepr,
            std::vector<std::string>{}
        );

        //imagini
        if (artistJson.contains("imagini")) {
            for (const auto &img: artistJson["imagini"]) {
                artist->adaugaImagine(img);
            }
        }

        adaugaArtist(artist);
    }

    fin.close();
}


void Galerie::incarcaTablouriDinFisier(const std::string& caleFisier) {
    std::ifstream fin(caleFisier);

    if (!fin.is_open()) {
        throw IncarcareDataException(caleFisier, "fisier");
    }

    json data;
    try {
        fin >> data;
    } catch (const json::parse_error& e) {
        throw IncarcareDataException(caleFisier, "parsare");
    }
    for (const auto& tablouJson : data) {
        std::string titlu = tablouJson["titlu"];
        std::string tehnica = tablouJson["tehnica"];
        int anRealizare = tablouJson["an_realizare"];
        bool rar = tablouJson["rar"];
        bool colectionat = tablouJson["colectionat"];

        //dimensiune (array de 2 elemente)
        int dimX = tablouJson["dimensiune"][0];
        int dimY = tablouJson["dimensiune"][1];

        //găsește artistul
        std::string numeArtist = tablouJson["artist"];
        auto artist = cautaArtist(numeArtist);

        //map-urile de culori și pensule
        std::map<std::string, int> culori;
        if (tablouJson.contains("culori")) {
            for (auto& [cheie, valoare] : tablouJson["culori"].items()) {
                culori[cheie] = valoare;
            }
        }

        std::map<std::string, int> pensule;
        if (tablouJson.contains("pensule")) {
            for (auto& [cheie, valoare] : tablouJson["pensule"].items()) {
                pensule[cheie] = valoare;
            }
        }

        auto tablou = std::make_shared<Tablou>(
            titlu, tehnica, anRealizare, rar,
            culori, pensule,
            std::make_pair(dimX, dimY),
            artist,
            colectionat
        );

        //imagini
        if (tablouJson.contains("imagini")) {
            for (const auto& img : tablouJson["imagini"]) {
                tablou->adaugaImagine(img);
            }
        }

        adaugaTablou(tablou);

        if (artist) {
            artist->adaugaTablou(tablou);
        }
    }

    fin.close();
}
std::shared_ptr<MiniJoc> Galerie::cautaJoc(const std::string& nume) const {
    for (const auto& joc : jocuri) {
        if (joc->getNume() == nume) {
            return joc;
        }
    }
    return nullptr;
}

void Galerie::afiseazaJocuri() const {
    std::cout << "\n==================== JOCURI DISPONIBILE ====================\n";
    if (jocuri.empty()) {
        std::cout << "Nu există jocuri disponibile.\n";
        return;
    }

    for (size_t i = 0; i < jocuri.size(); i++) {
        std::cout << i + 1 << ". " << *jocuri[i] << "\n";
    }
    std::cout << "=============================================================\n";
}

void Galerie::joacaJoc(const std::string& nume_joc) {
    auto joc = cautaJoc(nume_joc);
    if (!joc) {
        throw JocInvalidException(nume_joc);
    }

    joc->afiseazaRegulile();
    joc->initializeaza();
}


void Galerie::afiseazaSugestiiArtisticDelight() {
    std::cout << "\n=== SUGESTII PENTRU ARTISTIC DELIGHT ===\n";

    for (const auto& joc : jocuri) {

        if (auto ad = std::dynamic_pointer_cast<ArtisticDelight>(joc)) {
            std::cout << "Joc: " << ad->getNume() << "\n";
            ad->arataSugestie();
        }
    }
}


Galerie::Galerie(const Galerie& other)
    : nume(other.nume),
      subiect(other.subiect),
      an_infiintare(other.an_infiintare),
      artisti(other.artisti),
      tablouri(other.tablouri),
      jocuri(other.jocuri)
{
    std::cout << "[Copy constructor] Galerie: " << nume << "\n";
}


void swap(Galerie& first, Galerie& second) noexcept {
    using std::swap;
    swap(first.nume, second.nume);
    swap(first.subiect, second.subiect);
    swap(first.an_infiintare, second.an_infiintare);
    swap(first.artisti, second.artisti);
    swap(first.tablouri, second.tablouri);
    swap(first.jocuri, second.jocuri);
}


Galerie& Galerie::operator=(Galerie other) {
    std::cout << "[Copy-and-swap] Galerie operator=\n";
    swap(*this, other);
    return *this;
}

void Galerie::afiseazaArtisti() const {
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
