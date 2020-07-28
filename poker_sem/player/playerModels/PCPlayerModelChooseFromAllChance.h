
#ifndef SEM_ALI_PCPLAYERMODELCHOOSEFROMALLCHANCE_H
#define SEM_ALI_PCPLAYERMODELCHOOSEFROMALLCHANCE_H

#include "../PlayerAbstract.h"

class PCPLayerModelChooseFromAllChance : public PlayerAbstract {
public:
    explicit PCPLayerModelChooseFromAllChance(std::string playerName);

    std::pair<ENextStep, int> getNextStep(ENextStep nextStep, int bet) override;
};


#endif //SEM_ALI_PCPLAYERMODELCHOOSEFROMALLCHANCE_H
