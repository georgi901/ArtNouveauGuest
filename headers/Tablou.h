
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
    friend std::istream& operator>>(std::istream& in, Tablou& t) {
        std::cout << "Tablou: " << t.titlu << "\n";

        std::cout << "Tablou colecționat? (1=Da / 0=Nu): ";
        in >> t.colectionat;
        in.ignore();

        std::cout << "Număr de imagini: ";
        size_t n;
        in >> n;
        in.ignore();
        t.imagini_tablou.clear();
        for (size_t i = 0; i < n; ++i) {
            std::string img;
            std::cout << "Imagine " << i+1 << ": ";
            std::getline(in, img);
            t.imagini_tablou.push_back(img);
        }

        return in;
    }
    friend std::ostream& operator<<(std::ostream& os, const Tablou& tablou);
    static std::ostream& afiseaza_tablou(std::ostream& out, const Tablou& t, NivelDetaliu nivel);
    void setArtist(const std::shared_ptr<Artist>& a) { artist = a; }
    const std::shared_ptr<Artist> getArtist() const { return artist.lock(); }
    bool este_colectionat() const { return colectionat; }
    void set_colectionat(bool val) { colectionat = val; }
    bool este_rar() const { return rar; }
    const std::string getTitlu() const { return titlu; }
    const std::pair<int,int> getDimensiune() const { return dimensiune; }
    void afiseaza_tablou_zoom(NivelDetaliu nivel ) const;
    void setImagini(const std::vector<std::string>& imagini) {
        imagini_tablou = imagini;
    }
    void afiseaza_imagini(NivelDetaliu nivel) const;
};

#endif //ARTNOUVEAUGUEST_TABLOU_H