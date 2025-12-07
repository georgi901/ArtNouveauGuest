#ifndef ARTNOUVEAUGUEST_ARTPUZZLE_H
#define ARTNOUVEAUGUEST_ARTPUZZLE_H

#include "MiniJoc.h"
#include "Tablou.h"
#include <vector>
#include <memory>

class ArtPuzzle : public MiniJoc {
private:
    std::shared_ptr<Tablou> tablou_tinta;
    std::vector<int> ordine_fragmente;
    std::vector<int> ordine_corecta;
    int numar_fragmente;
    int mutari_efectuate;
    int mutari_maxime;
    bool rezolvat;

protected:
    void initializeaza_implementare() override;
    int calculeaza_puncte_implementare() override;
    void afiseaza_reguli_implementare() const override;

public:
    ArtPuzzle(const std::string& nume, Dificultate dif);
    ArtPuzzle(const ArtPuzzle& other);
    ~ArtPuzzle() override;


    void seteazaTablou(std::shared_ptr<Tablou> tablou);
    void amestecaFragmente();
    bool mutaFragment(int pozitie1, int pozitie2);
    bool esteRezolvat() const;
    void afiseazaPuzzle() const;


    int getMutariEfectuate() const { return mutari_efectuate; }
    int getMutariRamase() const { return mutari_maxime - mutari_efectuate; }
    int getNumarFragmente() const { return numar_fragmente; }


    std::unique_ptr<MiniJoc> clone() const override;
    std::string getTipJoc() const override;
};


#endif //ARTNOUVEAUGUEST_ARTPUZZLE_H