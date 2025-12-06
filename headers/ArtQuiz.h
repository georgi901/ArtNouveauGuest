#ifndef ARTNOUVEAUGUEST_ARTQUIZ_H
#define ARTNOUVEAUGUEST_ARTQUIZ_H

#include "MiniJoc.h"
#include "Tablou.h"
#include <vector>
#include <memory>

struct Intrebare {
    std::string text;
    std::string raspuns_corect;
    std::vector<std::string> variante;  // pentru întrebări cu variante
    int puncte;
};

class ArtQuiz : public MiniJoc {
private:
    std::vector<std::shared_ptr<Tablou>> tablouri_quiz;
    std::vector<Intrebare> intrebari;
    int intrebare_curenta;
    int raspunsuri_corecte;
    int raspunsuri_gresite;

protected:
    void initializeaza_implementare() override;
    int calculeaza_puncte_implementare() override;
    void afiseaza_reguli_implementare() const override;

public:
    ArtQuiz(const std::string& nume, Dificultate dif);
    ArtQuiz(const ArtQuiz& other);
    ~ArtQuiz() override = default;

    std::unique_ptr<MiniJoc> clone() const override;
    std::string getTipJoc() const override;

    // Funcții specifice
    void adaugaTablou(std::shared_ptr<Tablou> tablou);
    void genereazaIntrebari();
    void afiseazaIntrebareCurenta() const;
    bool raspunde(const std::string& raspuns);
    bool areIntrebariRamase() const;
    void urmatoraIntrebare();

    // Getteri
    int getRaspunsuriCorecte() const { return raspunsuri_corecte; }
    int getRaspunsuriGresite() const { return raspunsuri_gresite; }
    int getIntrebariRamase() const { return intrebari.size() - intrebare_curenta; }
};

#endif //ARTNOUVEAUGUEST_ARTQUIZ_H