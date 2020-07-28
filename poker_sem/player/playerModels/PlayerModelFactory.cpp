//
// Created by aheyeant on 12.07.2020.
//

#include "PlayerModelFactory.h"

#include <utility>


PlayerModelFactory::PlayerModelFactory() = default;

PlayerModelFactory::~PlayerModelFactory() = default;

///modelNumber (1 - all chance player, 2 - best chance player, 3 - random player(only for fun))
PlayerAbstract * PlayerModelFactory::getPCModel(int modelNumber, std::string playerName) {
    switch (modelNumber) {
        case 1:
            return new PCPLayerModelChooseFromAllChance(std::move(playerName));
        case 2:
            return new PCPLayerModelChooseFromBestChance(std::move(playerName));
        case 3:
            return new PCPLayerModelRandom(std::move(playerName));
        default:
            throw std::logic_error("Undefined player model");
    }
}

PlayerAbstract * PlayerModelFactory::getManualModel() {
    return new PlayerModelManual(PLAYER_NAME);
}
