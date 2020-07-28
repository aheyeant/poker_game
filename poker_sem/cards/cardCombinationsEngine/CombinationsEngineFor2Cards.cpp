
#include "CombinationsEngineFor2Cards.h"

CombinationsEngineFor2Cards::CombinationsEngineFor2Cards(const Card *cards) : CombinationsEngineAbstract(cards), cardsCount(2) {}

double CombinationsEngineFor2Cards::getSumChance() {
    double sum = 0.0;
    for (int i = 1; i < 11; i++) {
         sum += chanceMap[ECombinations(i)];
    }
    return sum;
}

double CombinationsEngineFor2Cards::getBestChance() {
    double max = 0.0;
    for (int i = 1; i < 11; i++) {
        if (max < chanceMap[ECombinations(i)]) {
            max = chanceMap[ECombinations(i)];
        }
    }
    return max;
}

ECombinations CombinationsEngineFor2Cards::getBestAchievedCombinations() {
    for (int i = 1; i < 11; i++) {
        if (!achievedMap[ECombinations(i)]) return ECombinations(i - 1);
    }
    return Ec::HIGH_CARD;
}

std::map<ECombinations, bool> CombinationsEngineFor2Cards::getAchievedCombinationsMap() {
    return achievedMap;
}

std::map<ECombinations, double> CombinationsEngineFor2Cards::getPotentialCombinationChance() {
    return chanceMap;
}

void CombinationsEngineFor2Cards::recalculate() {
    for(ECombinations e: getAllCombinations()) {
        achievedMap.insert(std::pair<ECombinations, bool>(e, false));
        chanceMap.insert(std::pair<ECombinations, double >(e, 0.0));
    }
    calculateChanceHighCard();
    calculateChanceOnePair();
    calculateChanceTwoPair();
    calculateChanceTreeOfAKind();
    calculateChanceStraight();
    calculateChanceFlush();
    calculateChanceFullHouse();
    calculateChanceFourOfAKind();
    calculateChanceStraightFlush();
    calculateChanceRoyalFlush();
}

void CombinationsEngineFor2Cards::calculateChanceHighCard() {
    int biggestRank = getMaxRank(2);
    double chance = (50 - (biggestRank * 4) - 5) / (50.);
    chanceMap[Ec::HIGH_CARD] = chance;
    achievedMap[Ec::HIGH_CARD] = true;
}

void CombinationsEngineFor2Cards::calculateChanceOnePair() {
    if (cards[0].numOfCardRank == cards[1].numOfCardRank) {
        achievedMap[Ec::ONE_PAIR] = true;
        chanceMap[Ec::ONE_PAIR] = 1.0 / (1 + 14 - cards[0].numOfCardRank);
        return;
    }
    int biggestRank = cards[0].numOfCardRank > cards[1].numOfCardRank ? cards[0].numOfCardRank : cards[1].numOfCardRank;
    double chance = ((14 - biggestRank) * 4 + 3) / (50.);
    chanceMap[Ec::ONE_PAIR] = chance;
}

void CombinationsEngineFor2Cards::calculateChanceTwoPair() {
    if (achievedMap[Ec::ONE_PAIR]) {
        chanceMap[Ec::TWO_PAIRS] = 3 / (50.);
        return;
    }
    chanceMap[Ec::TWO_PAIRS] = 6 / (50.);
}

void CombinationsEngineFor2Cards::calculateChanceTreeOfAKind() {
    if (achievedMap[Ec::ONE_PAIR]) {
        chanceMap[Ec::THREE_OF_A_KIND] = 2 / (50.);
        return;
    }
    chanceMap[Ec::THREE_OF_A_KIND] = 2 / (50.) + 2 / (49.);
}

void CombinationsEngineFor2Cards::calculateChanceStraight() {
    if (achievedMap[Ec::ONE_PAIR]) {
        chanceMap[Ec::THREE_OF_A_KIND] = 3 / (50.) + 3 / (49.) + 3 / (48.) + 3 / (47.);
        return;
    }
    if ((cards[0].numOfCardRank == 14 && cards[1].numOfCardRank == 2) || (cards[1].numOfCardRank == 14 && cards[0].numOfCardRank == 2)) {
        if (cards[1].numOfCardRank == 2) {
            chanceMap[Ec::STRAIGHT] = 3 / (50.) + 3 / (49.) + 3 / (48.);
            return;
        }
    }
    if ((cards[0].numOfCardRank > cards[1].numOfCardRank ? cards[0].numOfCardRank - cards[1].numOfCardRank : cards[1].numOfCardRank - cards[0].numOfCardRank) < 5) {
        chanceMap[Ec::STRAIGHT] = 3 / (50.) + 3 / (49.) + 3 / (48.);
    } else {
        chanceMap[Ec::STRAIGHT] = 2 * (3 / (50.) + 3 / (49.) + 3 / (48.) + 3 / (47.));
    }
}

void CombinationsEngineFor2Cards::calculateChanceFlush() {
    if (cards[0].numOfCardSuit == cards[1].numOfCardSuit) {
        chanceMap[Ec::FLUSH] = 11 / (50.) *  10 / (49.) * 9 / (48.);
    } else {
        chanceMap[Ec::FLUSH] = 2 * (11 / (50.) *  10 / (49.) *  9 / (48.) * 8 / (47.));
    }
}

