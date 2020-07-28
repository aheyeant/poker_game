
#ifndef SEM_ALI_POKERGAME_H
#define SEM_ALI_POKERGAME_H

#include <bits/types/stack_t.h>
#include "../GameBoard.h"
#include "../cards/cardCombinationsEngine/CombinationsEngineFactory.h"
#include "../cards/cardCombinationsEngine/WinnerComparator.h"

class PokerGame {
public:
    PokerGame(int playersCount);

    ~PokerGame();

private:
    void startGame();

    int oneCycleGame();

    bool manualPlayerCanGame();

    void printPlayerCannotGame();

    bool canContinuePlaying();

    void recalculatePlayersMoney();

    void giveOutCardOnTableAndPlayers();

    void openCardsFromTable(int count);


    ENextStep stepSwitcher(std::pair<ENextStep, int> step, int playerID);

    const int manualPlayerID;

    /**
     * Control if all players made bet
     */
    bool checkControl();

    void showPlayerStep(std::pair<ENextStep, int> step, int playerID);

    void restartCheck();

    void restartFold();

    void setEngineForPlayers(int cardsCountForCalculateChance);

    GameBoard * gameBoard;

    const int playersCounts;
};

#endif //SEM_ALI_POKERGAME_H
