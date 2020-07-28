
#ifndef SEM_ALI_CARD_H
#define SEM_ALI_CARD_H

#include <string>
#include <utility>
#include "../gameLogic/GameConstants.h"

class Card {
private:
    std::string cardRank;
    std::string cardSuit;

public:
    int numOfCardRank;
    int numOfCardSuit;

    Card();

    Card (int numOfCardRank, int numOfCardSuit, std::string cardRank, std::string cardSuit);

    bool isCorrect();

    friend std::ostream & operator<<(std::ostream & os, const Card & card);

    friend bool operator<(const Card & left, const Card & right);

    friend bool operator>(const Card & left, const Card & right);
};


#endif //SEM_ALI_CARD_H
