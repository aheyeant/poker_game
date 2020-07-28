
#ifndef SEM_ALI_COMBINATIONSENGINEFOR5CARDS_H
#define SEM_ALI_COMBINATIONSENGINEFOR5CARDS_H

#include "CombinationsEngineAbstract.h"

class CombinationsEngineFor5Cards : public CombinationsEngineAbstract {
public:
    explicit CombinationsEngineFor5Cards(const Card * cards);

    double getSumChance() override;

    double getBestChance() override;

    ECombinations getBestAchievedCombinations() override;

    std::map<ECombinations, bool> getAchievedCombinationsMap() override;

    std::map<ECombinations, double> getPotentialCombinationChance() override;

    void recalculate() override;

protected:
    void calculateChanceHighCard() override;

    void calculateChanceOnePair() override;

    void calculateChanceTwoPair() override;

    void calculateChanceTreeOfAKind() override;

    void calculateChanceStraight() override;

    void calculateChanceFlush() override;

    void calculateChanceFullHouse() override;

    void calculateChanceFourOfAKind() override;

    void calculateChanceStraightFlush() override;

    void calculateChanceRoyalFlush() override;

private:
    int cardsCount;
};

#endif //SEM_ALI_COMBINATIONSENGINEFOR5CARDS_H
