/**
 * @file Exceptii.h
 * @brief Definește ierarhia de excepții pentru aplicația galeriei.
 *
 * Acest fișier conține clasele de excepții personalizate folosite
 * pentru gestionarea erorilor în aplicația galeriei de artă.
 * Toate excepțiile derivează din GalerieException.
 */

#ifndef ARTNOUVEAUGUEST_EXCEPTII_H
#define ARTNOUVEAUGUEST_EXCEPTII_H

#include <exception>
#include <string>

/**
 * @class GalerieException
 * @brief Clasă de bază pentru toate excepțiile din aplicația galeriei.
 *
 * Derivată din std::exception, această clasă oferă un mecanism uniform
 * pentru tratarea erorilor în întreaga aplicație.
 *
 * @code
 * try {
 *     // operație care poate eșua
 * } catch (const GalerieException& e) {
 *     std::cerr << "Eroare galerie: " << e.what() << std::endl;
 * }
 * @endcode
 */
class GalerieException : public std::exception {
protected:
    std::string mesaj;

public:
    explicit GalerieException(const std::string& msj);
    const char* what() const noexcept override;
};

/**
 * @class PuncteInsuficienteException
 * @brief Excepție aruncată când utilizatorul nu are suficiente puncte.
 *
 * Folosită când se încearcă o achiziție cu puncte insuficiente.
 * Oferă informații despre punctele disponibile și cele necesare.
 *
 * @code
 * if (puncte < cost) {
 *     throw PuncteInsuficienteException(puncte, cost);
 * }
 * @endcode
 */
class PuncteInsuficienteException : public GalerieException {
private:
    int pct_disponibile = 0;
    int pct_necesare = 0;

public:
    explicit PuncteInsuficienteException(int pct_disponibile, int pct_necesare);
    int getPctDisponibile() const;
    int getPctNecesare() const;
    int getPctLipsa() const;
};

/**
 * @class TablouIndisponibilException
 * @brief Excepție aruncată când un tablou nu este disponibil pentru achiziție.
 *
 * Folosită când se încearcă cumpărarea unui tablou deja colecționat.
 *
 * @code
 * if (tablou->este_colectionat()) {
 *     throw TablouIndisponibilException(tablou->getTitlu());
 * }
 * @endcode
 */
class TablouIndisponibilException : public GalerieException {
private:
    std::string titlu_tablou;

public:
    explicit TablouIndisponibilException(const std::string& titlu);
    const std::string& getTitlu() const;
};

/**
 * @class JocInvalidException
 * @brief Excepție aruncată când se încearcă accesarea unui joc invalid.
 *
 * Folosită când jocul cerut nu există sau nu poate fi pornit.
 *
 * @code
 * auto joc = galerie.cautaJoc(nume);
 * if (!joc) {
 *     throw JocInvalidException(nume);
 * }
 * @endcode
 */
class JocInvalidException : public GalerieException {
private:
    std::string nume_joc;

public:
    explicit JocInvalidException(const std::string& nume_joc);
    const std::string& getNumeJoc() const;
};

/**
 * @class IncarcareDataException
 * @brief Excepție aruncată la erori de încărcare a datelor din fișiere.
 *
 * Folosită când apar probleme la citirea sau parsarea fișierelor JSON.
 * Poate indica eroare de deschidere fișier sau eroare de parsare.
 *
 * @code
 * std::ifstream fin(cale);
 * if (!fin.is_open()) {
 *     throw IncarcareDataException(cale, "fisier");
 * }
 * @endcode
 */
class IncarcareDataException : public GalerieException {
private:
    std::string detalii;
    std::string tip_eroare;

public:
    IncarcareDataException(const std::string& cale_fisier, const std::string& tip);
    const std::string& getDetalii() const;
    const std::string& getTipEroare() const;
};

#endif  // ARTNOUVEAUGUEST_EXCEPTII_H