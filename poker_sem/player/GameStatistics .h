
#ifndef SEM_ALI_GAMESTATISTICS_H
#define SEM_ALI_GAMESTATISTICS_H

struct GameStatistics {
public:
    GameStatistics();

    int playerMoney;

    bool inGame;

    int moneyOnTable;

    int lastBet;

    bool check;

    bool fold;

    bool needCall;

    void restartCycle();

    void restartBet();

    void restartNeedCall();
};

#endif //SEM_ALI_GAMESTATISTICS_H
