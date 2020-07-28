
#ifndef SEM_ALI_PCPLAYERMODELRANDOM_H
#define SEM_ALI_PCPLAYERMODELRANDOM_H

#include "../PlayerAbstract.h"

class PCPLayerModelRandom : public PlayerAbstract {
public:
    explicit PCPLayerModelRandom(std::string playerName);

    std::pair<ENextStep, int> getNextStep(ENextStep nextStep, int bet) override;
};
#endif //SEM_ALI_PCPLAYERMODELRANDOM_H
