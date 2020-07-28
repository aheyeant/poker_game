
#include "WinnerComparator.h"

WinnerComparator::WinnerComparator(int gameLevel, PlayerAbstract **players, int playersCount, int & bank) : gameLevel(gameLevel), players(players), playersCount(playersCount), bank(bank) {}

bool WinnerComparator::whoWin() {
    std::cout << "---- Results ----" << std::endl;
    if (gameLevel == 0) {
        std::cout << "\033[1;31mEnd of game\033[1;0m" << std::endl;
        return false;
    }
    std::vector<PlayerAbstract *> winners;
    for (int i = 0; i < playersCount; i++) {
        if (!players[i]->gameStatistics.fold && players[i]->gameStatistics.inGame) {
            winners.emplace_back(players[i]);
        }
    }
    if (winners.empty()) {
        std::cout << "\033[1;31mNo winners\033[1;0m" << std::endl;
        return true;
    }
    if (winners.size() == 1) {
        winners.at(0)->gameStatistics.playerMoney += bank;
        std::cout << "\033[1;31mPlayer: " << winners.at(0)->getName() << " won " << std::to_string(bank) << "\033[1;0m" << std::endl;
        return true;
    }
    int *tmp = new int[winners.size()];
    auto **pEngineAbstract = new CombinationsEngineAbstract *[winners.size()];
    for (int i = 0; i < winners.size(); i++) {
        pEngineAbstract[i] = CombinationsEngineFactory().getEngine(winners.at(i)->getPlayingCards(), gameLevel);
    }
    for (int i = 0; i < winners.size(); i++) {
        pEngineAbstract[i]->recalculate();
        tmp[i] = pEngineAbstract[i]->getBestAchievedCombinations();
    }
    int max = 0;
    int count = 0;
    for (int i = 0; i < winners.size(); i++) {
        if (tmp[i] > max) {
            max = tmp[i];
        }
    }
    for (int i = 0; i < winners.size(); i++) {
        if (tmp[i] == max) {
            count++;
        } else {
            tmp[i] = 0;
        }
    }
    if (count == 1) {
        for (int i = 0; i < winners.size(); i++) {
            if (tmp[i] == max) {
                std::cout << "\033[1;31mPlayer: " << winners.at(i)->getName() << " won " << std::to_string(bank) << "\033[1;0m" << std::endl;
                delete[] tmp;
                for (int j = 0; j < winners.size(); j++) {
                    delete pEngineAbstract[j];
                }
                delete[] pEngineAbstract;
                return true;
            }
        }
    } else {
        for (int i = 0; i < winners.size(); i++) {
            if (tmp[i] != 0) {
                max = 0;
                auto card = players[i]->getPlayingCards();
                for (int j = 0; j < gameLevel; j++) {
                    if (card[i].numOfCardRank > max) {
                        max = card[i].numOfCardRank;
                    }
                }
                tmp[i] = max;
            }
        }
    }
    max = 0;
    for (int i = 0; i < winners.size(); i++) {
        if (tmp[i] > max) max = tmp[i];
    }
    count = 0;
    for (int i = 0; i < winners.size(); i++) {
        if (tmp[i] != max) {
            tmp[i] = 0;
        } else {
            count++;
        }
    }
    if (count == 1) {
        for (int i = 0; i < winners.size(); i++) {
            if (tmp[i] == max) {
                winners.at(i)->gameStatistics.playerMoney += bank;
                std::cout << "\033[1;31mPlayer: " << winners.at(i)->getName() << " won " << std::to_string(bank) << "\033[1;0m" << std::endl;
            }
        }
    } else {
        for (int i = 0; i < winners.size(); i++) {
            if (tmp[i] == max) {
                winners.at(i)->gameStatistics.playerMoney += bank / count;
                std::cout << "\033[1;31mPlayer: " << winners.at(i)->getName() << " won " << std::to_string(bank / count)
                          << "\033[1;0m" << std::endl;
            }
        }

        delete[] tmp;
        for (int i = 0; i < winners.size(); i++) {
            delete pEngineAbstract[i];
        }
        delete[] pEngineAbstract;
    }
    return true;
}
