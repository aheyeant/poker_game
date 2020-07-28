
#include "Card.h"



Card::Card (int numOfCardRank, int numOfCardSuit, std::string cardRank, std::string cardSuit) : numOfCardRank(numOfCardRank),
                                                                                                numOfCardSuit(numOfCardSuit),
                                                                                                cardRank(std::move(cardRank)),
                                                                                                cardSuit(std::move(cardSuit)) {}


std::ostream & operator<<(std::ostream & os, const Card & card) {
    std::string delimiter = " of ";
    return os << green << card.cardRank << delimiter << card.cardSuit << original;
}

bool Card::isCorrect() {
    return !(cardSuit.empty() || cardRank.empty());
}

Card::Card() {
    numOfCardRank = 0;
    cardRank = "";
    cardSuit = "";
}

bool operator<(const Card & left, const Card & right) {
    return left.numOfCardRank < right.numOfCardRank;
}

bool operator>(const Card & left, const Card & right) {
    return left.numOfCardRank > right.numOfCardRank;
}