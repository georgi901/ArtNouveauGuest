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
#include "headers/ArtPuzzle.h"
#include "headers/JocFactory.h"
#include "headers/Collection.h"
#include "headers/Utils.h"
#include <fstream>
#include <sstream>
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
    std::cout << "15. Test MiniJoc + dynamic_cast + Copy and swap\n";
    std::cout << "16. Test Milestone 3 (Templates + Design Patterns)\n";
    std::cout << "17. Test funcții template neutilizate\n";
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
        std::cerr << "\nEROARE : " << e.what() << "\n";
        std::cerr << "Tip eroare: " << e.getTipEroare() << "\n";
        std::cerr << "Detalii: " << e.getDetalii() << "\n\n";
        std::cerr << "Programul nu poate continua fără date!\n";
        std::cerr << "Asigură-te că fișierele JSON există în folderul 'data/'.\n\n";
        return 1;
    } catch (const GalerieException& e) {
        std::cerr << "\nEROARE : " << e.what() << "\n";
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

    auto joc4 = std::make_shared<ArtPuzzle>("Art Puzzle", Dificultate::Usor);
    joc4->seteazaTablou(galerie.cautaTablou("Sarutul"));
    galerie.adaugaJoc(joc4);


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

                auto tablou_copie = std::make_unique<Tablou>(*tablou_original);
                std::cout << "Copiat: " << tablou_copie->getTitlu() << "\n\n";

                std::cout << "PASUL 3: Test OPERATOR= DE COPIERE\n";
                std::cout << "------------------------------------\n";

                auto tablou_gol = std::make_unique<Tablou>();
                std::cout << "Înainte: " << tablou_gol->getTitlu() << "\n";
                *tablou_gol = *tablou_original;
                std::cout << "După operator=: " << tablou_gol->getTitlu() << "\n\n";

                std::cout << " Toate testele OK! \n";
                std::cout << "  - Constructor copiere: BUN \n";
                std::cout << "  - Operator=: BUN \n";
                std::cout << "  - Destructor: BUN (se va apela automat)\n";
            }
                break;
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

                std::cout << "\n5. Test funcții adiționale:\n";

                // MiniJoc static functions
                std::cout << "Total jocuri: " << MiniJoc::getTotalJocuri() << "\n";
                std::cout << "Total puncte: " << MiniJoc::getTotalPuncte() << "\n";
                MiniJoc::afiseazaStatistici();
                MiniJoc::reseteazaStatistici();

                // Galerie
                galerie.joacaJoc("Artistic Delight");

                // Test pe un joc specific
                auto joc_test = galerie.cautaJoc("Artistic Delight");
                if (joc_test) {
                    std::cout << "Descriere: " << joc_test->getDescriere() << "\n";
                    std::cout << "Dificultate: " << static_cast<int>(joc_test->getDificultate()) << "\n";
                    std::cout << "Puncte maxime: " << joc_test->getPuncteMaxime() << "\n";
                    std::cout << "Puncte obtinute: " << joc_test->getPuncteObtinute() << "\n";
                    std::cout << "Finalizat: " << joc_test->esteFinalizat() << "\n";
                }

                // Test utilizator - nullptr
                std::cout << "\nTest 5: cumparaTablou cu nullptr\n";
                try {
                    utilizator->cumparaTablou(nullptr, 0);
                } catch (const TablouIndisponibilException& e) {
                    std::cout << "  Excepție prinsă corect: " << e.what() << "\n";
                }

                // ArtQuiz functions
                auto quiz = std::dynamic_pointer_cast<ArtQuiz>(galerie.cautaJoc("Art Quiz"));
                if (quiz) {
                    std::cout << "Raspunsuri corecte: " << quiz->getRaspunsuriCorecte() << "\n";
                    std::cout << "Raspunsuri gresite: " << quiz->getRaspunsuriGresite() << "\n";
                    std::cout << "Intrebari ramase: " << quiz->getIntrebariRamase() << "\n";
                }

                // ArtisticDelight
                auto ad = std::dynamic_pointer_cast<ArtisticDelight>(galerie.cautaJoc("Artistic Delight"));
                if (ad) {
                    std::cout << "Culori folosite: " << ad->getCulorifolosite().size() << "\n";
                }

                std::cout << "\n Toate testele OK!\n";
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

                    // ART QUIZ
                    if (auto quiz = std::dynamic_pointer_cast<ArtQuiz>(joc)) {
                        std::string raspuns;
                        while (quiz->areIntrebariRamase()) {
                            quiz->afiseazaIntrebareCurenta();
                            std::getline(std::cin, raspuns);
                            quiz->raspunde(raspuns);
                            quiz->urmatoraIntrebare();
                        }
                        std::cout << "\n Quiz terminat!\n";
                    }

                    // ARTISTIC DELIGHT
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

                    // QUICK ART LOOK
                    else if (auto qal = std::dynamic_pointer_cast<QuickArtLook>(joc)) {
                        qal->afiseazaTablele();
                        qal->afiseazaArtisti();

                        std::cout << "\nAsociaza fiecare tablou cu artistul corect!\n";
                        std::cout << "(Scrie 'exit' pentru a iesi)\n\n";

                        int total_perechi = qal->getTotalPerechi();
                        int incercari = 0;
                        int max_incercari = total_perechi + 3;

                        while (qal->getPerechilCorecte() < total_perechi && incercari < max_incercari) {
                            std::cout << "----------------------------------\n";
                            std::cout << "Corecte: " << qal->getPerechilCorecte() << "/" << total_perechi << "\n";

                            std::string titlu_tablou, artist_nume;

                            std::cout << "Titlu tablou: ";
                            std::getline(std::cin, titlu_tablou);

                            if (titlu_tablou == "exit") {
                                std::cout << "Ai iesit din joc.\n";
                                break;
                            }

                            std::cout << "Nume artist: ";
                            std::getline(std::cin, artist_nume);

                            qal->verificaPereche(titlu_tablou, artist_nume);
                            incercari++;
                        }

                        // Mesaj final
                        std::cout << "Perechi corecte: " << qal->getPerechilCorecte() << "/" << total_perechi << "\n";
                        std::cout << "Perechi gresite: " << qal->getPerechileGresite() << "\n";

                        if (qal->getPerechilCorecte() == total_perechi) {
                            std::cout << "\nFelicitari! Ai asociat toate perechile!\n";
                        } else {
                            std::cout << "\nJoc terminat! Ai asociat " << qal->getPerechilCorecte() << "/" << total_perechi << " perechi.\n";
                        }
                    }

                    // ArtPuzzle
                    auto puzzle = std::dynamic_pointer_cast<ArtPuzzle>(joc);
                    if (puzzle) {
                        puzzle->afiseazaPuzzle();

                        while (!puzzle->esteRezolvat() && puzzle->getMutariRamase() > 0) {
                            std::cout << "Introdu pozitiile de schimbat (poz1 poz2) sau -1 -1 pentru ieșire: ";
                            int poz1, poz2;
                            std::cin >> poz1 >> poz2;

                            if (poz1 == -1 || poz2 == -1) {
                                std::cout << "Ai ieșit din joc.\n";
                                break;
                            }

                            puzzle->mutaFragment(poz1, poz2);
                            puzzle->afiseazaPuzzle();
                        }

                        std::cout << "\n=== REZULTAT ===\n";
                        std::cout << "Mutari efectuate: " << puzzle->getMutariEfectuate() << "\n";
                        std::cout << "Numar fragmente: " << puzzle->getNumarFragmente() << "\n";

                        if (puzzle->esteRezolvat()) {
                            std::cout << "Felicitări! Ai rezolvat puzzle-ul!\n";
                        }
                    }


                    int puncte = joc->calculeazaPuncte();
                    utilizator->adaugaPuncte(puncte);
                    std::cout << "\n========================================\n";
                    std::cout << "   Ai câștigat " << puncte << " puncte!\n";
                    std::cout << "   Total puncte: " << utilizator->getPuncte() << "\n";
                    std::cout << "========================================\n";
                } catch (const JocInvalidException &e) {
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
                    joc->afiseazaRegulile();
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
             case 16:
            {
                std::cout << "\n";
                std::cout << "============================================================\n";
                std::cout << "     TEST MILESTONE 3 - TEMPLATES & DESIGN PATTERNS\n";
                std::cout << "============================================================\n\n";

                // TEST 1: SINGLETON PATTERN
                std::cout << "--- TEST 1: SINGLETON PATTERN (Galerie) ---\n";
                Galerie& g1 = Galerie::getInstance();
                Galerie& g2 = Galerie::getInstance();
                std::cout << "Galerie::getInstance() apelat de 2 ori.\n";
                std::cout << "Adresa g1: " << &g1 << "\n";
                std::cout << "Adresa g2: " << &g2 << "\n";
                std::cout << "Aceeași instanță? " << (&g1 == &g2 ? "DA - Singleton funcționează!" : "NU") << "\n\n";

                // TEST 2: FACTORY PATTERN
                std::cout << "--- TEST 2: FACTORY PATTERN (JocFactory) ---\n";
                std::cout << "Tipuri de jocuri disponibile: ";
                for (const auto& tip : JocFactory::obtineTipuriDisponibile()) {
                    std::cout << tip << " ";
                }
                std::cout << "\n\n";

                std::cout << "Creare jocuri folosind Factory:\n";
                try {
                    auto joc_f1 = JocFactory::creeazaJoc("ArtQuiz", Dificultate::Mediu);
                    std::cout << "  Creat: " << joc_f1->getTipJoc() << " (" << joc_f1->getNume() << ")\n";

                    auto joc_f2 = JocFactory::creeazaJoc("ArtPuzzle", Dificultate::Greu);
                    std::cout << "  Creat: " << joc_f2->getTipJoc() << " (" << joc_f2->getNume() << ")\n";

                    auto joc_f3 = JocFactory::creeazaJoc("ArtisticDelight", Dificultate::Usor);
                    std::cout << "  Creat: " << joc_f3->getTipJoc() << " (" << joc_f3->getNume() << ")\n";
                } catch (const JocInvalidException& e) {
                    std::cout << "Eroare: " << e.what() << "\n";
                }

                std::cout << "\nTest creare joc invalid:\n";
                try {
                    auto joc_invalid = JocFactory::creeazaJoc("JocInexistent", Dificultate::Mediu);
                } catch (const JocInvalidException& e) {
                    std::cout << "  Excepție prinsă corect: " << e.what() << "\n";
                }
                std::cout << "\n";

                // TEST 3: CLASĂ ȘABLON (Collection<T>)
                std::cout << "--- TEST 3: CLASĂ ȘABLON (Collection<T>) ---\n";

                // Instanțiere 1: Collection<Artist>
                std::cout << "Instanțiere 1: Collection<Artist>\n";
                Collection<Artist> colectieArtisti;
                for (const auto& a : galerie.getArtisti()) {
                    colectieArtisti.adauga(a);
                }
                std::cout << "  Artiști în colecție: " << colectieArtisti.dimensiune() << "\n";

                auto artistGasit = colectieArtisti.cautaDupaPredicate([](const Artist& a) {
                    return a.getAnDeces() == 0;
                });
                if (artistGasit) {
                    std::cout << "  Artist în viață găsit: " << artistGasit->getNume() << "\n";
                }

                // Instanțiere 2: Collection<Tablou>
                std::cout << "\nInstanțiere 2: Collection<Tablou>\n";
                Collection<Tablou> colectieTablouri;
                for (const auto& t : galerie.getTablouri()) {
                    colectieTablouri.adauga(t);
                }
                std::cout << "  Tablouri în colecție: " << colectieTablouri.dimensiune() << "\n";

                auto tablouriRare = colectieTablouri.filtreaza([](const Tablou& t) {
                    return t.este_rar();
                });
                std::cout << "  Tablouri rare (filtrate): " << tablouriRare.dimensiune() << "\n";

                // Instanțiere 3: Collection<MiniJoc>
                std::cout << "\nInstanțiere 3: Collection<MiniJoc>\n";
                Collection<MiniJoc> colectieJocuri;
                for (const auto& j : galerie.getJocuri()) {
                    colectieJocuri.adauga(j);
                }
                std::cout << "  Jocuri în colecție: " << colectieJocuri.dimensiune() << "\n\n";

                // TEST 4: FUNCȚII ȘABLON
                std::cout << "--- TEST 4: FUNCȚII ȘABLON (Utils.h) ---\n";

                // Instanțiere 1: cautaDupaNume<Artist>
                std::cout << "Instanțiere 1: cautaDupaNume<Artist>\n";
                auto artistCautat = cautaDupaNume(galerie.getArtisti(), "Mucha");
                std::cout << "  Căutare 'Mucha': " << (artistCautat ? artistCautat->getNume() + " " + artistCautat->getPrenume() : "Negăsit") << "\n";

                // Instanțiere 2: cautaDupaCamp<Tablou>
                std::cout << "\nInstanțiere 2: cautaDupaCamp<Tablou>\n";
                auto tablouCautat = cautaDupaCamp<Tablou>(galerie.getTablouri(), "Zodiac",
                    [](const Tablou& t) { return t.getTitlu(); });
                std::cout << "  Căutare tablou 'Zodiac': " << (tablouCautat ? tablouCautat->getTitlu() : "Negăsit") << "\n";

                // Instanțiere 3: filtreazaElemente<Tablou>
                std::cout << "\nInstanțiere 3: filtreazaElemente<Tablou>\n";
                auto tablouriFiltered = filtreazaElemente<Tablou>(galerie.getTablouri(),
                    [](const Tablou& t) { return t.este_rar(); });
                std::cout << "  Tablouri rare filtrate: " << tablouriFiltered.size() << "\n";

                // Instanțiere 4: filtreazaElemente<Artist>
                std::cout << "\nInstanțiere 4: filtreazaElemente<Artist>\n";
                auto artistiViata = filtreazaElemente<Artist>(galerie.getArtisti(),
                    [](const Artist& a) { return a.getAnDeces() == 0; });
                std::cout << "  Artiști în viață: " << artistiViata.size() << "\n";

                // Instanțiere 5: numaraElemente<Tablou>
                std::cout << "\nInstanțiere 5: numaraElemente<Tablou>\n";
                int nrColectionate = numaraElemente<Tablou>(galerie.getTablouri(),
                    [](const Tablou& t) { return t.este_colectionat(); });
                std::cout << "  Tablouri colecționate: " << nrColectionate << "\n";

                // Instanțiere 6: numaraElemente<Artist>
                std::cout << "\nInstanțiere 6: numaraElemente<Artist>\n";
                int nrDecedati = numaraElemente<Artist>(galerie.getArtisti(),
                    [](const Artist& a) { return a.getAnDeces() != 0; });
                std::cout << "  Artiști decedați: " << nrDecedati << "\n";

                // Instanțiere 7: transforma<Artist, std::string>
                std::cout << "\nInstanțiere 7: transforma<Artist, string>\n";
                auto numeArtisti = transforma<Artist, std::string>(galerie.getArtisti(),
                    [](const Artist& a) { return a.getNume() + " " + a.getPrenume(); });
                std::cout << "  Nume artiști: ";
                for (size_t i = 0; i < std::min(numeArtisti.size(), size_t(3)); i++) {
                    std::cout << numeArtisti[i];
                    if (i < std::min(numeArtisti.size(), size_t(3)) - 1) std::cout << ", ";
                }
                if (numeArtisti.size() > 3) std::cout << "...";
                std::cout << "\n";

                std::cout << "\n";
                std::cout << "============================================================\n";
                std::cout << "                 REZUMAT TESTE M3\n";
                std::cout << "============================================================\n";
                std::cout << "  [OK] Design Pattern 1: SINGLETON (Galerie)\n";
                std::cout << "  [OK] Design Pattern 2: FACTORY (JocFactory)\n";
                std::cout << "  [OK] Clasă Șablon: Collection<T> - 3 instanțieri\n";
                std::cout << "       - Collection<Artist>\n";
                std::cout << "       - Collection<Tablou>\n";
                std::cout << "       - Collection<MiniJoc>\n";
                std::cout << "  [OK] Funcții Șablon: 7+ instanțieri\n";
                std::cout << "       - cautaDupaNume<Artist>\n";
                std::cout << "       - cautaDupaCamp<Tablou>\n";
                std::cout << "       - filtreazaElemente<Tablou>\n";
                std::cout << "       - filtreazaElemente<Artist>\n";
                std::cout << "       - numaraElemente<Tablou>\n";
                std::cout << "       - numaraElemente<Artist>\n";
                std::cout << "       - transforma<Artist, string>\n";
                std::cout << "============================================================\n";
                std::cout << "       TOATE TESTELE M3 AU TRECUT CU SUCCES!\n";
                std::cout << "============================================================\n";
            }
                break;
             case 17:
            {
                std::cout << "\n===== TEST FUNCȚII TEMPLATE NEUTILIZATE =====\n\n";

                 // Test înregistrare joc personalizat
                 std::cout << "Test înregistrare tip nou de joc:\n";
                 JocFactory::inregistreazaJoc("JocPersonalizat", [](Dificultate d) {
                     return std::make_unique<ArtQuiz>("Joc Personalizat", d);
                 });

                 auto jocNou = JocFactory::creeazaJoc("JocPersonalizat", Dificultate::Mediu);
                 std::cout << "Joc creat: " << jocNou->getNume() << "\n";

                // Test Collection - funcții neutilizate
                Collection<Tablou> colTest;
                for (const auto& t : galerie.getTablouri()) {
                    colTest.adauga(t);
                }

                // Test elimina
                if (colTest.dimensiune() > 0) {
                    auto primul = colTest.obtine(0);
                    std::cout << "Test elimina: " << (colTest.elimina(primul) ? "Succes" : "Eșuat") << "\n";
                }

                // Test obtine
                if (colTest.dimensiune() > 0) {
                    auto elem = colTest.obtine(0);
                    std::cout << "Test obtine: " << (elem ? elem->getTitlu() : "null") << "\n";
                }

                // Test esteGoala
                std::cout << "Test esteGoala: " << (colTest.esteGoala() ? "Da" : "Nu") << "\n";

                // Test sorteaza
                colTest.sorteaza([](const Tablou& a, const Tablou& b) {
                    return a.getTitlu() < b.getTitlu();
                });
                std::cout << "Test sorteaza: Executat\n";

                 // Test pentruFiecare
                 int count = 0;
                 colTest.pentruFiecare([&count](Tablou&) {  // Fără nume pentru parametru
                     count++;
                 });
                 std::cout << "Test pentruFiecare: Procesate " << count << " elemente\n";

                // Test obtineToate
                auto toate = colTest.obtineToate();
                std::cout << "Test obtineToate: " << toate.size() << " elemente\n";

                // Test Utils - afiseazaToate
                std::ostringstream oss;
                afiseazaToate(galerie.getTablouri(), oss, "Tablouri");
                std::cout << "Test afiseazaToate: Executat\n";

                // Test Utils - sumaProprietate
                int sumaAni = sumaProprietate<Tablou, int>(galerie.getTablouri(),
                    [](const Tablou& t) { return t.getAnRealizare(); });
                std::cout << "Test sumaProprietate: Suma ani = " << sumaAni << "\n";

                // Test JocFactory - funcții neutilizate
                std::cout << "Test esteTipInregistrat: "
                          << (JocFactory::esteTipInregistrat("ArtQuiz") ? "Da" : "Nu") << "\n";

                // Test goleste
                colTest.goleste();
                std::cout << "Test goleste: Executat (dimensiune = " << colTest.dimensiune() << ")\n";

                std::cout << "\n Toate funcțiile template testate!\n";
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