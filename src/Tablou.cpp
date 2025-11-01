#include "../headers/Tablou.h"
#include "../headers/Artist.h"
#include <iostream>
Tablou::Tablou(const std::string& titlu,
               const std::string& tehnica,
               int an_realizare,
               bool rar,
               const std::map<std::string,int>& culori,
               const std::map<std::string,int>& pensule,
               const std::pair<int,int>& dimensiune,
               std::shared_ptr<Artist> artist,
               bool colectionat)
    : titlu(titlu),
      tehnica(tehnica),
      an_realizare(an_realizare),
      colectionat(colectionat),
      rar(rar),
      culori(culori),
      pensule(pensule),
      dimensiune(dimensiune),
      artist(artist)
{}

void Artist::afiseaza_imagini(NivelDetaliu nivel) const {
    if(imagini_artist.empty()) {
        std::cout << "Nu există imagini cu acest tablou.\n";
        return;
    }

    if(nivel == NivelDetaliu::Minimal) {
        std::cout << "Tabloul: " << imagini_artist[0] << "\n";
    }
    else if(nivel == NivelDetaliu::Complet) {
        std::cout << "Imagini cu detaliile tabloului:\n";
        for(size_t i = 1; i < imagini_artist.size(); ++i) {
            std::cout << "  " << imagini_artist[i] << "\n";
        }
    }
}

void Tablou::afiseaza_tablou_zoom(NivelDetaliu nivel) const {
    std::cout << "\n---- TABLOU: " << titlu << " ----\n";

    if (nivel >= NivelDetaliu::Minimal ) {
        std::cout << "Tehnica: " << tehnica
                  << " | An realizare: " << an_realizare
                  << " | Dimensiune: " << dimensiune.first << "x" << dimensiune.second << " cm\n";
        std::cout << "Colecționat: " << (colectionat ? "Da" : "Nu")
                  << " | Raritate: " << (rar ? "Da" : "Nu") << "\n";
        std::cout << "\n---- TABLOU "<< dimensiune.first << "x" << dimensiune.second << " cm"<<" ----\n";
        afiseaza_imagini(nivel);

        auto ptr_artist = artist.lock();
        if (ptr_artist) {
            std::cout << "Artist: " << ptr_artist->getNume() << " " << ptr_artist->getPrenume()
                      << " | Perioada: " << ptr_artist->getPerioadaArtistica() << "\n";
        } else {
            std::cout << "Artist: Necunoscut\n";
        }
    }

    if (nivel >= NivelDetaliu::Complet) {

        std::cout << "\nCulori folosite:\n";
        for (const auto& [culoare, nr] : culori)
            std::cout << "  • " << culoare << ": " << nr << " tuburi\n";

        std::cout << "\nTipuri de pensule folosite:\n";
        for (const auto& [tip, nr] : pensule)
            std::cout << "  • " << tip << ": " << nr << "\n";

        std::cout << "\n---- ZOOM TABLOU "<< dimensiune.first << "x" << dimensiune.second << " cm"<<" ----\n";
        afiseaza_imagini(nivel);
    }
}

