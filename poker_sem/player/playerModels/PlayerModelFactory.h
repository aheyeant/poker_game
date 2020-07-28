
#ifndef SEM_ALI_PLAYERMODELFACTORY_H
#define SEM_ALI_PLAYERMODELFACTORY_H

#include "../PlayerAbstract.h"
#include "PCPlayerModelChooseFromAllChance.h"
#include "PCPlayerModelChooseFromBestChance.h"
#include "PlayerModelManual.h"
#include "PCPlayerModelRandom.h"

class PlayerModelFactory {
public:
    PlayerModelFactory();

    ~PlayerModelFactory();

    /**
     * @note can throw exception
     * @param modelNumber (1 - all chance player, 2 - best chance player)
     * @return
     */
    static PlayerAbstract * getPCModel(int modelNumber, std::string playerName);

    static PlayerAbstract * getManualModel();
};


#endif //SEM_ALI_PLAYERMODELFACTORY_H
