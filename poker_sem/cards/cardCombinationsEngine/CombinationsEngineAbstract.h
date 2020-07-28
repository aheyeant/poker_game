
#ifndef SEM_ALI_COMBINATIONSENGINEABSTRACT_H
#define SEM_ALI_COMBINATIONSENGINEABSTRACT_H

#include <cmath>
#include <map>
#include <vector>
#include "../ECombinations.h"
#include "../Card.h"
#include "../../gameLogic/GameConstants.h"


typedef ECombinations Ec;

class CombinationsEngineAbstract {
public:
    explicit CombinationsEngineAbstract(const Card * cards);

    virtual ~CombinationsEngineAbstract() = 0;

    virtual double getSumChance() = 0;

    virtual double getBestChance() = 0;

    virtual ECombinations getBestAchievedCombinations() = 0;

    virtual std::map<ECombinations, bool> getAchievedCombinationsMap() = 0;

    virtual std::map<ECombinations, double> getPotentialCombinationChance() = 0;

    virtual void recalculate() = 0;

protected:
    const Card * cards;

    std::map<ECombinations, double> chanceMap;

    std::map<ECombinations, bool> achievedMap;

    virtual void calculateChanceHighCard() = 0;

    virtual void calculateChanceOnePair() = 0;

    virtual void calculateChanceTwoPair() = 0;

    virtual void calculateChanceTreeOfAKind() = 0;

    virtual void calculateChanceStraight() = 0;

    virtual void calculateChanceFlush() = 0;

    virtual void calculateChanceFullHouse() = 0;

    virtual void calculateChanceFourOfAKind() = 0;

    virtual void calculateChanceStraightFlush() = 0;

    virtual void calculateChanceRoyalFlush() = 0;

    int getMaxRank(int cardsCount);

    int getMaxRankWithSuit(int cardCount, int suit);

    static std::vector<ECombinations> getAllCombinations();
};

#endif //SEM_ALI_COMBINATIONSENGINEABSTRACT_H
