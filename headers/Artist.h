
#ifndef ARTNOUVEAUGUEST_ARTIST_H
#define ARTNOUVEAUGUEST_ARTIST_H



#pragma once
#include <string>
#include <iostream>
#include <vector>

class Artist {
private:
    const std::string nume;
    const std::string prenume;
    const std::string nationalitate;
    const int varsta;
    const int an_nastere;
    const int an_deces;
    std::string perioada_artistica;
    std::vector<std::string> imagini_artist;
    int nr_tablouri;
    int nr_tablouri_colectionate;
    const int nr_tablouri_rare;
    const int data_inscriere;
    std::string username;
    std::string email;
    std::vector<std::string> istoric;
    std::string pers_reprezentant;
    std::string username_reprezentant;
    std::string email_reprezentant;
    std::vector<std::string> istoric_reprezentant;

public:
    Artist(const std::string& nume,
           const std::string& prenume,
           const std::string& nationalitate,
           int varsta,
           int an_nastere,
           int an_deces,
           const std::string& perioada_artistica,
           int nr_tablouri = 0,
           int nr_tablouri_colectionate = 0,
           int nr_tablouri_rare = 0,
           int data_inscriere = 0,
           const std::string& username = "",
           const std::string& email = "",
           const std::vector<std::string>& istoric = {},
           const std::string& pers_reprezentant = "",
           const std::string& username_reprezentant = "",
           const std::string& email_reprezentant = "",
           const std::vector<std::string>& istoric_reprezentant = {});
    ~Artist();
    friend std::ostream& operator<<(std::ostream& os, const Artist& artist);

    void afiseaza_informatii_artist()const;
    void afiseaza_bibliografie()const;
    void afiseaza_imagini()const;
    double calculeaza_scor_stelute()const;
    void setImagini(const std::vector<std::string>& imagini) {
        imagini_artist = imagini;
    }

};



#endif //ARTNOUVEAUGUEST_ARTIST_H