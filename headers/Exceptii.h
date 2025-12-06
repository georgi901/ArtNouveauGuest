#ifndef ARTNOUVEAUGUEST_EXCEPTII_H
#define ARTNOUVEAUGUEST_EXCEPTII_H

#include <exception>
#include <string>

class GalerieException : public std::exception {
protected:
    std::string mesaj;
public:
    explicit GalerieException(const std::string& msj);
    const char* what()const noexcept override ;
};

class  PuncteInsuficienteException : public GalerieException {
private:
    int pct_disponibile;
    int pct_necesare;
public:
    explicit PuncteInsuficienteException ( int pct_disponibile , int pct_necesare );
    int getPctDisponibile() const;
    int getPctNecesare() const;
    int getPctLipsa() const;
};

class TablouIndisponibilException : public GalerieException {
private:
    std::string titlu_tablou;
public:
    explicit TablouIndisponibilException(const std::string& titlu);
    const std::string& getTitlu() const;
};

class JocInvalidException : public GalerieException {
private:
    std::string nume_joc;
public:
    explicit JocInvalidException(const std::string& nume_joc);
    const std::string& getNumeJoc() const;
};

class IncarcareDataException : public GalerieException {
private:
    std::string detalii;
    std::string tip_eroare;
public:
    IncarcareDataException(const std::string& cale_fisier, const std::string& tip);
    const std::string& getDetalii() const;
    const std::string& getTipEroare() const;
};


#endif //ARTNOUVEAUGUEST_EXCEPTII_H