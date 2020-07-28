
#ifndef SEM_ALI_PCPLAYERMODELCHOOSEFROMBESTCHANCE_H
#define SEM_ALI_PCPLAYERMODELCHOOSEFROMBESTCHANCE_H

#include "../PlayerAbstract.h"

class PCPLayerModelChooseFromBestChance : public PlayerAbstract {
public:
    explicit PCPLayerModelChooseFromBestChance(std::string playerName);

    std::pair<ENextStep, int> getNextStep(ENextStep nextStep, int bet) override;
};

#endif //SEM_ALI_PCPLAYERMODELCHOOSEFROMBESTCHANCE_H
