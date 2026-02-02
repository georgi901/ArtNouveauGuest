/**
 * @file MiniJoc.h
 * @brief Definește clasa abstractă MiniJoc pentru sistemul de jocuri.
 *
 * Acest fișier conține clasa de bază MiniJoc care definește interfața
 * comună pentru toate mini-jocurile din galerie. Folosește NVI (Non-Virtual Interface)
 * pattern pentru a asigura comportament consistent.
 */

#ifndef ARTNOUVEAUGUEST_MINIJOC_H
#define ARTNOUVEAUGUEST_MINIJOC_H

#include <iostream>
#include <memory>
#include <string>

/**
 * @enum Dificultate
 * @brief Nivelurile de dificultate disponibile pentru jocuri.
 */
enum class Dificultate { Usor, Mediu, Greu };

/**
 * @class MiniJoc
 * @brief Clasă abstractă de bază pentru toate mini-jocurile din galerie.
 *
 * Implementează pattern-ul NVI (Non-Virtual Interface) pentru a separa
 * interfața publică de implementarea specifică fiecărui joc.
 * Gestionează statistici globale pentru toate jocurile jucate.
 *
 * Clasele derivate trebuie să implementeze:
 * - initializeaza_implementare() - logica de inițializare
 * - calculeaza_puncte_implementare() - calculul punctajului
 * - afiseaza_reguli_implementare() - regulile specifice
 * - clone() - pentru copiere polimorfică
 * - getTipJoc() - numele tipului de joc
 *
 * @code
 * class JocNou : public MiniJoc {
 *     void initializeaza_implementare() override { ... }
 *     int calculeaza_puncte_implementare() override { return puncte; }
 *     void afiseaza_reguli_implementare() const override { ... }
 * };
 * @endcode
 */
class MiniJoc {
protected:
    std::string nume_joc;
    std::string descriere;
    Dificultate dificultate;
    int puncte_obtinute = 0;
    int puncte_maxime = 100;
    bool finalizat = false;

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

    const std::string& getNume() const {
        return nume_joc;
    }
    const std::string& getDescriere() const {
        return descriere;
    }
    Dificultate getDificultate() const {
        return dificultate;
    }
    int getPuncteMaxime() const {
        return puncte_maxime;
    }
    int getPuncteObtinute() const {
        return puncte_obtinute;
    }
    bool esteFinalizat() const {
        return finalizat;
    }

    friend std::ostream& operator<<(std::ostream& os, const MiniJoc& joc);
};

std::ostream& operator<<(std::ostream& os, const Dificultate& dif);

#endif  // ARTNOUVEAUGUEST_MINIJOC_H