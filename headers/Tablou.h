
#ifndef ARTNOUVEAUGUEST_TABLOU_H
#define ARTNOUVEAUGUEST_TABLOU_H


#pragma once
#include <iostream>
#include <string>
#include <map>
#include <memory>
#include <vector>



class Artist;

enum class NivelDetaliu {
    Minimal,
    Complet
};

class Tablou {
private:
    const std::string titlu;
    const std::string tehnica;
    const int an_realizare;
    bool colectionat;
    bool rar;
    const std::map<std::string,int> culori;
    const std::map<std::string,int> pensule;
    const std::pair<int,int> dimensiune;
    std::weak_ptr<Artist> artist;
    std::vector<std::string> imagini_tablou;

public:
    Tablou(const std::string& titlu,
           const std::string& tehnica,
           int an_realizare,
           bool rar,
           const std::map<std::string,int>& culori,
           const std::map<std::string,int>& pensule,
           const std::pair<int,int>& dimensiune,
           std::shared_ptr<Artist> artist,
           bool colectionat = false);
    ~Tablou() = default;
    void setArtist(const std::shared_ptr<Artist>& a) { artist = a; }
    std::shared_ptr<Artist> getArtist() const { return artist.lock(); }
    bool este_colectionat() const { return colectionat; }
    void set_colectionat(bool val) { colectionat = val; }
    bool este_rar() const { return rar; }
    std::string getTitlu() const { return titlu; }
    std::pair<int,int> getDimensiune() const { return dimensiune; }
    void afiseaza_tablou_zoom(NivelDetaliu nivel ) const;
    void setImagini(const std::vector<std::string>& imagini) {
        imagini_tablou = imagini;
    }
    void afiseaza_imagini(NivelDetaliu nivel) const;
};

#endif //ARTNOUVEAUGUEST_TABLOU_H