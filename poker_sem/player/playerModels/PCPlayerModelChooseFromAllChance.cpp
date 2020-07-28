
#include "PCPlayerModelChooseFromAllChance.h"

PCPLayerModelChooseFromAllChance::PCPLayerModelChooseFromAllChance(std::string playerName) : PlayerAbstract(std::move(playerName)) {}


std::pair<ENextStep, int> PCPLayerModelChooseFromAllChance::getNextStep(ENextStep nextStep, int bet) {
    engine->recalculate();
    double sumChance = engine->getSumChance();
    double subMoney = static_cast<double>(bet) / gameStatistics.playerMoney;
    switch (nextStep) {
        case BET:
            if (static_cast<int>(engine->getBestAchievedCombinations()) > (static_cast<int>(getRandChance() * 10) + 4)|| static_cast<int>(engine->getBestAchievedCombinations()) > 7) {
                if (static_cast<int>(engine->getBestAchievedCombinations()) / 10. + getRandChance() > getRandChance())
                    return std::pair<ENextStep, int>{ENextStep::ALL_IN, gameStatistics.playerMoney};
            }
            if (sumChance * (static_cast<int>(engine->getBestAchievedCombinations())) > getRandChance()) {
                return std::pair<ENextStep, int>{ENextStep::BET, bet};
            } else if ((sumChance * (static_cast<int>(engine->getBestAchievedCombinations())) / 10 > getRandChance())){
                return std::pair<ENextStep, int>{ENextStep::RAISE, bet * MULTIPLY_BET - bet};
            } else {
                return std::pair<ENextStep, int>{ENextStep::FOLD, 0};
            }
        case CHECK:
            return std::pair<ENextStep, int>{ENextStep::CHECK, 0};
        case RAISE:
                if (sumChance > subMoney) {
                    if (sumChance > getRandChance() && gameStatistics.playerMoney >= bet * MULTIPLY_BET) {
                        return std::pair<ENextStep, int>{ENextStep::CALL, bet};
                    }
                } else {
                    return std::pair<ENextStep, int>{ENextStep::FOLD, 0};
                }
        case CALL:
            if (gameStatistics.playerMoney < bet) return std::pair<ENextStep, int>{ENextStep::FOLD, 0};
            if (sumChance > subMoney) {
                if (sumChance > getRandChance()) {
                    return std::pair<ENextStep, int>{ENextStep::CALL, bet};
                }
            } else {
                return std::pair<ENextStep, int>{ENextStep::FOLD, 0};
            }
        case ALL_IN:
            if (static_cast<int>(engine->getBestAchievedCombinations()) > (static_cast<int>(getRandChance() * 10) + 4) || static_cast<int>(engine->getBestAchievedCombinations()) > 7) {
                if (static_cast<int>(engine->getBestAchievedCombinations()) / 10. + getRandChance() > getRandChance())
                    return std::pair<ENextStep, int>{ENextStep::ALL_IN, gameStatistics.playerMoney};
            }
            return std::pair<ENextStep, int>{ENextStep::FOLD, 0};
        case FOLD:
            return std::pair<ENextStep, int>{ENextStep::FOLD, 0};
        case ALL:
            if (static_cast<int>(engine->getBestAchievedCombinations()) > (static_cast<int>(getRandChance() * 10) + 4)|| static_cast<int>(engine->getBestAchievedCombinations()) > 7) {
                if (static_cast<int>(engine->getBestAchievedCombinations()) / 10. + getRandChance() > getRandChance())
                    return std::pair<ENextStep, int>{ENextStep::ALL_IN, gameStatistics.playerMoney};
            }
            if (sumChance * static_cast<int>(engine->getBestAchievedCombinations()) > getRandChance() && gameStatistics.playerMoney >= bet * MULTIPLY_BET) {
                return std::pair<ENextStep, int>{ENextStep::RAISE, bet * MULTIPLY_BET};
            } else {
                return std::pair<ENextStep, int>{ENextStep::CHECK, 0};
            }
        case EXIT:
        default:
            return std::pair<ENextStep, int>{ENextStep::FOLD, 0};
    }
}
