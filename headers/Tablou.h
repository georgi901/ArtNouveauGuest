
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
    std::string titlu;
    std::string tehnica;
    int an_realizare;
    bool colectionat;
    bool rar;
    std::map<std::string,int> culori;
    std::map<std::string,int> pensule;
    std::pair<int,int> dimensiune;
    std::weak_ptr<Artist> artist;
    std::vector<std::string> imagini_tablou;

public:
    Tablou()
      : titlu("Necunoscut"),
        tehnica("Necunoscut"),
        an_realizare(0),
        colectionat(false),
        rar(false),
        culori({}),
        pensule({}),
        dimensiune({0, 0})
    {}
    Tablou(const std::string& titlu,
           const std::string& tehnica,
           int an_realizare,
           bool rar,
           const std::map<std::string,int>& culori,
           const std::map<std::string,int>& pensule,
           const std::pair<int,int>& dimensiune,
           const std::shared_ptr<Artist>& artist,
           bool colectionat = false);
    friend std::istream& operator>>(std::istream& in, Tablou& t) {
        std::cout << "Tablou: " << t.titlu << "\n";
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
    Tablou(const Tablou& other);
    Tablou& operator=(const Tablou& other);
    ~Tablou() = default;
    static std::ostream& afiseaza_tablou(std::ostream& out, const Tablou& t, NivelDetaliu nivel);
    const std::shared_ptr<Artist> getArtist() const { return artist.lock(); }
    void setArtist(const std::shared_ptr<Artist>& art) {
        artist = art;
    }
    bool este_colectionat() const { return colectionat; }
    void set_colectionat(bool val) { colectionat = val; }
    bool este_rar() const { return rar; }
    const std::string& getTitlu() const { return titlu; }
    int getAnRealizare() const { return an_realizare; }
    void afiseaza_tablou_zoom(NivelDetaliu nivel ) const;
    void afiseaza_imagini(NivelDetaliu nivel) const;
    void adaugaImagine(const std::string& cale_imagine) {
        imagini_tablou.push_back(cale_imagine);
    }
};

#endif //ARTNOUVEAUGUEST_TABLOU_H