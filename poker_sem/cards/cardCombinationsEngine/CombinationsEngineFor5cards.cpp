
#include "CombinationsEngineFor5cards.h"


CombinationsEngineFor5Cards::CombinationsEngineFor5Cards(const Card *cards) : CombinationsEngineAbstract(cards), cardsCount(5) {}

double CombinationsEngineFor5Cards::getSumChance() {
    double sum = 0.0;
    for (int i = 1; i < 11; i++) {
        sum += chanceMap[ECombinations(i)];
    }
    return sum;
}

double CombinationsEngineFor5Cards::getBestChance() {
    double max = 0.0;
    for (int i = 1; i < 11; i++) {
        if (max < chanceMap[ECombinations(i)]) {
            max = chanceMap[ECombinations(i)];
        }
    }
    return max;
}

ECombinations CombinationsEngineFor5Cards::getBestAchievedCombinations() {
    for (int i = 1; i < 11; i++) {
        if (!achievedMap[ECombinations(i)]) return ECombinations(i - 1);
    }
    return Ec::HIGH_CARD;
}

std::map<ECombinations, bool> CombinationsEngineFor5Cards::getAchievedCombinationsMap() {
    return achievedMap;
}

std::map<ECombinations, double> CombinationsEngineFor5Cards::getPotentialCombinationChance() {
    return chanceMap;
}

void CombinationsEngineFor5Cards::recalculate() {
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

void CombinationsEngineFor5Cards::calculateChanceHighCard() {
    int biggestRank = getMaxRank(5);
    double chance = (50 - (biggestRank * 4) - 5) / (50.);
    chanceMap[Ec::HIGH_CARD] = chance;
    achievedMap[Ec::HIGH_CARD] = true;
}

void CombinationsEngineFor5Cards::calculateChanceOnePair() {
    int pairRank = 0;
    for (int i = 0; i < 4; i++) {
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
    chanceMap[Ec::ONE_PAIR] = 5 * (3 / 47.);
}

void CombinationsEngineFor5Cards::calculateChanceTwoPair() {
    int firstRank = 0;
    int secondRank = 0;
    for (int i = 0; i < 4; i++) {
        if (cards[i].numOfCardRank == cards[i + 1].numOfCardRank) {
           firstRank = cards[i].numOfCardRank;
        }
    }
    for (int i = 0; i < 4; i++) {
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
    if (achievedMap[Ec::ONE_PAIR]) {
        chanceMap[Ec::TWO_PAIRS] = 3 * (3 / 47.);
        return;
    }
    chanceMap[Ec::TWO_PAIRS] = (5 * (3 / 47.)) * (4 * (3 / 46.));

}

void CombinationsEngineFor5Cards::calculateChanceTreeOfAKind() {
    int threeRank = 0;
    int count = 0;
    for (int i = 0; i < 4; i++) {
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
    if (achievedMap[Ec::TWO_PAIRS]) {
        chanceMap[Ec::THREE_OF_A_KIND] = 4 / (47.);
        return;
    }
    if (achievedMap[Ec::ONE_PAIR]) {
        chanceMap[Ec::THREE_OF_A_KIND] = 2 / (47.) + 3 / (46.) + 3 / (45.) + 3 / (44.);
        return;
    }
    chanceMap[Ec::THREE_OF_A_KIND] = (3 / (47.) + 3 / (46.) + 3 / (45.) + 3 / (44.) + 3 / (43.)) / 2;
}

void CombinationsEngineFor5Cards::calculateChanceStraight() {
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

    int nums[5] = {0, 0, 0, 0, 0};
    for (int i = 0; i < 4; i++) {
        nums[i] = cards[i + 1].numOfCardRank - cards[i].numOfCardRank;
    }
    nums[4] = 14 - cards[4].numOfCardRank;
    chanceMap[Ec::STRAIGHT] = nums[0] / (47.) + nums[1] / (47.) + nums[2] / (47.) + nums[3] / (47.) + nums[4] / (47.);
}

void CombinationsEngineFor5Cards::calculateChanceFlush() {
    int maxRank = 0;
    int suites[4] = {0, 0, 0, 0};
    for (int i = 0; i < 5; i++) {
        if (maxRank < cards[i].numOfCardRank) maxRank = cards[i].numOfCardRank;
        suites[cards[i].numOfCardSuit - 1]++;
    }
    for (int i : suites) {
        if (i == 5) {
            achievedMap[Ec::FLUSH] = true;
            chanceMap[Ec::FLUSH] = 1.0 / (1 + 14 - maxRank);
            return;
        }
    }
    for (int suite : suites) {
        chanceMap[Ec::FLUSH] += pow((13 - suite) / (47.), suite);
    }
}

void CombinationsEngineFor5Cards::calculateChanceFullHouse() {
    if (achievedMap[Ec::ONE_PAIR] && achievedMap[Ec::THREE_OF_A_KIND]) {
        achievedMap[Ec::FULL_HOUSE] = true;
        chanceMap[Ec::FULL_HOUSE] = 1.0 / (1 + 14 - getMaxRank(5));
    }
    if (achievedMap[Ec::THREE_OF_A_KIND]) {
        chanceMap[Ec::FULL_HOUSE] = 3 / (47.) + 3 / (46.);
        return;
    }
    if (achievedMap[Ec::TWO_PAIRS]) {
        chanceMap[Ec::FULL_HOUSE] = 2 / (47.) + 2 / (46.);
        return;
    }
    if (achievedMap[Ec::ONE_PAIR]) {
        chanceMap[Ec::FULL_HOUSE] = 2 / (47.) + 2 * (3 / (46.) * 2 / (45.));
        return;
    }
    chanceMap[Ec::FULL_HOUSE] = 3 / (47.) * 3 * (3 / (46.) * 2 / (45.));
}

void CombinationsEngineFor5Cards::calculateChanceFourOfAKind() {
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
    if (achievedMap[Ec::THREE_OF_A_KIND]) {
        chanceMap[Ec::FOUR_OF_A_KIND] = 1 / (47.);
    }
    if (achievedMap[Ec::TWO_PAIRS]) {
        chanceMap[Ec::FOUR_OF_A_KIND] = 2 * (2 / (47.) * 1 / (46.));
    }
    if (achievedMap[Ec::ONE_PAIR]) {
        chanceMap[Ec::FOUR_OF_A_KIND] = (2 / (47.) * 1 / (46.));
    }
}

void CombinationsEngineFor5Cards::calculateChanceStraightFlush() {
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
    chanceMap[Ec::STRAIGHT_FLUSH] = chanceMap[Ec::STRAIGHT] * CHANCE_SIMILAR_SUITES;
}

void CombinationsEngineFor5Cards::calculateChanceRoyalFlush() {
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
    int neededCards = 0;
    for (int i = 0; i < 5; i++) {
        if (cards[i].numOfCardRank == 10) {
            neededCards++;
            break;
        }
    }
    for (int i = 0; i < 5; i++) {
        if (cards[i].numOfCardRank == 11) {
            neededCards++;
            break;
        }
    }
    for (int i = 0; i < 5; i++) {
        if (cards[i].numOfCardRank == 12) {
            neededCards++;
            break;
        }
    }
    for (int i = 0; i < 5; i++) {
        if (cards[i].numOfCardRank == 13) {
            neededCards++;
            break;
        }
    }
    for (int i = 0; i < 5; i++) {
        if (cards[i].numOfCardRank == 14) {
            neededCards++;
            break;
        }
    }
    chanceMap[Ec::ROYAL_FLUSH] = (5 - neededCards) / (47.) * CHANCE_SIMILAR_SUITES;
}




