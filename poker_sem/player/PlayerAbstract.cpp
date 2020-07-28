
#include "PlayerAbstract.h"

PlayerAbstract::PlayerAbstract(std::string playerName) {
    this->playerName = std::move(playerName);
    this->cardsCount = 0;
    this->maxPlayerCards = MAX_CARD_ON_PLAYER_HANDS + MAX_CARD_ON_TABLE;
    this->currentPlayingCards = new Card[maxPlayerCards];
    this->engine = nullptr;
}

PlayerAbstract::~PlayerAbstract() {
    delete[] currentPlayingCards;
    delete engine;
}

void PlayerAbstract::addCard(Card &card) {
    if (cardsCount == maxPlayerCards)
        throw std::logic_error("Cannot add more cards than " + std::to_string(maxPlayerCards));
    if (cardsCount < MAX_CARD_ON_PLAYER_HANDS) playerCardsOnTable.emplace_back(card);
    currentPlayingCards[cardsCount++] = card;
    bobbleSort();
}

void PlayerAbstract::bobbleSort() {
    //todo control swap
    for (int i = 0; i < cardsCount - 1 ; i++) {
        bool swap = false;
        for (int j = 0; j < cardsCount - i - 1; j++) {
            if (currentPlayingCards[i] < currentPlayingCards[j]) {
                Card tmp = currentPlayingCards[i];
                currentPlayingCards[i] = currentPlayingCards[j];
                currentPlayingCards[j] = tmp;
                swap = true;
            }
        }
        if (!swap) return;
    }
}

void PlayerAbstract::setCombinationEngine(CombinationsEngineAbstract * combinationsEngine) {
    delete this->engine;
    this->engine = combinationsEngine;
}

double PlayerAbstract::getRandChance() {
    srand(time(nullptr));
    return (double)random() / (double)RAND_MAX;
}

Card *PlayerAbstract::getPlayingCards() {
    return currentPlayingCards;
}

void PlayerAbstract::selfShow() {
    if (gameStatistics.inGame) {


        std::cout << std::setw(12) << std::left << playerName << " " << std::setw(6) << std::left << blue << gameStatistics.playerMoney << original;
        if (gameStatistics.fold) {
            //todo make red
            std::cout << "   Fold" << std::endl;
        } else {
            //todo make some colour
            std::cout << red << "   [X] [X]" << original <<  std::endl;
        }
    }
}

void PlayerAbstract::relocateCards() {
    delete[] currentPlayingCards;
    //todo max_player_cards
    currentPlayingCards = new Card[maxPlayerCards];
    playerCardsOnTable.clear();
    cardsCount = 0;
}

