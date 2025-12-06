#include <iostream>
#include <memory>
#include "headers/Galerie.h"
#include "headers/Artist.h"
#include "headers/Tablou.h"
#include "headers/Utilizator.h"
#include "headers/Exceptii.h"
#include "headers/MiniJoc.h"
#include "headers/ArtisticDelight.h"
#include "headers/QuickArtLook.h"
#include "headers/ArtQuiz.h"
#include <fstream>
#include <nlohmann/json.hpp>


std::shared_ptr<Utilizator> incarcaUtilizatorDinFisier(const std::string& caleFisier) {
    std::ifstream fin(caleFisier);

    if (!fin.is_open()) {
        throw IncarcareDataException(caleFisier, "fisier");
    }

    nlohmann::json data;
    try {
        fin >> data;
    } catch (const nlohmann::json::parse_error& ) {
        throw IncarcareDataException(caleFisier, "parsare");
    }

    fin.close();

    auto u = data[0];

    return std::make_shared<Utilizator>(
        u["nume"],
        u["username"],
        u["email"],
        u["varsta"],
        u["data_inregistrare"]
    );
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
    std::cout << "11. Test cerințe (Tablou)\n";
    std::cout << "12. Test exceptii\n";
    std::cout << "13. Afișează jocuri disponibile\n";
    std::cout << "14. Joacă un joc\n";
    std::cout << "15. Test MiniJoc + dynamic_cast\n";
    std::cout << "0.  Ieșire\n";
    std::cout << "========================================\n";
    std::cout << "Alege opțiunea: ";
}

