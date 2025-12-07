#include "../headers/ArtPuzzle.h"
#include <iostream>
#include <algorithm>
#include <random>

ArtPuzzle::ArtPuzzle(const std::string& nume, Dificultate dif)
    : MiniJoc(nume, "Aranjează fragmentele tabloului în ordinea corectă", dif),
      tablou_tinta(nullptr),
      numar_fragmente(0),
      mutari_efectuate(0),
      mutari_maxime(0),
      rezolvat(false)
{
    // Setează numărul de fragmente și mutări maxime în funcție de dificultate
    switch(dif) {
        case Dificultate::Usor:
            numar_fragmente = 4;   // 2x2
            mutari_maxime = 6;
            break;
        case Dificultate::Mediu:
            numar_fragmente = 9;   // 3x3
            mutari_maxime = 14;
            break;
        case Dificultate::Greu:
            numar_fragmente = 16;  // 4x4
            mutari_maxime = 22;
            break;
    }


    for (int i = 0; i < numar_fragmente; i++) {
        ordine_corecta.push_back(i);
        ordine_fragmente.push_back(i);
    }

    std::cout << "ArtPuzzle constructor: " << nume << "\n";
}

ArtPuzzle::ArtPuzzle(const ArtPuzzle& other)
    : MiniJoc(other),
      tablou_tinta(other.tablou_tinta),
      ordine_fragmente(other.ordine_fragmente),
      ordine_corecta(other.ordine_corecta),
      numar_fragmente(other.numar_fragmente),
      mutari_efectuate(other.mutari_efectuate),
      mutari_maxime(other.mutari_maxime),
      rezolvat(other.rezolvat)
{
    std::cout << "ArtPuzzle copy constructor\n";
}

ArtPuzzle::~ArtPuzzle() {
    std::cout << "ArtPuzzle destructor: " << getNume() << "\n";
}

void ArtPuzzle::seteazaTablou(std::shared_ptr<Tablou> tablou) {
    tablou_tinta = tablou;
    if (tablou) {
        std::cout << "Puzzle setat pentru tabloul: " << tablou->getTitlu() << "\n";
    }
}

void ArtPuzzle::amestecaFragmente() {
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(ordine_fragmente.begin(), ordine_fragmente.end(), g);
    rezolvat = false;
    std::cout << "Fragmentele au fost amestecate!\n";
}

bool ArtPuzzle::mutaFragment(int pozitie1, int pozitie2) {
    if (pozitie1 < 0 || pozitie1 >= numar_fragmente ||
        pozitie2 < 0 || pozitie2 >= numar_fragmente) {
        std::cout << "Poziții invalide!\n";
        return false;
    }

    if (mutari_efectuate >= mutari_maxime) {
        std::cout << "Ai epuizat toate mutările!\n";
        return false;
    }

    std::swap(ordine_fragmente[pozitie1], ordine_fragmente[pozitie2]);
    mutari_efectuate++;


    rezolvat = (ordine_fragmente == ordine_corecta);

    return true;
}

bool ArtPuzzle::esteRezolvat() const {
    return rezolvat;
}

void ArtPuzzle::afiseazaPuzzle() const {
    std::cout << "\n=== PUZZLE: ";
    if (tablou_tinta) {
        std::cout << tablou_tinta->getTitlu();
    }
    std::cout << " ===\n";

    int dim = (numar_fragmente == 4) ? 2 : (numar_fragmente == 9) ? 3 : 4;

    for (int i = 0; i < numar_fragmente; i++) {
        std::cout << "[" << ordine_fragmente[i] << "] ";
        if ((i + 1) % dim == 0) {
            std::cout << "\n";
        }
    }

    std::cout << "Mutări: " << mutari_efectuate << "/" << mutari_maxime << "\n";
}

void ArtPuzzle::initializeaza_implementare() {
    mutari_efectuate = 0;
    rezolvat = false;


    ordine_fragmente.clear();
    for (int i = 0; i < numar_fragmente; i++) {
        ordine_fragmente.push_back(i);
    }

    amestecaFragmente();
    std::cout << "Puzzle inițializat cu " << numar_fragmente << " fragmente.\n";
}

int ArtPuzzle::calculeaza_puncte_implementare() {

        if (!rezolvat) {
            return 0;
        }

        int puncte_baza = puncte_maxime;

        int mutari_ramase = mutari_maxime - mutari_efectuate;
        int bonus = (mutari_ramase * puncte_maxime) / (mutari_maxime * 2);

        std::cout << "Puncte bază: " << puncte_baza << "\n";
        std::cout << "Bonus mutări rămase (" << mutari_ramase << " mutări): +" << bonus << "\n";

        return puncte_baza + bonus;

}

void ArtPuzzle::afiseaza_reguli_implementare() const {
    std::cout << "\n==========================================\n";
    std::cout << "         REGULI ART PUZZLE                  \n";
    std::cout << "============================================\n";
    std::cout << "  1. Aranjează fragmentele în ordine        \n";
    std::cout << "  2. Schimbă poziția a două fragmente       \n";
    std::cout << "  3. Ordinea corectă: 0,1,2,3...            \n";
    std::cout << "  4. Ai un număr limitat de mutări          \n";
    std::cout << "============================================\n";
    std::cout << "  Fragmente: " << numar_fragmente << "      \n";
    std::cout << "  Mutări maxime: " << mutari_maxime << "    \n";
    std::cout << "============================================\n";
}

std::unique_ptr<MiniJoc> ArtPuzzle::clone() const {
    return std::make_unique<ArtPuzzle>(*this);
}

std::string ArtPuzzle::getTipJoc() const {
    return "ArtPuzzle";
}