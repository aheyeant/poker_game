
#ifndef SEM_ALI_PLAYERMODELMANUAL_H
#define SEM_ALI_PLAYERMODELMANUAL_H

#include "../PlayerAbstract.h"

class PlayerModelManual : public PlayerAbstract {
public:
    explicit PlayerModelManual(std::string playerName);

    std::pair<ENextStep, int> getNextStep(ENextStep nextStep, int bet) override;

private:
    std::pair <ENextStep, int> makeBet();

    std::pair <ENextStep, int> makeCall(int bet);

    std::pair <ENextStep, int> makeAlIn();

    std::pair<ENextStep, int> makeStep();
};

#endif //SEM_ALI_PLAYERMODELMANUAL_H
