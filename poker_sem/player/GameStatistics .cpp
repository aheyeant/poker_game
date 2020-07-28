
#include "GameStatistics .h"
#include "../gameLogic/GameConstants.h"

GameStatistics::GameStatistics() : playerMoney(DEFAULT_MONEY_WHEN_GAME_START), inGame(true), moneyOnTable(0), lastBet(0), check(false), fold(false), needCall(false){}

void GameStatistics::restartCycle() {
    moneyOnTable = 0;
    lastBet = 0;
    fold = false;
    check = false;
    needCall = false;
}

void GameStatistics::restartBet() {
    check = false;
}

void GameStatistics::restartNeedCall() {
    needCall = false;
}
