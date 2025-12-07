#include "../headers/ArtisticDelight.h"
#include <iostream>
#include <algorithm>
#include <cmath>


ArtisticDelight::ArtisticDelight(const std::string& nume, Dificultate dif)
    : MiniJoc(nume, "Recreează tabloul folosind culorile potrivite!", dif),
      tablou_tinta(nullptr),
      scor_asemanare(0.0),
      incercari_ramase(0)
{

    switch(dif) {
        case Dificultate::Usor:  incercari_ramase = 10; break;
        case Dificultate::Mediu: incercari_ramase = 7; break;
        case Dificultate::Greu:  incercari_ramase = 5; break;
    }

    std::cout << "ArtisticDelight constructor: " << nume << std::endl;
}


ArtisticDelight::ArtisticDelight(const ArtisticDelight& other)
    : MiniJoc(other),
      tablou_tinta(other.tablou_tinta),
      scor_asemanare(other.scor_asemanare),
      culori_folosite(other.culori_folosite),
      incercari_ramase(other.incercari_ramase)
{
    std::cout << " ArtisticDelight copy constructor" << std::endl;
}


std::unique_ptr<MiniJoc> ArtisticDelight::clone() const {
    return std::make_unique<ArtisticDelight>(*this);
}


std::string ArtisticDelight::getTipJoc() const {
    return "Artistic Delight";
}


void ArtisticDelight::seteazaTablou(std::shared_ptr<Tablou> tablou) {
    tablou_tinta = tablou;
    std::cout << "Tablou setat: " << tablou->getTitlu() << std::endl;
}


void ArtisticDelight::picteaza(const std::string& culoare) {
    if (incercari_ramase <= 0) {
        std::cout << "Nu mai ai încercări rămase!" << std::endl;
        return;
    }

    culori_folosite.push_back(culoare);
    incercari_ramase--;

    std::cout << "Ai folosit culoarea: " << culoare << std::endl;
    std::cout << "Încercări rămase: " << incercari_ramase << std::endl;

    evalueazaAsemanare();
}

double ArtisticDelight::evalueazaAsemanare() {
    if (!tablou_tinta) {
        scor_asemanare = 0.0;
        return scor_asemanare;
    }

    const auto& culori_originale = tablou_tinta->getCulori();

    if (culori_originale.empty()) {
        scor_asemanare = 0.0;
        return scor_asemanare;
    }

    int culori_corecte = 0;
    for (const auto& culoare : culori_folosite) {
        if (culori_originale.find(culoare) != culori_originale.end()) {
            culori_corecte++;
        }
    }


    double procent_ghicite = static_cast<double>(culori_corecte) / culori_originale.size() * 100.0;


    int culori_gresite = culori_folosite.size() - culori_corecte;
    double penalizare = culori_gresite * 5.0;

    scor_asemanare = std::max(0.0, std::min(100.0, procent_ghicite - penalizare));

    std::cout << "Scor asemănare: " << scor_asemanare << "%" << std::endl;

    return scor_asemanare;
}


void ArtisticDelight::arataSugestie() const {
    if (!tablou_tinta) {
        std::cout << "Nu este setat niciun tablou!" << std::endl;
        return;
    }

    const auto& culori_originale = tablou_tinta->getCulori();

    if (culori_originale.empty()) {
        std::cout << "Tabloul nu are culori definite." << std::endl;
        return;
    }


    for (const auto& [culoare, _] : culori_originale) {
        bool gasita = false;
        for (const auto& c : culori_folosite) {
            if (c == culoare) {
                gasita = true;
                break;
            }
        }
        if (!gasita) {
            std::cout << "Sugestie: Încearcă culoarea care începe cu '"
                      << culoare[0] << "'..." << std::endl;
            return;
        }
    }

    std::cout << "Ai găsit toate culorile!" << std::endl;
}



void ArtisticDelight::initializeaza_implementare() {
    scor_asemanare = 0.0;
    culori_folosite.clear();


    switch(dificultate) {
        case Dificultate::Usor:  incercari_ramase = 10; break;
        case Dificultate::Mediu: incercari_ramase = 7; break;
        case Dificultate::Greu:  incercari_ramase = 5; break;
    }

    std::cout << "Artistic Delight inițializat!" << std::endl;
    std::cout << "Încercări disponibile: " << incercari_ramase << std::endl;

    if (tablou_tinta) {
        std::cout << "Tablou de recreat: " << tablou_tinta->getTitlu() << std::endl;
    }
}

int ArtisticDelight::calculeaza_puncte_implementare() {
    int puncte = static_cast<int>((scor_asemanare / 100.0) * puncte_maxime);

    int bonus = incercari_ramase * 5;
    int total = puncte + bonus;

    std::cout << "Scor asemanare: " << scor_asemanare << "%" << std::endl;
    std::cout << "Puncte baza: " << puncte << std::endl;
    std::cout << "Bonus incercari ramase (" << incercari_ramase << " incercari): +" << bonus << std::endl;
    std::cout << "Total: " << total << std::endl;

    return total;
}

void ArtisticDelight::afiseaza_reguli_implementare() const {
    std::cout << "ARTISTIC DELIGHT - Reguli:" << std::endl;
    std::cout << "1. Ți se va arăta un tablou celebru." << std::endl;
    std::cout << "2. Trebuie să ghicești culorile folosite în tablou." << std::endl;
    std::cout << "3. Scrie numele culorilor una câte una." << std::endl;
    std::cout << "4. Cu cât ghicești mai multe culori, cu atât scorul e mai mare." << std::endl;
    std::cout << "5. Ai un număr limitat de încercări!" << std::endl;
    std::cout << "Încercări disponibile: " << incercari_ramase << std::endl;
}