
#ifndef ARTNOUVEAUGUEST_ARTIST_H
#define ARTNOUVEAUGUEST_ARTIST_H



#pragma once
#include "Tablou.h"
#include <string>
#include <iostream>
#include <vector>
#include <memory>


class Artist : public std::enable_shared_from_this<Artist>  {
private:
    const std::string nume;
    const std::string prenume;
    const std::string nationalitate;
    const int varsta;
    const int an_nastere;
    const int an_deces;
    std::string perioada_artistica;
    std::vector<std::string> imagini_artist;
    const int data_inscriere;
    std::string username;
    std::string email;
    std::vector<std::string> istoric;
    std::string pers_reprezentant;
    std::string username_reprezentant;
    std::string email_reprezentant;
    std::vector<std::string> istoric_reprezentant;
    std::vector<std::shared_ptr<Tablou>> tablouri;

public:
    Artist(const std::string& nume,
           const std::string& prenume,
           const std::string& nationalitate,
           int varsta,
           int an_nastere,
           int an_deces,
           const std::string& perioada_artistica,
           int data_inscriere = 0,
           const std::string& username = "",
           const std::string& email = "",
           const std::vector<std::string>& istoric = {},
           const std::string& pers_reprezentant = "",
           const std::string& username_reprezentant = "",
           const std::string& email_reprezentant = "",
           const std::vector<std::string>& istoric_reprezentant = {});
    ~Artist()= default;

    friend std::istream& operator>>(std::istream& in, Artist& a) {

        std::cout << "Perioadă artistică: ";
        std::getline(in, a.perioada_artistica);

        std::cout << "Username: ";
        std::getline(in, a.username);

        std::cout << "Email: ";
        std::getline(in, a.email);

        std::cout << "Număr de imagini: ";
        size_t n;
        in >> n;
        in.ignore();
        a.imagini_artist.clear();
        for (size_t i = 0; i < n; ++i) {
            std::string img;
            std::cout << "Imagine " << i+1 << ": ";
            std::getline(in, img);
            a.imagini_artist.push_back(img);
        }

        std::cout << "Număr de activități în istoric: ";
        in >> n;
        in.ignore();
        a.istoric.clear();
        for (size_t i = 0; i < n; ++i) {
            std::string act;
            std::cout << "Activitate " << i+1 << ": ";
            std::getline(in, act);
            a.istoric.push_back(act);
        }

        std::cout << "Persoană reprezentantă: ";
        std::getline(in, a.pers_reprezentant);
        std::cout << "Username reprezentant: ";
        std::getline(in, a.username_reprezentant);
        std::cout << "Email reprezentant: ";
        std::getline(in, a.email_reprezentant);

        std::cout << "Număr de activități ale reprezentantului: ";
        in >> n;
        in.ignore();
        a.istoric_reprezentant.clear();
        for (size_t i = 0; i < n; ++i) {
            std::string act;
            std::cout << "Activitate " << i+1 << ": ";
            std::getline(in, act);
            a.istoric_reprezentant.push_back(act);
        }

        return in;
    }

    friend std::ostream& operator<<(std::ostream& os, const Artist& artist);
    static std::ostream& afiseaza_artist(std::ostream& out, const Artist& a, NivelDetaliu nivel);
    void adaugaTablou(const std::shared_ptr<Tablou>& tablou);
    const std::vector<std::shared_ptr<Tablou>>& getTablouri() const;

    const std::string& getNume() const { return nume; }
    const std::string& getPrenume() const { return prenume; }
    const std::string& getNationalitate() const { return nationalitate; }
    int getVarsta() const { return varsta; }


    int nrTablouri() const;
    int nrTablouriColectionate() const;
    int nrTablouriRare() const;
    std::vector<std::shared_ptr<Tablou>> getTablouriRare() const;
    std::vector<std::shared_ptr<Tablou>> getTablouriColectionate() const;

    void afiseaza_profil_artist(NivelDetaliu nivel ) const;
    double calculeaza_scor_stelute()const;
    const std::string getTitlu() const;
    void setImagini(const std::vector<std::string>& imagini) {
        imagini_artist = imagini;
    }
    void setPerioadaArtistica(const std::string& perioada) { perioada_artistica = perioada; }
    const std::string getPerioadaArtistica() const { return perioada_artistica; }
    void afiseaza_imagini(NivelDetaliu nivel) const;
};



#endif //ARTNOUVEAUGUEST_ARTIST_H