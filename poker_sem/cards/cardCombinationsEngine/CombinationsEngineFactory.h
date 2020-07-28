
#ifndef SEM_ALI_COMBINATIONSENGINEFACTORY_H
#define SEM_ALI_COMBINATIONSENGINEFACTORY_H

#include "CombinationsEngineAbstract.h"

class CombinationsEngineFactory {
public:
    CombinationsEngineFactory() = default;

    //todo control delete after use
    CombinationsEngineAbstract * getEngine(const Card * cards, int cardsCount);
};

#endif //SEM_ALI_COMBINATIONSENGINEFACTORY_H
