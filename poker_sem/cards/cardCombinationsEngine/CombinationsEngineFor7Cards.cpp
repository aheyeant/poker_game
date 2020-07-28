
#include "CombinationsEngineFor7Cards.h"

CombinationsEngineFor7Cards::CombinationsEngineFor7Cards(const Card *cards) : CombinationsEngineAbstract(cards), cardsCount(7) {}

double CombinationsEngineFor7Cards::getSumChance() {
    double sum = 0.0;
    for (int i = 1; i < 11; i++) {
        sum += chanceMap[ECombinations(i)];
    }
    return sum;
}

double CombinationsEngineFor7Cards::getBestChance() {
    double max = 0.0;
    for (int i = 1; i < 11; i++) {
        if (max < chanceMap[ECombinations(i)]) {
            max = chanceMap[ECombinations(i)];
        }
    }
    return max;
}

ECombinations CombinationsEngineFor7Cards::getBestAchievedCombinations() {
    for (int i = 1; i < 11; i++) {
        if (!achievedMap[ECombinations(i)]) return ECombinations(i - 1);
    }
    return Ec::HIGH_CARD;
}

std::map<ECombinations, bool> CombinationsEngineFor7Cards::getAchievedCombinationsMap() {
    return achievedMap;
}

std::map<ECombinations, double> CombinationsEngineFor7Cards::getPotentialCombinationChance() {
    return chanceMap;
}

