#include <iostream>
#include <memory>
#include "headers/Galerie.h"
#include "headers/Artist.h"
#include "headers/Tablou.h"
#include "headers/Utilizator.h"

void initializeazaDate(Galerie& galerie) {

    auto mucha = std::make_shared<Artist>(
        "Mucha", "Alfons", "Ceh", 78, 1860, 1939,
        "Art Nouveau", "01.01.2020",
        "", "", std::vector<std::string>{},
        "Jiří Mucha", "jiri_mucha", "jiri@mucha.cz",
        std::vector<std::string>{"A adăugat tabloul 'Zodiac'", "A adăugat tabloul 'Seasons'"}
    );
    mucha->adaugaImagine("mucha_portret.jpg");
    mucha->adaugaImagine("mucha_atelier.jpg");

    auto klimt = std::make_shared<Artist>(
        "Klimt", "Gustav", "Austriac", 55, 1862, 1918,
        "Art Nouveau", "15.01.2020",
        "", "", std::vector<std::string>{},
        "Emilie Flöge", "emilie_f", "emilie@klimt.at",
        std::vector<std::string>{"A adăugat tabloul 'Sărutul'"}
    );
    klimt->adaugaImagine("klimt_portret.jpg");

    auto beardsley = std::make_shared<Artist>(
        "Beardsley", "Aubrey", "Britanic", 25, 1872, 1898,
        "Art Nouveau", "01.02.2020",
        "", "", std::vector<std::string>{},
        "Mabel Beardsley", "mabel_b", "mabel@beardsley.uk",
        std::vector<std::string>{"A adăugat tabloul 'Salome'"}
    );
    beardsley->adaugaImagine("beardsley_portret.jpg");

    auto lalique = std::make_shared<Artist>(
        "Lalique", "Rene", "Francez", 85, 1860, 1945,
        "Art Nouveau", "05.05.2023",
        "", "", std::vector<std::string>{},
        "Marie Lalique", "marie_l", "marie@lalique.fr",
        std::vector<std::string>{"A adăugat designul 'Dragonfly Woman'"}
    );
    lalique->adaugaImagine("lalique_foto.jpg");

    auto sophia = std::make_shared<Artist>(
        "Chen", "Sophia", "Taiwaneză", 38, 1987, 0,
        "Art Nouveau Contemporan", "15.03.2021",
        "sophia_art_nouveau", "sophia@chenart.com",
        std::vector<std::string>{"Înregistrare în galerie", "A adăugat 'Floral Dreams'", "Participare la expoziție"}
    );
    sophia->adaugaImagine("sophia_portrait.jpg");
    sophia->adaugaImagine("sophia_studio.jpg");

    auto elena = std::make_shared<Artist>(
        "Popescu", "Elena", "Română", 42, 1983, 0,
        "Art Nouveau Contemporan", "20.06.2020",
        "elena_nouveau", "elena.popescu@artmail.ro",
        std::vector<std::string>{"Înregistrare în galerie", "A adăugat 'Romanian Legends'", "Colaborare cu muzeul local"}
    );
    elena->adaugaImagine("elena_photo.jpg");

    auto marcus = std::make_shared<Artist>(
        "Bergstrom", "Marcus", "Suedez", 35, 1990, 0,
        "Art Nouveau Contemporan", "10.09.2023",
        "marcus_nouveau_design", "marcus@bergstrom.se",
        std::vector<std::string>{"Înregistrare în galerie", "A creat 'Nordic Flora'"}
    );
    marcus->adaugaImagine("marcus_pic.jpg");


    auto zodiac = std::make_shared<Tablou>(
        "Zodiac",
        "Litografie",
        1896,
        true,
        std::map<std::string, int>{{"Auriu", 5}, {"Albastru", 4}, {"Verde", 3}},
        std::map<std::string, int>{{"Detaliu fin", 5}, {"Ornamental", 4}},
        std::make_pair(66, 66),
        mucha,
        true
    );
    zodiac->adaugaImagine("zodiac_complet.jpg");
    zodiac->adaugaImagine("zodiac_detaliu1.jpg");
    zodiac->adaugaImagine("zodiac_detaliu2.jpg");

    auto seasons = std::make_shared<Tablou>(
        "The Seasons",
        "Litografie",
        1896,
        true,
        std::map<std::string, int>{{"Pastel", 6}, {"Auriu", 3}, {"Verde", 4}},
        std::map<std::string, int>{{"Decorativ", 4}, {"Floral", 5}},
        std::make_pair(72, 52),
        mucha,
        false
    );
    seasons->adaugaImagine("seasons_complet.jpg");

    auto sarutul = std::make_shared<Tablou>(
        "Sărutul",
        "Ulei pe pânză cu frunze de aur",
        1908,
        true,
        std::map<std::string, int>{{"Auriu", 10}, {"Galben", 5}, {"Maro", 3}},
        std::map<std::string, int>{{"Geometric", 5}, {"Ornamental", 6}},
        std::make_pair(180, 180),
        klimt,
        true
    );
    sarutul->adaugaImagine("sarutul_complet.jpg");
    sarutul->adaugaImagine("sarutul_detalii.jpg");

    auto salome = std::make_shared<Tablou>(
        "Salome",
        "Cerneală indiană",
        1894,
        true,
        std::map<std::string, int>{{"Negru", 8}, {"Alb", 10}},
        std::map<std::string, int>{{"Peniță", 10}, {"Detaliu fin", 8}},
        std::make_pair(23, 28),
        beardsley,
        false
    );
    salome->adaugaImagine("salome_complet.jpg");

    auto dragonfly = std::make_shared<Tablou>(
        "Dragonfly Woman",
        "Design bijuterie - smalț și aur",
        1897,
        false,
        std::map<std::string, int>{{"Verde smarald", 4}, {"Auriu", 5}, {"Albastru", 2}},
        std::map<std::string, int>{{"Miniaturist", 8}, {"Detaliu", 9}},
        std::make_pair(15, 23),
        lalique,
        false
    );
    dragonfly->adaugaImagine("dragonfly_complet.jpg");

    auto floral_dreams = std::make_shared<Tablou>(
        "Floral Dreams",
        "Acrilic și frunze de aur pe pânză",
        2023,
        false,
        std::map<std::string, int>{{"Auriu", 6}, {"Roz pastel", 5}, {"Verde mentă", 4}, {"Alb perlat", 3}},
        std::map<std::string, int>{{"Ornamental", 5}, {"Detaliu fin", 6}, {"Plat", 2}},
        std::make_pair(120, 90),
        sophia,
        true
    );
    floral_dreams->adaugaImagine("floral_dreams_complet.jpg");
    floral_dreams->adaugaImagine("floral_dreams_detaliu.jpg");

    auto romanian_legends = std::make_shared<Tablou>(
        "Romanian Legends",
        "Tempera și ornamente metalice",
        2024,
        true,
        std::map<std::string, int>{{"Roșu", 7}, {"Auriu", 8}, {"Negru", 3}, {"Verde", 4}},
        std::map<std::string, int>{{"Decorativ", 6}, {"Traditional", 5}, {"Detaliu", 7}},
        std::make_pair(100, 80),
        elena,
        false
    );
    romanian_legends->adaugaImagine("romanian_legends_full.jpg");

    auto nordic_flora = std::make_shared<Tablou>(
        "Nordic Flora",
        "Acuarelă și cerneală pe hârtie",
        2023,
        false,
        std::map<std::string, int>{{"Albastru nordic", 6}, {"Verde pădure", 5}, {"Gri argintiu", 3}},
        std::map<std::string, int>{{"Floral", 8}, {"Detaliu botanesc", 7}, {"Liniar", 4}},
        std::make_pair(70, 100),
        marcus,
        true
    );
    nordic_flora->adaugaImagine("nordic_flora_complete.jpg");
    nordic_flora->adaugaImagine("nordic_flora_details.jpg");


    galerie.adaugaArtist(mucha);
    galerie.adaugaArtist(klimt);
    galerie.adaugaArtist(beardsley);
    galerie.adaugaArtist(lalique);
    galerie.adaugaArtist(sophia);
    galerie.adaugaArtist(elena);
    galerie.adaugaArtist(marcus);

    galerie.adaugaTablou(zodiac);
    galerie.adaugaTablou(seasons);
    galerie.adaugaTablou(sarutul);
    galerie.adaugaTablou(salome);
    galerie.adaugaTablou(dragonfly);
    galerie.adaugaTablou(floral_dreams);
    galerie.adaugaTablou(romanian_legends);
    galerie.adaugaTablou(nordic_flora);


    mucha->adaugaTablou(zodiac);
    mucha->adaugaTablou(seasons);
    klimt->adaugaTablou(sarutul);
    beardsley->adaugaTablou(salome);
    lalique->adaugaTablou(dragonfly);
    sophia->adaugaTablou(floral_dreams);
    elena->adaugaTablou(romanian_legends);
    marcus->adaugaTablou(nordic_flora);
}