void CombinationsEngineFor2Cards::calculateChanceFullHouse() {
    if (achievedMap[Ec::ONE_PAIR]) {
        chanceMap[Ec::FULL_HOUSE] = (4 / (50.) + 3 / (49.) + 2 / (48.) + (2 / (50.) + 4 / (49.) + 3 / (48.)));
    } else {
        chanceMap[Ec::FULL_HOUSE] = (3 / (50.) + 2 / (49.) + 3 / (48.));
    }
}

void CombinationsEngineFor2Cards::calculateChanceFourOfAKind() {
    if (achievedMap[Ec::ONE_PAIR]) {
        chanceMap[Ec::FOUR_OF_A_KIND] = (2 / (50.) + 1 / (49.));
        return;
    }
    chanceMap[Ec::FOUR_OF_A_KIND] = 2 * (3 / (50.) + 2 / (49.) + 1 / (48.));
}

void CombinationsEngineFor2Cards::calculateChanceStraightFlush() {
    double multiply = (cards[0].numOfCardSuit == cards[1].numOfCardSuit) ? ((12 / (50.) * 11 / (49.) * 10 / (48.))) : (12 / (50.) * 11 / (49.) * 10 / (48.) * 9 / (47.));
    if (achievedMap[Ec::ONE_PAIR]) {
        chanceMap[Ec::THREE_OF_A_KIND] = (3 / (50.) + 3 / (49.) + 3 / (48.) + 3 / (47.)) * multiply;
        return;
    }
    if ((cards[0].numOfCardRank == 14 && cards[1].numOfCardRank == 2) || (cards[1].numOfCardRank == 14 && cards[0].numOfCardRank == 2)) {
        if (cards[1].numOfCardRank == 2) {
            chanceMap[Ec::STRAIGHT] = (3 / (50.) + 3 / (49.) + 3 / (48.)) * multiply;
            return;
        }
    }
    if ((cards[0].numOfCardRank > cards[1].numOfCardRank ? cards[0].numOfCardRank - cards[1].numOfCardRank : cards[1].numOfCardRank - cards[0].numOfCardRank) < 5) {
        chanceMap[Ec::STRAIGHT] = (3 / (50.) + 3 / (49.) + 3 / (48.)) * multiply;
    } else {
        chanceMap[Ec::STRAIGHT] = (2 * (3 / (50.) + 3 / (49.) + 3 / (48.) + 3 / (47.))) * multiply;
    }
}

void CombinationsEngineFor2Cards::calculateChanceRoyalFlush() {
    double multiply = (cards[0].numOfCardSuit == cards[1].numOfCardSuit) ? ((12 / (50.) * 11 / (49.) * 10 / (48.))) : (12 / (50.) * 11 / (49.) * 10 / (48.) * 9 / (47.));
    if (achievedMap[Ec::TWO_PAIRS]) {
        if (cards[0].numOfCardRank == 14 || cards[0].numOfCardRank == 13 || cards[0].numOfCardRank == 12 || cards[0].numOfCardRank == 11 || cards[0].numOfCardRank == 10) {
            chanceMap[Ec::ROYAL_FLUSH] = (1 / (50.) + 1 / (49.) + 1 / (48.) + 1 / (47.)) * multiply;
        }
        return;
    }
    if (cards[0].numOfCardRank == 14 || cards[0].numOfCardRank == 13 || cards[0].numOfCardRank == 12 || cards[0].numOfCardRank == 11 || cards[0].numOfCardRank == 10) {
        if (cards[1].numOfCardRank == 14 || cards[1].numOfCardRank == 13 || cards[1].numOfCardRank == 12 || cards[1].numOfCardRank == 11 || cards[1].numOfCardRank == 10) {
            chanceMap[Ec::ROYAL_FLUSH] = (1 / (50.) + 1 / (49.) + 1 / (48.)) * multiply;
        } else {
            chanceMap[Ec::ROYAL_FLUSH] = (1 / (50.) + 1 / (49.) + 1 / (48.) + 1 / (47.)) * multiply;
        }
        return;
    }
    if (cards[1].numOfCardRank == 14 || cards[1].numOfCardRank == 13 || cards[1].numOfCardRank == 12 || cards[1].numOfCardRank == 11 || cards[1].numOfCardRank == 10) {
        if (cards[0].numOfCardRank == 14 || cards[0].numOfCardRank == 13 || cards[0].numOfCardRank == 12 || cards[0].numOfCardRank == 11 || cards[0].numOfCardRank == 10) {
            chanceMap[Ec::ROYAL_FLUSH] = (1 / (50.) + 1 / (49.) + 1 / (48.)) * multiply;
        } else {
            chanceMap[Ec::ROYAL_FLUSH] = (1 / (50.) + 1 / (49.) + 1 / (48.) + 1 / (47.)) * multiply;
        }
        return;
    }
    chanceMap[Ec::ROYAL_FLUSH] = (1 / (50.) + 1 / (49.) + 1 / (48.) + 1 / (47.) + 1 / (46.)) * multiply;
}
