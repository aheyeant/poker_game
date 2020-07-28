
#include "GameBoard.h"

GameBoard::GameBoard(int playersCount) : playersCount(playersCount){
    bank = 0;
    players = new PlayerAbstract*[playersCount];
    if (CHOOSE_RANDOM_PLAYER_MODEL) {
        setRandomPlayerModel();
    } else {
        setDefinedPlayerModel();
    }
}

GameBoard::~GameBoard() {
    for (int i = 0; i < playersCount; i++) {
        delete players[i];
    }
    delete[] players;
}

void GameBoard::setRandomPlayerModel() {
    players[0] = PlayerModelFactory::getManualModel();
    srand(time(nullptr));
    for (int i = 1; i < playersCount; i++) {
        players[i] = PlayerModelFactory::getPCModel(static_cast<int>(random()) % PLAYER_MODEL_COUNT + 1, PC_PLAYER_NAME[i - 1]);
    }
}

void GameBoard::setDefinedPlayerModel() {
    players[0] = PlayerModelFactory::getManualModel();
    for (int i = 1; i < playersCount; i++) {
        players[i] = PlayerModelFactory::getPCModel(PLAYER_MODELS[i - 1], PC_PLAYER_NAME[i - 1]);
    }
}

void GameBoard::showTableOnTerminal() {
    std::cout << "**********************************************" << std::endl;
    std::cout << "NAME         MONEY    CARDS" << std::endl;

    for (int i = 1; i < playersCount; i++) {
        players[i]->selfShow();
    }
    players[0]->selfShow();
    std::cout << "       Bank: " << blue << std::to_string(bank) << original << std::endl;

    tableCards.printCards();
    std::cout << "**********************************************" << std::endl;

}

void GameBoard::restart() {
    bank = 0;
    cardStock = CardStock();
    tableCards = TableCards();
    for (int i = 0; i < playersCount; i++) {
        players[i]->relocateCards();
    }

}



