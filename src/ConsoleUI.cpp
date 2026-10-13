#include "../headers/ConsoleUI.h"

#include <iostream>

void ConsoleUI::displayMenu() {
    std::cout << "\n========================================\n";
    std::cout << "      ART GALLERY - MAIN MENU\n";
    std::cout << "========================================\n";
    std::cout << "1.  Display all artists\n";
    std::cout << "2.  Display all paintings\n";
    std::cout << "3.  Search artist (minimal profile)\n";
    std::cout << "4.  Search artist (full profile)\n";
    std::cout << "5.  Search painting (minimal details)\n";
    std::cout << "6.  Search painting (full details)\n";
    std::cout << "7.  Display full gallery\n";
    std::cout << "8.  Test user and collection\n";
    std::cout << "9.  Display artist statistics\n";
    std::cout << "10. Rare paintings by an artist\n";
    std::cout << "11. Test requirements (Painting)\n";
    std::cout << "12. Test exceptions\n";
    std::cout << "13. Display available games\n";
    std::cout << "14. Play a game\n";
    std::cout << "15. Test MiniGame + dynamic_cast + copy and swap\n";
    std::cout << "16. Test milestone 3 (templates + design patterns)\n";
    std::cout << "17. Test unused template functions\n";
    std::cout << "0.  Exit\n";
    std::cout << "========================================\n";
    std::cout << "Choose an option: ";
}
