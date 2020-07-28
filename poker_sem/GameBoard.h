
#ifndef SEM_ALI_GAMEBOARD_H
#define SEM_ALI_GAMEBOARD_H


#include "player/PlayerAbstract.h"
#include "cards/CardStock.h"
#include "cards/TableCards.h"
#include "player/playerModels/PlayerModelFactory.h"

class GameBoard {
private:

public:
    explicit GameBoard(int playersCount);

    ~GameBoard();

    PlayerAbstract ** players;

    CardStock cardStock;

    TableCards tableCards;

    int bank;

    int playersCount;

    void showTableOnTerminal();

    void restart();

private:
    void setRandomPlayerModel();

    void setDefinedPlayerModel();
};


#endif //SEM_ALI_GAMEBOARD_H