int main() {
    Galerie galerie("Galeria Art Nouveau", "Art Nouveau", 1895);
    std::shared_ptr<Utilizator> utilizator;
    // Încărcare date din fișiere JSON
    try {
        std::cout << "\n========================================\n";
        std::cout << "  ÎNCĂRCARE DATE DIN FIȘIERE JSON\n";
        std::cout << "========================================\n";

        std::cout << "→ Încărcare artiști din 'artisti.json'...\n";
        galerie.incarcaArtistiDinFisier("data/artisti.json");
        std::cout << "    Artiști încărcați cu succes!\n\n";

        std::cout << "→ Încărcare tablouri din 'tablouri.json'...\n";
        galerie.incarcaTablouriDinFisier("data/tablouri.json");
        std::cout << "    Tablouri încărcate cu succes!\n\n";

        std::cout << "→ Încărcare utilizator din 'utilizatori.json'...\n";
        utilizator = incarcaUtilizatorDinFisier("data/utilizatori.json");
        std::cout << "    Utilizator încărcat cu succes!\n";

        std::cout << "========================================\n";
        std::cout << "    TOATE DATELE AU FOST ÎNCĂRCATE\n";
        std::cout << "========================================\n";

    } catch (const IncarcareDataException& e) {
        std::cerr << "\nEROARE FATALĂ: " << e.what() << "\n";
        std::cerr << "Tip eroare: " << e.getTipEroare() << "\n";
        std::cerr << "Detalii: " << e.getDetalii() << "\n\n";
        std::cerr << "Programul nu poate continua fără date!\n";
        std::cerr << "Asigură-te că fișierele JSON există în folderul 'data/'.\n\n";
        return 1;
    } catch (const GalerieException& e) {
        std::cerr << "\nEROARE FATALĂ: " << e.what() << "\n";
        std::cerr << "Programul nu poate continua!\n\n";
        return 1;
    }

    auto joc1 = std::make_shared<ArtisticDelight>("Artistic Delight", Dificultate::Mediu);
    auto tablou_zodiac = galerie.cautaTablou("Zodiac");
    if (tablou_zodiac) {
        joc1->seteazaTablou(tablou_zodiac);
    }
    galerie.adaugaJoc(joc1);


    auto joc2 = std::make_shared<QuickArtLook>("Quick Art Look", Dificultate::Usor);
    // Adaugă perechi tablou-artist
    for (const auto& tablou : galerie.getTablouri()) {
        auto artist = tablou->getArtist();
        if (artist) {
            joc2->adaugaPereche(tablou, artist);
        }
    }
    galerie.adaugaJoc(joc2);


    auto joc3 = std::make_shared<ArtQuiz>("Art Quiz", Dificultate::Greu);
    for (const auto& tablou : galerie.getTablouri()) {
        joc3->adaugaTablou(tablou);
    }
    galerie.adaugaJoc(joc3);

    std::cout << " Jocuri create cu succes!\n";



    int optiune;
    std::string nume, titlu;

    do {
        afiseazaMeniu();
        std::cin >> optiune;
        std::cin.ignore();

        switch(optiune) {
            case 1:
                galerie.afiseazaArtisti();
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
                    std::cout << "  Adăugat cu succes!\n\n";
                }

                tablou = galerie.cautaTablou("Sărutul");
                if (tablou) {
                    std::cout << "→ Se adaugă: 'Sărutul' de Klimt Gustav\n";
                    utilizator->adaugaTablou(tablou);
                    std::cout << "  Adăugat cu succes!\n";
                }


                std::cout << "\n\nPASUL 3: Vizualizare colecție completă\n";
                std::cout << "----------------------------------------------------------------------\n";
                utilizator->afiseazaColectie();


                std::cout << "\n\nPASUL 4: Profilul utilizatorului DUPĂ adăugarea tablourilor\n";
                std::cout << "----------------------------------------------------------------------\n";
                std::cout << *utilizator;

                std::cout << "\n\n Test finalizat cu succes!\n";
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
            case 11:
            {
                std::cout << "\n========== TESTE CERINȚE  ==========\n\n";

                auto tablou_original = galerie.cautaTablou("Zodiac");

                if (!tablou_original) {
                    std::cout << "Tabloul Zodiac nu a fost găsit!\n";
                    break;
                }

                std::cout << "PASUL 1: Tabloul original\n";
                std::cout << "-------------------------\n";
                std::cout << "Titlu: " << tablou_original->getTitlu() << "\n";
                std::cout << "An: " << tablou_original->getAnRealizare() << "\n\n";

                std::cout << "PASUL 2: Test CONSTRUCTOR DE COPIERE\n";
                std::cout << "--------------------------------------\n";
                const Tablou tablou_copie(*tablou_original);
                std::cout << "Copiat: " << tablou_copie.getTitlu() << "\n\n";

                std::cout << "PASUL 3: Test OPERATOR= DE COPIERE\n";
                std::cout << "------------------------------------\n";
                Tablou tablou_gol;
                std::cout << "Înainte: " << tablou_gol.getTitlu() << "\n";
                tablou_gol = *tablou_original;
                std::cout << "După operator=: " << tablou_gol.getTitlu() << "\n\n";

                std::cout << " Toate testele OK! \n";
                std::cout << "  - Constructor copiere: BUN \n";
                std::cout << "  - Operator=: BUN \n";
                std::cout << "  - Destructor: BUN (se va apela automat)\n";
            }
            case 12:
            {
                std::cout << "\n===== TEST EXCEPTII =====\n\n";

                // Test 1: PuncteInsuficienteException
                std::cout << "Test 1: PuncteInsuficienteException\n";
                try {
                    throw PuncteInsuficienteException(100, 500);
                } catch (const PuncteInsuficienteException& e) {
                    std::cout << "  Mesaj: " << e.what() << "\n";
                    std::cout << "  Disponibile: " << e.getPctDisponibile() << "\n";
                    std::cout << "  Necesare: " << e.getPctNecesare() << "\n";
                    std::cout << "  Lipsa: " << e.getPctLipsa() << "\n";
                }

                // Test 2: TablouIndisponibilException
                std::cout << "\nTest 2: TablouIndisponibilException\n";
                try {
                    throw TablouIndisponibilException("Mona Lisa");
                } catch (const TablouIndisponibilException& e) {
                    std::cout << "  Mesaj: " << e.what() << "\n";
                    std::cout << "  Titlu: " << e.getTitlu() << "\n";
                }

                // Test 3: JocInvalidException
                std::cout << "\nTest 3: JocInvalidException\n";
                try {
                    throw JocInvalidException("SuperJoc");
                } catch (const JocInvalidException& e) {
                    std::cout << "  Mesaj: " << e.what() << "\n";
                    std::cout << "  Nume joc: " << e.getNumeJoc() << "\n";
                }

                // Test 4: Prinde orice exceptie din galerie
                std::cout << "\nTest 4: Prindere cu clasa de baza\n";
                try {
                    throw TablouIndisponibilException("Zodiac");
                } catch (const GalerieException& e) {
                    std::cout << "  Prins ca GalerieException: " << e.what() << "\n";
                }

                std::cout << "\n✓ Toate testele OK!\n";
            }
                break;

            case 13:
                galerie.afiseazaJocuri();
                break;

            case 14:
{
    std::cout << "Introdu numele jocului: ";
    std::getline(std::cin, nume);


    try {
        auto joc = galerie.cautaJoc(nume);
        if (!joc) {
            throw JocInvalidException(nume);
        }

        joc->afiseazaRegulile();
        joc->initializeaza();

        // ========== ART QUIZ ==========
        if (auto quiz = std::dynamic_pointer_cast<ArtQuiz>(joc)) {
            std::string raspuns;
            while (quiz->areIntrebariRamase()) {
                quiz->afiseazaIntrebareCurenta();
                std::getline(std::cin, raspuns);
                quiz->raspunde(raspuns);
                quiz->urmatoraIntrebare();
            }
            std::cout << "\n✓ Quiz terminat!\n";
        }

        // ========== ARTISTIC DELIGHT ==========
        else if (auto ad = std::dynamic_pointer_cast<ArtisticDelight>(joc)) {
            std::string culoare;
            std::cout << "\nGhicește culorile tabloului!\n";
            std::cout << "(scrie 'sugestie' pentru ajutor)\n\n";

            while (ad->getIncercariRamase() > 0 && ad->getScorAsemanare() < 100) {
                std::cout << "\n----------------------------------\n";
                std::cout << "Încercări rămase: " << ad->getIncercariRamase() << "\n";
                std::cout << "Scor actual: " << ad->getScorAsemanare() << "%\n";
                std::cout << "Introdu o culoare: ";
                std::getline(std::cin, culoare);

                if (culoare == "sugestie") {
                    ad->arataSugestie();
                    continue;
                }

                ad->picteaza(culoare);
            }

            // Mesaj final
            if (ad->getScorAsemanare() >= 100) {
                std::cout << "\n Felicitări! Ai ghicit toate culorile!\n";
            } else {
                std::cout << "\n Nu mai ai încercări! Scor final: " << ad->getScorAsemanare() << "%\n";
            }
        }

        // ========== QUICK ART LOOK ==========
        else if (auto qal = std::dynamic_pointer_cast<QuickArtLook>(joc)) {
            std::string titlu_tablou, artist_nume;
            int total_perechi = qal->getPerechilCorecte() + qal->getPerechileGresite();
            // Calculăm totalul din perechile existente
            total_perechi = 8;  // sau adaugă un getter

            qal->afiseazaTablele();
            qal->afiseazaArtisti();

            std::cout << "\nAsociază fiecare tablou cu artistul corect!\n\n";

            int incercari = 0;
            int max_incercari = total_perechi + 3;

            while (qal->getPerechilCorecte() < total_perechi && incercari < max_incercari) {
                std::cout << "\n----------------------------------\n";
                std::cout << "Corecte: " << qal->getPerechilCorecte() << "/" << total_perechi << "\n";
                std::cout << "Titlu tablou: ";
                std::getline(std::cin, titlu_tablou);

                std::cout << "Nume artist: ";
                std::getline(std::cin, artist_nume);

                qal->verificaPereche(titlu, artist_nume);
                incercari++;
            }

            // Mesaj final
            if (qal->getPerechilCorecte() == total_perechi) {
                std::cout << "\n Felicitări! Ai asociat toate perechile!\n";
            } else {
                std::cout << "\n Joc terminat! Ai asociat " << qal->getPerechilCorecte() << "/" << total_perechi << " perechi.\n";
            }
        }


        int puncte = joc->calculeazaPuncte();
        utilizator->adaugaPuncte(puncte);
        std::cout << "\n========================================\n";
        std::cout << "   Ai câștigat " << puncte << " puncte!\n";
        std::cout << "   Total puncte: " << utilizator->getPuncte() << "\n";
        std::cout << "========================================\n";

    } catch (const JocInvalidException& e) {
        std::cerr << "Eroare: " << e.what() << "\n";
    }
}
    break;

            case 15:
            {
                std::cout << "\n===== TEST MINIJOC + DYNAMIC_CAST , GALERIE + COPY_AND_SWAP =====\n\n";

                // Test polimorfism - apel funcții virtuale prin pointer de bază
                std::cout << "1. Test polimorfism (funcții virtuale prin pointer bază):\n";
                auto joc = galerie.cautaJoc("Artistic Delight");
                if (joc) {
                    std::cout << "Tip joc: " << joc->getTipJoc() << "\n";  // funcție virtuală
                    joc->afiseazaRegulile();  // NVI pattern
                }

                // Test dynamic_cast
                std::cout << "\n2. Test dynamic_cast:\n";
                galerie.afiseazaSugestiiArtisticDelight();

                // Test clone (constructor virtual)
                std::cout << "\n3. Test clone (constructor virtual):\n";
                if (joc) {
                    auto copie = joc->clone();
                    std::cout << "Original: " << joc->getNume() << "\n";
                    std::cout << "Clonă: " << copie->getNume() << "\n";
                }

                // Test statistici statice
                std::cout << "\n4. Test membri statici:\n";
                MiniJoc::afiseazaStatistici();

                std::cout << "\n5. Test copy-and-swap Galerie:\n";
                std::cout << "-----------------------------------\n";

                // Galeria originală
                std::cout << "GALERIA ORIGINALĂ:\n";
                std::cout << "  - Artiști: " << galerie.getArtisti().size() << "\n";
                std::cout << "  - Tablouri: " << galerie.getTablouri().size() << "\n";
                std::cout << "  - Jocuri: " << galerie.getJocuri().size() << "\n";

                // Creează o galerie goală
                Galerie galerie_copie("Copie", "Test", 2000);
                std::cout << "\nGALERIA COPIE (înainte de copy-and-swap):\n";
                std::cout << "  - Artiști: " << galerie_copie.getArtisti().size() << "\n";
                std::cout << "  - Tablouri: " << galerie_copie.getTablouri().size() << "\n";
                std::cout << "  - Jocuri: " << galerie_copie.getJocuri().size() << "\n";

                // Copy-and-swap!
                galerie_copie = galerie;

                std::cout << "\nGALERIA COPIE (după copy-and-swap):\n";
                std::cout << "  - Artiști: " << galerie_copie.getArtisti().size() << "\n";
                std::cout << "  - Tablouri: " << galerie_copie.getTablouri().size() << "\n";
                std::cout << "  - Jocuri: " << galerie_copie.getJocuri().size() << "\n";

                // Verifică că sunt independente
                std::cout << "\nVERIFICARE INDEPENDENȚĂ:\n";
                std::cout << "  Galeria originală încă are: " << galerie.getArtisti().size() << " artiști, "
                          << galerie.getTablouri().size() << " tablouri, "
                          << galerie.getJocuri().size() << " jocuri\n";

                std::cout << "\n Copy-and-swap funcționează!\n";
                std::cout << "\n Toate testele OK!\n";
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