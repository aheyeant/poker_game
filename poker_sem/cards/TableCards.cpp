
#include "TableCards.h"

TableCards::TableCards() : openedCards(0) {}

bool TableCards::addCardOnTable(Card &card) {
    if (cardsOnTable.size() < MAX_CARD_ON_TABLE) {
        cardsOnTable.emplace_back(card);
        return true;
    } else return false;
}

void TableCards::openCard(int i = 1) {
    if (openedCards + i <= MAX_CARD_ON_TABLE) {
        openedCards += i;
    } else throw std::logic_error("All card was opened.");
}

std::vector<Card> TableCards::getOpenedCards() {
    std::vector<Card> opened;
    opened.reserve(openedCards);
    for (int i = 0; i < openedCards; i++) {
        opened.emplace_back(cardsOnTable.at(i));
    }
    return opened;
}

void TableCards::printCards() {
    std::cout << "Cards on table" << std::endl;
    for (int i = 0; i < cardsOnTable.size(); i++) {
        if (i >= openedCards) {
            //todo make red
            std::cout << "\t\t\t" << red << "[X]" << original << std::endl;
        } else {
            std::cout << "\t\t\t" << cardsOnTable.at(i) << std::endl;
        }

    }
}


