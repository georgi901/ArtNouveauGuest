/**
 * @file Galerie.h
 * @brief Definește clasa Galerie folosind design pattern-ul Singleton.
 *
 * Acest fișier implementează design pattern-ul Singleton pentru clasa Galerie,
 * asigurând că există o singură instanță a galeriei pe durata aplicației.
 * Acesta este unul din cele două pattern-uri cerute pentru Milestone 3.
 */

#ifndef ARTNOUVEAUGUEST_GALERIE_H
#define ARTNOUVEAUGUEST_GALERIE_H
#pragma once
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "Artist.h"
#include "MiniJoc.h"
#include "Tablou.h"

/**
 * @class Galerie
 * @brief Clasă Singleton pentru gestionarea galeriei de artă.
 *
 * Implementează design pattern-ul Singleton pentru a asigura că există
 * o singură instanță a galeriei pe durata aplicației. Gestionează
 * colecții de artiști, tablouri și mini-jocuri.
 *
 * @note Această clasă poate fi folosită în două moduri:
 *       1. Ca Singleton prin getInstance() - recomandat pentru producție
 *       2. Cu constructori normali - util pentru testare
 *
 * Beneficiile pattern-ului Singleton pentru Galerie:
 * - Asigură consistența datelor (sursă unică de adevăr)
 * - Punct de acces global pentru operațiile galeriei
 * - Inițializare leneșă (creată doar când e nevoie)
 *
 * @code
 * // Folosind Singleton
 * Galerie& galerie = Galerie::getInstance();
 * galerie.adaugaArtist(artist);
 *
 * // Folosind constructor normal (pentru testare)
 * Galerie galerieTest("Galerie Test", "Testare", 2024);
 * @endcode
 */

class Galerie {
private:
    std::string nume;
    std::string subiect;
    int an_infiintare;
    std::vector<std::shared_ptr<Artist>> artisti;
    std::vector<std::shared_ptr<Tablou>> tablouri;
    std::vector<std::shared_ptr<MiniJoc>> jocuri;

public:
    // ==================== SINGLETON ====================
    /**
     * @brief Obține instanța singleton a galeriei.
     * @return Referință către unica instanță Galerie.
     *
     * Implementare thread-safe folosind pattern-ul "Meyer's Singleton".
     * Instanța este creată la primul apel și distrusă la ieșirea din program.
     */
    static Galerie& getInstance();

    // ==================== CONSTRUCTORI ====================
    Galerie() : an_infiintare(0) {
    }
    Galerie(const std::string& n, const std::string& subj, int an) : nume(n), subiect(subj), an_infiintare(an) {
    }
    ~Galerie() = default;

    // ==================== GESTIONARE TABLOURI ====================
    void adaugaTablou(const std::shared_ptr<Tablou>& t) {
        tablouri.push_back(t);
    }

    void incarcaArtistiDinFisier(const std::string& caleFisier);
    void incarcaTablouriDinFisier(const std::string& caleFisier);

    void afiseazaArtisti() const;
    void afiseazaTablouri() const;
    std::shared_ptr<Artist> cautaArtist(const std::string& nume_cautat) const;
    void adaugaArtist(const std::shared_ptr<Artist>& a) {
        artisti.push_back(a);
    }
    std::shared_ptr<Tablou> cautaTablou(const std::string& titlu) const;
    friend std::ostream& operator<<(std::ostream& out, const Galerie& g);
    friend std::istream& operator>>(std::istream& in, Galerie& g) {
        std::cout << "Nume galerie: ";
        in >> g.nume;
        std::cout << "Locatie: ";
        in >> g.subiect;
        std::cout << "An infiintare: ";
        in >> g.an_infiintare;
        return in;
    }

    // ==================== GESTIONARE JOCURI ====================
    void adaugaJoc(const std::shared_ptr<MiniJoc>& joc) {
        jocuri.push_back(joc);
    }
    std::shared_ptr<MiniJoc> cautaJoc(const std::string& nume_joc) const;
    void afiseazaJocuri() const;
    void joacaJoc(const std::string& nume_joc);
    void afiseazaSugestiiArtisticDelight();

    // ==================== GETTERI ====================
    const std::vector<std::shared_ptr<Tablou>>& getTablouri() const {
        return tablouri;
    }
    const std::vector<std::shared_ptr<Artist>>& getArtisti() const {
        return artisti;
    }
    const std::vector<std::shared_ptr<MiniJoc>>& getJocuri() const {
        return jocuri;
    }

    // ==================== COPY-AND-SWAP ====================
    Galerie(const Galerie& other);
    Galerie& operator=(Galerie other);
    friend void swap(Galerie& first, Galerie& second) noexcept;
};

#endif  // ARTNOUVEAUGUEST_GALERIE_H