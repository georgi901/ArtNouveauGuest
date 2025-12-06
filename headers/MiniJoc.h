#ifndef ARTNOUVEAUGUEST_MINIJOC_H
#define ARTNOUVEAUGUEST_MINIJOC_H

#include <string>
#include <memory>
#include <iostream>

enum class Dificultate {
    Usor,
    Mediu,
    Greu
};

class MiniJoc {
protected:
    std::string nume_joc;
    std::string descriere;
    Dificultate dificultate;
    int puncte_obtinute;
    int puncte_maxime;
    bool finalizat;


    static int total_jocuri_jucate;
    static int total_puncte_acordate;


    virtual void initializeaza_implementare() = 0;
    virtual int calculeaza_puncte_implementare() = 0;
    virtual void afiseaza_reguli_implementare() const = 0;

    MiniJoc& operator=(const MiniJoc& other);

public:
    MiniJoc(const std::string& nume_joc, const std::string& descriere, Dificultate dificultate);
    virtual ~MiniJoc() = default;

    MiniJoc(const MiniJoc& other);

    virtual std::unique_ptr<MiniJoc> clone() const = 0;
    virtual std::string getTipJoc() const = 0;


    void initializeaza();
    int calculeazaPuncte();
    void afiseazaRegulile() const;


    static int getTotalJocuri();
    static int getTotalPuncte();
    static void afiseazaStatistici();
    static void reseteazaStatistici();


    const std::string& getNume() const { return nume_joc; }
    const std::string& getDescriere() const { return descriere; }
    Dificultate getDificultate() const { return dificultate; }
    int getPuncteMaxime() const { return puncte_maxime; }
    int getPuncteObtinute() const { return puncte_obtinute; }
    bool esteFinalizat() const { return finalizat; }

    friend std::ostream& operator<<(std::ostream& os, const MiniJoc& joc);
};


std::ostream& operator<<(std::ostream& os, const Dificultate& dif);

#endif //ARTNOUVEAUGUEST_MINIJOC_H