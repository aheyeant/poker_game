
#ifndef SEM_ALI_WINNERCOMPARATOR_H
#define SEM_ALI_WINNERCOMPARATOR_H

#include "../../player/PlayerAbstract.h"
#include "CombinationsEngineFactory.h"

class WinnerComparator {
public:
    /**
     *
     * @param gameLevel moment when game finished(2, 5, 7 cards)
     * @param players
     * @param playersCount
     * @param bank
     */
    WinnerComparator(int gameLevel, PlayerAbstract ** players, int playersCount, int & bank);

    bool whoWin();

private:
    int gameLevel;
    PlayerAbstract ** players;
    int playersCount;
    int bank;

};

#endif //SEM_ALI_WINNERCOMPARATOR_H
