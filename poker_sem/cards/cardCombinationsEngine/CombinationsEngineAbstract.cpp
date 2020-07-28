
#include "CombinationsEngineAbstract.h"

CombinationsEngineAbstract::CombinationsEngineAbstract(const Card *cards) : cards(cards) {}

CombinationsEngineAbstract::~CombinationsEngineAbstract() = default;

std::vector<ECombinations> CombinationsEngineAbstract::getAllCombinations() {
    std::vector<ECombinations> v;
    v.emplace_back(ECombinations::HIGH_CARD);
    v.emplace_back(ECombinations::ONE_PAIR);
    v.emplace_back(ECombinations::TWO_PAIRS);
    v.emplace_back(ECombinations::THREE_OF_A_KIND);
    v.emplace_back(ECombinations::STRAIGHT);
    v.emplace_back(ECombinations::FLUSH);
    v.emplace_back(ECombinations::FULL_HOUSE);
    v.emplace_back(ECombinations::FOUR_OF_A_KIND);
    v.emplace_back(ECombinations::STRAIGHT_FLUSH);
    v.emplace_back(ECombinations::ROYAL_FLUSH);

    return v;
}

int CombinationsEngineAbstract::getMaxRank(int cardsCount) {
    int maxRank = 0;
    for (int i = 0; i < cardsCount; i++) {
        if (maxRank < cards[i].numOfCardRank) maxRank = cards[i].numOfCardRank;
    }
    return maxRank;
}

int CombinationsEngineAbstract::getMaxRankWithSuit(int cardCount, int suit) {
    int maxRank = 0;
    for (int i = 0; i < cardCount; i++) {
        if (cards[i].numOfCardSuit == suit) {
            if (maxRank < cards[i].numOfCardRank) maxRank = cards[i].numOfCardRank;
        }
    }
    return maxRank;
}
