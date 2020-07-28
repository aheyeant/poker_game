
#include <iostream>
#include "TerminalMenu.h"
#include "gameLogic/PokerGame.h"

TerminalMenu::TerminalMenu() = default;

void TerminalMenu::run() {
    int readValue = 0;
    while (true) {
        while (true) {
            std::cout << "1: Start game(6 players)\n" << "2: Choose quantity of players and start\n" << "3: Exit" << std::endl;
            std::cin >> readValue;
            if (readValue != 1 && readValue != 2 && readValue != 3) {
                std::cout << "Write number 1, 2 or 3" << std::endl;
            } else {
                if (readValue == 1) {
                    PokerGame pokerGame(6);
                }
                if (readValue == 2) {
                    while (true) {
                        std::cout <<"Chose quantity of players 2 - 6 or 0 for Exit" << std::endl;
                        std::cin >> readValue;
                        if (readValue <= 6 && readValue >= 2) {
                            PokerGame pokerGame(readValue);
                        }
                        if (readValue == 0) break;
                    }
                }
                if (readValue == 3) return;
             }
        }

    }
}
