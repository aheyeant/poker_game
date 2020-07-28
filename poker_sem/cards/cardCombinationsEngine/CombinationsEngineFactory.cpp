
#include "CombinationsEngineFactory.h"
#include "CombinationsEngineFor2Cards.h"
#include "CombinationsEngineFor5cards.h"
#include "CombinationsEngineFor7Cards.h"

CombinationsEngineAbstract * CombinationsEngineFactory::getEngine(const Card *cards, int cardsCount) {
    switch (cardsCount) {
        case 2:
            return new CombinationsEngineFor2Cards(cards);
        case 5:
            return new CombinationsEngineFor5Cards(cards);
        case 6:
            return nullptr;
        case 7:
            return new CombinationsEngineFor7Cards(cards);
        default:
            return nullptr;
    }
}
