#include "../headers/Exceptii.h"

GalerieException::GalerieException(const std::string& msj) : mesaj(msj){}

const char *GalerieException::what() const noexcept {
    return mesaj.c_str();
}

PuncteInsuficienteException::PuncteInsuficienteException(int pct_disponibile, int pct_necesare) : GalerieException("Puncte insuficiente: ai " +
                                                                                                                    std::to_string(pct_disponibile) +
                                                                                                                     ", dar ai nevoie de " +
                                                                                                                     std::to_string(pct_necesare)) ,
                                                                                                    pct_disponibile(pct_disponibile),
                                                                                                    pct_necesare(pct_necesare) {}

int PuncteInsuficienteException::getPctDisponibile() const {
    return pct_disponibile;
}

int PuncteInsuficienteException::getPctNecesare() const {
    return pct_necesare;
}

int PuncteInsuficienteException::getPctLipsa() const {
    return pct_necesare - pct_disponibile;
}

TablouIndisponibilException::TablouIndisponibilException(const std::string& titlu_tablou) : GalerieException("Tabloul '" + titlu_tablou + "' nu este disponibil"),
                                                                                             titlu_tablou(titlu_tablou) {}

const std::string& TablouIndisponibilException::getTitlu() const {
    return titlu_tablou;
}

JocInvalidException::JocInvalidException(const std::string& nume_joc) : GalerieException("Jocul '" + nume_joc + "' nu exista sau nu poate fi pornit"),
                                                                 nume_joc(nume_joc) {}

const std::string& JocInvalidException::getNumeJoc() const {
    return nume_joc;
}

IncarcareDataException::IncarcareDataException(const std::string& cale_fisier,
                                               const std::string& tip)
    : GalerieException(
        tip == "fisier"
            ? "Nu pot deschide fisierul: " + cale_fisier
            : "Eroare la parsarea JSON din fisierul: " + cale_fisier
      ),
      detalii(cale_fisier),
      tip_eroare(tip) {}

const std::string& IncarcareDataException::getDetalii() const {
    return detalii;
}

const std::string& IncarcareDataException::getTipEroare() const {
    return tip_eroare;
}





