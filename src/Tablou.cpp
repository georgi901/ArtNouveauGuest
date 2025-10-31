#include "../headers/Tablou.h"
#include <iostream>

Tablou::Tablou(const std::string& titlu, int an)
    : titlu(titlu), an(an) {}

void Tablou::afiseaza() const {
    std::cout << "Tablou frumos: " << titlu << " (" << an << ") " << std::endl;
}