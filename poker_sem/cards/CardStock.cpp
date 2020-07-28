
#include "CardStock.h"

void CardStock::cardsInit() {
    for (int i = 1; i < CARD_SUITES  + 1; i++) {
        for (int j = 2; j < CARD_RANKS + 2; j++) {
            cardsCount++;
            cardStock.emplace_back(j, i, getCardRank(j), getCardSuite(i));
        }
    }
}

std::string CardStock::getCardSuite(int suite) {
    switch (suite) {
        case 1: return "Hearts";
        case 2: return "Diamonds";
        case 3: return "Club";
        case 4: return "Spad";
        default: return "";
    }
}

std::string CardStock::getCardRank(int rank) {
    switch (rank) {
        case 11: return "Jack";
        case 12: return "Queen";
        case 13: return "King";
        case 14: return "Ace";
        default: return std::to_string( rank );
    }
}

void CardStock::cardsShuffle() {
    long randPosition = 0;
    srand((unsigned int)time(nullptr));

    for (long i = 0; i < cardsCount; i++) {
        randPosition = random() % cardsCount;
        while (randPosition == i) {
            randPosition = random() % cardsCount;
        }
        Card firstTmp = cardStock.at(i);
        Card secondTmp = cardStock.at(randPosition);

        cardStock.at(i) = secondTmp;
        cardStock.at(randPosition) = firstTmp;
    }
}

void CardStock::printCardStock() {
    std::cout << "Card stock" << std::endl;
    for (int i = 0; i < cardsCount; i++) {

    }


    std::cout << "---- start printing card stock ----" << std::endl;
    for (int i = 0; i < cardsCount; i++) {
        std::cout << i + 1 << ": " << cardStock.at(i) << std::endl;
    }
    std::cout << "---- finish printing card stock ----" << std::endl;

}

CardStock::CardStock() {
    cardsInit();
    cardsShuffle();
}

Card & CardStock::getLastCard() {
    //todo control exception
    if (cardsCount == 0) throw std::logic_error("Card stock is empty");
    return cardStock.at(--cardsCount);
}