void afiseazaMeniu() {
    std::cout << "\n========================================\n";
    std::cout << "      GALERIE DE ARTĂ - MENIU\n";
    std::cout << "========================================\n";
    std::cout << "1.  Afișează toți artiștii\n";
    std::cout << "2.  Afișează toate tablourile\n";
    std::cout << "3.  Caută artist (profil minimal)\n";
    std::cout << "4.  Caută artist (profil complet)\n";
    std::cout << "5.  Caută tablou (detalii minime)\n";
    std::cout << "6.  Caută tablou (detalii complete)\n";
    std::cout << "7.  Afișează galeria completă\n";
    std::cout << "8.  Testează utilizator și colecție\n";
    std::cout << "9.  Afișează statistici artist\n";
    std::cout << "10. Tablouri rare ale unui artist\n";
    std::cout << "0.  Ieșire\n";
    std::cout << "========================================\n";
    std::cout << "Alege opțiunea: ";
}

int main() {
    Galerie galerie("Galeria Art Nouveau", "Art Nouveau", 1895);
    initializeazaDate(galerie);

    auto utilizator = std::make_shared<Utilizator>(
        "Popescu Ion", "ion_pop", "ion@email.com", 35, "01.01.2023"
    );

    int optiune;
    std::string nume, titlu;

    do {
        afiseazaMeniu();
        std::cin >> optiune;
        std::cin.ignore();

        switch(optiune) {
            case 1:
                galerie.afiseazaArtiști();
                break;

            case 2:
                galerie.afiseazaTablouri();
                break;

            case 3:
                std::cout << "Introdu numele/prenumele artistului: ";
                std::getline(std::cin, nume);
                {
                    auto artist = galerie.cautaArtist(nume);
                    if (artist) {
                        artist->afiseaza_profil_artist(NivelDetaliu::Minimal);
                    } else {
                        std::cout << "Artist negăsit!\n";
                    }
                }
                break;

            case 4:
                std::cout << "Introdu numele/prenumele artistului: ";
                std::getline(std::cin, nume);
                {
                    auto artist = galerie.cautaArtist(nume);
                    if (artist) {
                        artist->afiseaza_profil_artist(NivelDetaliu::Complet);
                    } else {
                        std::cout << "Artist negăsit!\n";
                    }
                }
                break;

            case 5:
                std::cout << "Introdu titlul tabloului: ";
                std::getline(std::cin, titlu);
                {
                    auto tablou = galerie.cautaTablou(titlu);
                    if (tablou) {
                        tablou->afiseaza_tablou_zoom(NivelDetaliu::Minimal);
                    } else {
                        std::cout << "Tablou negăsit!\n";
                    }
                }
                break;

            case 6:
                std::cout << "Introdu titlul tabloului: ";
                std::getline(std::cin, titlu);
                {
                    auto tablou = galerie.cautaTablou(titlu);
                    if (tablou) {
                        tablou->afiseaza_tablou_zoom(NivelDetaliu::Complet);
                    } else {
                        std::cout << "Tablou negăsit!\n";
                    }
                }
                break;

            case 7:
                std::cout << galerie;
                break;

            case 8:
            {
                std::cout << "\n----- TEST UTILIZATOR ȘI COLECȚIE -----\n\n";


                std::cout << "PASUL 1: Profilul utilizatorului ÎNAINTE de adăugarea tablourilor\n";
                std::cout << "-------------------------------------------------------------------\n";
                std::cout << *utilizator;


                std::cout << "\n\nPASUL 2: Adăugarea tablourilor în colecție\n";
                std::cout << "-------------------------------------------------------------------\n";

                auto tablou = galerie.cautaTablou("Zodiac");
                if (tablou) {
                    std::cout << "→ Se adaugă: 'Zodiac' de Mucha Alfons\n";
                    utilizator->adaugaTablou(tablou);
                    std::cout << "  ✓ Adăugat cu succes!\n\n";
                }

                tablou = galerie.cautaTablou("Sărutul");
                if (tablou) {
                    std::cout << "→ Se adaugă: 'Sărutul' de Klimt Gustav\n";
                    utilizator->adaugaTablou(tablou);
                    std::cout << "  ✓ Adăugat cu succes!\n";
                }


                std::cout << "\n\nPASUL 3: Vizualizare colecție completă\n";
                std::cout << "----------------------------------------------------------------------\n";
                utilizator->afiseazaColectie();


                std::cout << "\n\nPASUL 4: Profilul utilizatorului DUPĂ adăugarea tablourilor\n";
                std::cout << "----------------------------------------------------------------------\n";
                std::cout << *utilizator;

                std::cout << "\n\n✓ Test finalizat cu succes!\n";
            }
                break;

            case 9:
                std::cout << "Introdu numele/prenumele artistului: ";
                std::getline(std::cin, nume);
                {
                    auto artist = galerie.cautaArtist(nume);
                    if (artist) {
                        std::cout << "\n======= STATISTICI " << artist->getNume() << " =======\n";
                        std::cout << "Total tablouri: " << artist->nrTablouri() << "\n";
                        std::cout << "Tablouri colecționate: " << artist->nrTablouriColectionate() << "\n";
                        std::cout << "Tablouri rare: " << artist->nrTablouriRare() << "\n";
                        std::cout << "Scor popularitate: " << artist->calculeaza_scor_stelute() << " stele\n";
                        std::cout << "Titlu: " << artist->getTitlu() << "\n";
                    } else {
                        std::cout << "Artist negăsit!\n";
                    }
                }
                break;

            case 10:
                std::cout << "Introdu numele/prenumele artistului: ";
                std::getline(std::cin, nume);
                {
                    auto artist = galerie.cautaArtist(nume);
                    if (artist) {
                        auto rare = artist->getTablouriRare();
                        std::cout << "\n======== TABLOURI RARE - " << artist->getNume() << " ========\n";
                        if (rare.empty()) {
                            std::cout << "Nu există tablouri rare.\n";
                        } else {
                            for (const auto& t : rare) {
                                std::cout << "• " << t->getTitlu() << " (" << t->getAnRealizare() << ")\n";
                            }
                        }
                    } else {
                        std::cout << "Artist negăsit!\n";
                    }
                }
                break;

            case 0:
                std::cout << "\nLa revedere!\n";
                break;

            default:
                std::cout << "\nOpțiune invalidă!\n";
        }

        if (optiune != 0) {
            std::cout << "\nApasă ENTER pentru a continua...";
            std::cin.get();
        }

    } while(optiune != 0);

    return 0;
}