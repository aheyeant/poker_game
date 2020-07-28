
#ifndef SEM_ALI_TABLECARDS_H
#define SEM_ALI_TABLECARDS_H

#include <vector>
#include <stdexcept>
#include <iostream>
#include "Card.h"
#include "../gameLogic/GameConstants.h"

class TableCards {
private:
    std::vector<Card> cardsOnTable;
    int openedCards;

public:
    TableCards();

    bool addCardOnTable(Card & card);

    /// method can throw exception
    void openCard(int i);

    std::vector<Card> getOpenedCards();

    void printCards();
};

#endif //SEM_ALI_TABLECARDS_H
