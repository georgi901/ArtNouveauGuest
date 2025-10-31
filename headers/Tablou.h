
#ifndef ARTNOUVEAUGUEST_TABLOU_H
#define ARTNOUVEAUGUEST_TABLOU_H


#pragma once
#include <string>
#include <iostream>

class Tablou {
private:
    std::string titlu;
    int an;

public:
    Tablou(const std::string& titlu, int an);
    void afiseaza() const;
};


#endif //ARTNOUVEAUGUEST_TABLOU_H