void CombinationsEngineFor7Cards::recalculate() {
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

void CombinationsEngineFor7Cards::calculateChanceHighCard() {
    int biggestRank = getMaxRank(5);
    double chance = (50 - (biggestRank * 4) - 5) / (50.);
    chanceMap[Ec::HIGH_CARD] = chance;
    achievedMap[Ec::HIGH_CARD] = true;
}

void CombinationsEngineFor7Cards::calculateChanceOnePair() {
    int pairRank = 0;
    for (int i = 0; i < 6; i++) {
        if (cards[i].numOfCardRank == cards[i + 1].numOfCardRank) {
            if (pairRank < cards[i].numOfCardRank) {
                pairRank = cards[i].numOfCardRank;
            }
        }
    }
    if (pairRank > 0) {
        achievedMap[Ec::ONE_PAIR] = true;
        chanceMap[Ec::ONE_PAIR] = 1.0 / (1 + 14 - pairRank);
        return;
    }
    chanceMap[Ec::ONE_PAIR] = 0.0;
}

void CombinationsEngineFor7Cards::calculateChanceTwoPair() {
    int firstRank = 0;
    int secondRank = 0;
    for (int i = 0; i < 6; i++) {
        if (cards[i].numOfCardRank == cards[i + 1].numOfCardRank) {
            firstRank = cards[i].numOfCardRank;
        }
    }
    for (int i = 0; i < 6; i++) {
        if (cards[i].numOfCardRank == cards[i + 1].numOfCardRank) {
            if (cards[i].numOfCardRank != firstRank)
                secondRank = cards[i].numOfCardRank;
        }
    }

    if (firstRank > 0 && secondRank > 0) {
        achievedMap[Ec::TWO_PAIRS] = true;
        chanceMap[Ec::TWO_PAIRS] = 1.0 / (1 + 14 - (firstRank > secondRank ? firstRank : secondRank));
        return;
    }
    chanceMap[Ec::ONE_PAIR] = 0.0;
}

void CombinationsEngineFor7Cards::calculateChanceTreeOfAKind() {
    int threeRank = 0;
    int count = 0;
    for (int i = 0; i < 6; i++) {
        if (cards[i].numOfCardRank == cards[i + 1].numOfCardRank) {
            threeRank = cards[i].numOfCardRank;
            count++;
            if (count == 3) {
                achievedMap[Ec::THREE_OF_A_KIND] = true;
                chanceMap[Ec::THREE_OF_A_KIND] = 1.0 / (1 + 14 - threeRank);
                return;
            }
        } else {
            count = 0;
        }
    }
    chanceMap[Ec::THREE_OF_A_KIND] = 0.0;
}

void CombinationsEngineFor7Cards::calculateChanceStraight() {
    if (cards[4].numOfCardRank == 14 && cards[0].numOfCardRank == 2) {
        if (cards[1].numOfCardRank != 3) {
            chanceMap[Ec::STRAIGHT] = 3 / (47.) + 3 / (46.) + 3 / (45.);
            return;
        }
        if (cards[2].numOfCardRank != 4) {
            chanceMap[Ec::STRAIGHT] = 3 / (47.) + 3 / (46.);
            return;
        }
        if (cards[3].numOfCardRank != 5) {
            chanceMap[Ec::STRAIGHT] = 3 / (47.);
            return;
        }
        achievedMap[Ec::STRAIGHT] = true;
        chanceMap[Ec::STRAIGHT] = 1.0 / (1 + 14 - 5);
        return;
    }
    chanceMap[Ec::STRAIGHT] = 0.0;
}

void CombinationsEngineFor7Cards::calculateChanceFlush() {
    int maxRank = 0;
    int suites[4] = {0, 0, 0, 0};
    for (int i = 0; i < 7; i++) {
        if (maxRank < cards[i].numOfCardRank) maxRank = cards[i].numOfCardRank;
        suites[cards[i].numOfCardSuit - 1]++;
    }
    for (int i = 0; i < 4; i++) {
        if (suites[i] == 5) {
            achievedMap[Ec::FLUSH] = true;
            chanceMap[Ec::FLUSH] = 1.0 / (1 + 14 - getMaxRankWithSuit(7, i + 1));
            return;
        }
    }
    chanceMap[Ec::FLUSH] = 0;
}

void CombinationsEngineFor7Cards::calculateChanceFullHouse() {
    if (achievedMap[Ec::ONE_PAIR] && achievedMap[Ec::THREE_OF_A_KIND]) {
        achievedMap[Ec::FULL_HOUSE] = true;
        chanceMap[Ec::FULL_HOUSE] = 1.0 / (1 + 14 - getMaxRank(5));
    }
    chanceMap[Ec::FULL_HOUSE] = 0.0;
}

void CombinationsEngineFor7Cards::calculateChanceFourOfAKind() {
    int rank = 0;
    int count = 0;
    for (int i = 0; i < 4; i++) {
        if (cards[i].numOfCardRank == cards[i + 1].numOfCardRank) {
            rank = cards[i].numOfCardRank;
            count++;
            if (count == 4) {
                chanceMap[Ec::FOUR_OF_A_KIND] = 1.0 / (1 + 14 - rank);
                achievedMap[Ec::FOUR_OF_A_KIND] = true;
                return;
            }
        } else {
            count = 0;
        }
    }
    chanceMap[Ec::FOUR_OF_A_KIND] = 0.0;
}

void CombinationsEngineFor7Cards::calculateChanceStraightFlush() {
    if (achievedMap[Ec::FLUSH]) {
        int suites[4] = {0, 0, 0, 0};
        for (int i = 0; i < 5; i++) {
            suites[cards[i].numOfCardSuit - 1]++;
        }
        for (int i : suites) {
            if (i == 5) {
                achievedMap[Ec::STRAIGHT_FLUSH] = true;
                chanceMap[Ec::STRAIGHT_FLUSH] = 1.0 / (1 + 14 - getMaxRank(5));
                return;
            }
        }
    }
    chanceMap[Ec::STRAIGHT_FLUSH] = 0.0;
}

void CombinationsEngineFor7Cards::calculateChanceRoyalFlush() {
    if (cards[0].numOfCardRank == 10 && cards[0].numOfCardRank == 11 && cards[0].numOfCardRank == 12 && cards[0].numOfCardRank == 13 && cards[0].numOfCardRank == 14) {
        int suites[4] = {0, 0, 0, 0};
        for (int i = 0; i < 5; i++) {
            suites[cards[i].numOfCardSuit - 1]++;
        }
        for (int i : suites) {
            if (i == 4) {
                achievedMap[Ec::ROYAL_FLUSH] = true;
                chanceMap[Ec::STRAIGHT_FLUSH] = 1.0;
                return;
            }
        }
    }
}


