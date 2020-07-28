
#include "PCPlayerModelRandom.h"

PCPLayerModelRandom::PCPLayerModelRandom(std::string playerName) : PlayerAbstract(std::move(playerName)) {}

std::pair<ENextStep, int> PCPLayerModelRandom::getNextStep(ENextStep nextStep, int bet) {
    return std::pair<ENextStep, int>();
}
