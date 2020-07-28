
#ifndef SEM_ALI_CARDSTOCK_H
#define SEM_ALI_CARDSTOCK_H

#include <vector>
#include "Card.h"
#include <iostream>
#include "../gameLogic/GameConstants.h"

class CardStock {
private:
    int cardsCount = 0;

    std::vector<Card> cardStock;

    void cardsInit();

    void cardsShuffle();

    static std::string getCardRank(int rank);

    static std::string getCardSuite(int suite);

public:
    CardStock();

    /**
     * Function can throw exception
     * @return last card
     */
    Card & getLastCard();


    /**
    * Only for test
    */
    void printCardStock();
};

#endif //SEM_ALI_CARDSTOCK_H
