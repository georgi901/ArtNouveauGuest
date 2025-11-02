
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
    const std::string data_inscriere;
    std::string username;
    std::string email;
    std::vector<std::string> istoric;
    std::string pers_reprezentant;
    std::string username_reprezentant;
    std::string email_reprezentant;
    std::vector<std::string> istoric_reprezentant;
    std::vector<std::shared_ptr<Tablou>> tablouri;
    static std::vector<std::shared_ptr<Artist>> lista_artistilor;

public:
    Artist()
       : nume("Necunoscut"),
         prenume("Necunoscut"),
         nationalitate("Necunoscut"),
         varsta(0),
         an_nastere(0),
         an_deces(0),
         perioada_artistica("Necunoscută"),
         data_inscriere("Necunoscut"){}
    Artist(const std::string& nume,
           const std::string& prenume,
           const std::string& nationalitate,
           int varsta,
           int an_nastere,
           int an_deces,
           const std::string& perioada_artistica,
           const std::string& data_inscriere = "",
           const std::string& username = "",
           const std::string& email = "",
           const std::vector<std::string>& istoric = {},
           const std::string& pers_reprezentant = "",
           const std::string& username_reprezentant = "",
           const std::string& email_reprezentant = "",
           const std::vector<std::string>& istoric_reprezentant = {}
           );
    ~Artist()= default;
    static const std::vector<std::shared_ptr<Artist>>& getListaArtistilor() {
        return lista_artistilor;
    }
    friend std::ostream& operator<<(std::ostream& os, const Artist& artist);
    static std::ostream& afiseaza_artist(std::ostream& out, const Artist& a, NivelDetaliu nivel);


    void adaugaTablou(const std::shared_ptr<Tablou>& tablou);
    void adaugaImagine(const std::string& cale_imagine) {
        imagini_artist.push_back(cale_imagine);
    }
    std::shared_ptr<Tablou> cautaTablou(const std::string& titlu) const;
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

    static void adaugaInLista(const std::shared_ptr<Artist> &artist);

    void afiseaza_profil_artist(NivelDetaliu nivel ) const;
    double calculeaza_scor_stelute()const;
    const std::string getTitlu() const;
    void afiseaza_imagini(NivelDetaliu nivel) const;
    const std::string& getPerioadaArtistica() const { return perioada_artistica; }
};



#endif //ARTNOUVEAUGUEST_ARTIST_H