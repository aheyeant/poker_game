
#ifndef SEM_ALI_PLAYERABSTRACT_H
#define SEM_ALI_PLAYERABSTRACT_H

#include <vector>
#include <utility>
#include <stdexcept>
#include <iostream>
#include <iomanip>
#include "../cards/Card.h"
#include "../gameLogic/ENextStep.h"
#include "../gameLogic/GameConstants.h"
#include "../cards/cardCombinationsEngine/CombinationsEngineAbstract.h"
#include "GameStatistics .h"

class PlayerAbstract {
protected:
    std::string playerName;

    int maxPlayerCards;
    int cardsCount;

    // all card which was opened
    Card * currentPlayingCards;

    CombinationsEngineAbstract * engine;

    std::vector<Card> playerCardsOnTable;


    void bobbleSort();

    /**
     * Get random [0.0 .. 1.0]
     */
    static double getRandChance();

public:
    explicit PlayerAbstract(std::string playerName);

    virtual ~PlayerAbstract() = 0;

    GameStatistics gameStatistics;

    /**
     * Method can throw exception
     * @param card
     */
    void addCard(Card & card);

    void relocateCards();

    void setCombinationEngine(CombinationsEngineAbstract * combinationsEngine);

    Card * getPlayingCards();

    virtual std::pair<ENextStep, int> getNextStep(ENextStep nextStep, int bet) = 0;

    void selfShow();

    inline std::string getName() { return playerName;}
};


#endif //SEM_ALI_PLAYERABSTRACT_H
