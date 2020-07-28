
#include "PokerGame.h"

PokerGame::PokerGame(int playersCount) : manualPlayerID(0), playersCounts(playersCount){
    gameBoard = nullptr;
    startGame();
}

PokerGame::~PokerGame() {
    delete gameBoard;
}

void PokerGame::startGame() {
    gameBoard = new GameBoard(playersCounts);
    int cycle = 0;
    while (canContinuePlaying()) {
        restartFold();
        recalculatePlayersMoney();
        giveOutCardOnTableAndPlayers();
        std::cout << "\033[1;32m---- Start " << std::to_string(++cycle) << " game cycle ----\033[1;0m" << std::endl;
        WinnerComparator winnerComparator(oneCycleGame(), gameBoard->players, gameBoard->playersCount, gameBoard->bank);
        if (!winnerComparator.whoWin()) {
            delete gameBoard;
            gameBoard = nullptr;
            return;
        }
        restartCheck();
        gameBoard->restart();
        std::cout << "\033[1;32m---- End " << std::to_string(cycle) << " game cycle ----\033[1;0m" << std::endl;
    }
}

int PokerGame::oneCycleGame() {
    PlayerAbstract **&player = gameBoard->players;
    std::pair<ENextStep, int> step;
    step = std::pair<ENextStep, int>{BET, MIN_BET};
    int currentPlayerID = 0;
    for (int i = 0; i < gameBoard->playersCount; i++) {
        gameBoard->players[i]->gameStatistics.restartCycle();
    }
    //2 cards
    setEngineForPlayers(2);
    restartCheck();
    while (!checkControl()) {
        if (!canContinuePlaying()) {
            return 2;
        }
        if (currentPlayerID == manualPlayerID && !player[manualPlayerID]->gameStatistics.fold) gameBoard->showTableOnTerminal();
        if (!manualPlayerCanGame()) {
            printPlayerCannotGame();
            return 0;
        }
        if (!player[currentPlayerID]->gameStatistics.inGame || player[currentPlayerID]->gameStatistics.fold) {
            currentPlayerID = (currentPlayerID + 1) % gameBoard->playersCount;
            continue;
        }
        step = player[currentPlayerID]->getNextStep(step.first, step.second);
        if (step.second == 0) step.second = MIN_BET;
        showPlayerStep(step, currentPlayerID);
        if (step.first == ENextStep::EXIT) return 0;
        if (step.first == ENextStep::RAISE) {
            if (currentPlayerID == manualPlayerID) {
                player[manualPlayerID]->gameStatistics.playerMoney -= step.second;
                gameBoard->bank += step.second;
            }
            for (int i = 0; i < gameBoard->playersCount; i++) {
                int bet = step.second;
                if (i != currentPlayerID) {
                    if (player[i]->gameStatistics.inGame && !player[i]->gameStatistics.fold) {
                        step.first = ENextStep::CALL;
                        step = player[i]->getNextStep(step.first, step.second);
                        showPlayerStep(step, i);
                        step.first = stepSwitcher(step, i);
                        if (step.second == 0) step.second = bet;
                    }
                }
            }
            currentPlayerID = manualPlayerID;
            step.first = ENextStep::BET;
            step.second = MIN_BET;
            continue;
        }
        if (step.first == ENextStep::ALL_IN) {
            if (currentPlayerID == manualPlayerID) {
                player[manualPlayerID]->gameStatistics.playerMoney -= step.second;
                gameBoard->bank += step.second;
            }
            for (int i = 0; i < gameBoard->playersCount; i++) {
                int bet = step.second;
                if (i != currentPlayerID) {
                    if (player[i]->gameStatistics.inGame && !player[i]->gameStatistics.fold) {
                        step.first = ENextStep::CALL;
                        step = player[i]->getNextStep(step.first, step.second);
                        showPlayerStep(step, i);
                        step.first = stepSwitcher(step, i);
                        if (step.second == 0) step.second = bet;
                    }
                }
            }
            return 7;
        }
        step.first = stepSwitcher(step, currentPlayerID);
        currentPlayerID = (currentPlayerID + 1) % gameBoard->playersCount;
        if (!canContinuePlaying()) {
            return 2;
        }
    }
    //5 cards
    recalculatePlayersMoney();
    openCardsFromTable(3);
    setEngineForPlayers(5);
    restartCheck();
    while (!checkControl()) {
        if (!canContinuePlaying()) {
            return 5;
        }
        if (currentPlayerID == manualPlayerID && !player[manualPlayerID]->gameStatistics.fold) gameBoard->showTableOnTerminal();
        if (!manualPlayerCanGame()) {
            printPlayerCannotGame();
            return 0;
        }
        if (!player[currentPlayerID]->gameStatistics.inGame || player[currentPlayerID]->gameStatistics.fold) {
            currentPlayerID = (currentPlayerID + 1) % gameBoard->playersCount;
            continue;
        }
        step = player[currentPlayerID]->getNextStep(step.first, step.second);
        showPlayerStep(step, currentPlayerID);
        if (step.first == ENextStep::EXIT) return 0;
        if (step.first == ENextStep::RAISE) {
            if (currentPlayerID == manualPlayerID) {
                player[manualPlayerID]->gameStatistics.playerMoney -= step.second;
                gameBoard->bank += step.second;
            }
            for (int i = 0; i < gameBoard->playersCount; i++) {
                int bet = step.second;
                if (i != currentPlayerID) {
                    if (player[i]->gameStatistics.inGame && !player[i]->gameStatistics.fold) {
                        step.first = ENextStep::CALL;
                        step = player[i]->getNextStep(step.first, step.second);
                        showPlayerStep(step, i);
                        step.first = stepSwitcher(step, i);
                        if (step.second == 0) step.second = bet;
                    }
                }
            }
            currentPlayerID = manualPlayerID;
            step.first = ENextStep::BET;
            step.second = MIN_BET;
            continue;
        }
        if (step.first == ENextStep::ALL_IN) {
            if (currentPlayerID == manualPlayerID) {
                player[manualPlayerID]->gameStatistics.playerMoney -= step.second;
                gameBoard->bank += step.second;
            }
            for (int i = 0; i < gameBoard->playersCount; i++) {
                if (i != currentPlayerID) {
                    if (player[i]->gameStatistics.inGame && !player[i]->gameStatistics.fold) {
                        step.first = ENextStep::ALL_IN;
                        step = player[i]->getNextStep(step.first, step.second);
                        showPlayerStep(step, i);
                        step.first = stepSwitcher(step, i);
                    }
                }
            }
            return 5;
        }
        step.first = stepSwitcher(step, currentPlayerID);
        currentPlayerID = (currentPlayerID + 1) % gameBoard->playersCount;
        if (!canContinuePlaying()) {
            return 5;
        }
    }
    //7 cards
    recalculatePlayersMoney();
    openCardsFromTable(2);
    setEngineForPlayers(7);
    restartCheck();
    while (!checkControl()) {
        if (currentPlayerID == manualPlayerID) {
            player[manualPlayerID]->gameStatistics.playerMoney -= step.second;
            gameBoard->bank += step.second;
        }
        if (!canContinuePlaying()) {
            return 7;
        }
        if (currentPlayerID == manualPlayerID && !player[manualPlayerID]->gameStatistics.fold) gameBoard->showTableOnTerminal();
        if (!manualPlayerCanGame()) {
            printPlayerCannotGame();
            return 0;
        }
        if (!player[currentPlayerID]->gameStatistics.inGame || player[currentPlayerID]->gameStatistics.fold) {
            currentPlayerID = (currentPlayerID + 1) % gameBoard->playersCount;
            continue;
        }
        step = player[currentPlayerID]->getNextStep(step.first, step.second);
        showPlayerStep(step, currentPlayerID);
        if (step.first == ENextStep::EXIT) return 0;
        if (step.first == ENextStep::RAISE) {
            if (currentPlayerID == manualPlayerID) {
                player[manualPlayerID]->gameStatistics.playerMoney -= step.second;
                gameBoard->bank += step.second;
            }
            for (int i = 0; i < gameBoard->playersCount; i++) {
                if (i != currentPlayerID) {
                    if (player[i]->gameStatistics.inGame && !player[i]->gameStatistics.fold) {
                        step.first = ENextStep::CALL;
                        step = player[i]->getNextStep(step.first, step.second);
                        showPlayerStep(step, i);
                        step.first = stepSwitcher(step, i);
                    }
                }
            }
            currentPlayerID = manualPlayerID;
            step.first = ENextStep::BET;
            step.second = MIN_BET;
            continue;
        }
        if (step.first == ENextStep::ALL_IN) {
            for (int i = 0; i < gameBoard->playersCount; i++) {
                if (i != currentPlayerID) {
                    if (player[i]->gameStatistics.inGame && !player[i]->gameStatistics.fold) {
                        step.first = ENextStep::ALL_IN;
                        step = player[i]->getNextStep(step.first, step.second);
                        showPlayerStep(step, i);
                        step.first = stepSwitcher(step, i);
                    }
                }
            }
            return 7;
        }
        step.first = stepSwitcher(step, currentPlayerID);
        currentPlayerID = (currentPlayerID + 1) % gameBoard->playersCount;
        if (!canContinuePlaying()) {
            return 7;
        }
    }
    return 2;
}

ENextStep PokerGame::stepSwitcher(std::pair<ENextStep, int> step, int playerID) {
    PlayerAbstract **&player = gameBoard->players;
    switch (step.first) {
        case BET:
            player[playerID]->gameStatistics.check = false;
            player[playerID]->gameStatistics.moneyOnTable += step.second;
            player[playerID]->gameStatistics.playerMoney -= step.second;
            gameBoard->bank += step.second;
            return BET;
        case CHECK:
            player[playerID]->gameStatistics.check = true;
            return CHECK;
        case RAISE:
            player[playerID]->gameStatistics.check = false;
            player[playerID]->gameStatistics.moneyOnTable += step.second;
            player[playerID]->gameStatistics.playerMoney -= step.second;
            gameBoard->bank += step.second + MIN_BET;
            return CALL;
        case CALL:
            player[playerID]->gameStatistics.check = false;
            player[playerID]->gameStatistics.moneyOnTable += step.second;
            player[playerID]->gameStatistics.playerMoney -= step.second;
            gameBoard->bank += step.second;
            return CALL;
        case ALL_IN:
            player[playerID]->gameStatistics.check = false;
            player[playerID]->gameStatistics.moneyOnTable += step.second;
            player[playerID]->gameStatistics.playerMoney -= step.second;
            gameBoard->bank += step.second;
            return ALL_IN;
        case FOLD:
            player[playerID]->gameStatistics.check = true;
            player[playerID]->gameStatistics.fold = true;
            return BET;
        case ALL:
            return ALL;
        case EXIT:
            return EXIT;
    }
}


bool PokerGame::canContinuePlaying() {
    recalculatePlayersMoney();
    int count = 0;
    if (gameBoard->players[0]->gameStatistics.playerMoney < MIN_BET) return false;
    for (int i = 0; i < gameBoard->playersCount; i++) {
        if (gameBoard->players[i]->gameStatistics.inGame && !gameBoard->players[i]->gameStatistics.fold) count++;
    }
    return count > 1;
}

void PokerGame::recalculatePlayersMoney() {
    for (int i = 0; i < gameBoard->playersCount; i++) {
        if (gameBoard->players[i]->gameStatistics.playerMoney < MIN_BET)
            gameBoard->players[i]->gameStatistics.inGame = false;
    }
}

void PokerGame::giveOutCardOnTableAndPlayers() {
    for (int i = 0; i < gameBoard->playersCount; i++) {
        for (int j = 0; j < MAX_CARD_ON_PLAYER_HANDS; j++) {
            gameBoard->players[i]->addCard(gameBoard->cardStock.getLastCard());
        }
    }
    for (int i = 0; i < MAX_CARD_ON_TABLE; i++) {
        gameBoard->tableCards.addCardOnTable(gameBoard->cardStock.getLastCard());
    }
}

void PokerGame::openCardsFromTable(int count) {
    try {
        (gameBoard->tableCards.openCard(count));
    } catch (std::exception &e) {
        std::cout << "Game error. " << e.what() << std::endl;
        exit(1);
    }
    auto opened = gameBoard->tableCards.getOpenedCards();
    for (int i = 0; i < gameBoard->playersCount; i++) {
        for (int j = 1; j <= count; j++) {
            gameBoard->players[i]->addCard(opened.at(opened.size() - j));
        }
    }
}


bool PokerGame::checkControl() {
    for (int i = 0; i < gameBoard->playersCount; i++) {
        if (gameBoard->players[i]->gameStatistics.inGame && !gameBoard->players[i]->gameStatistics.fold) {
            if (!gameBoard->players[i]->gameStatistics.check) return false;
        }
    }
    return true;
}

void PokerGame::setEngineForPlayers(int cardsCountForCalculateChance) {
    for (int i = 0; i < gameBoard->playersCount; i++) {
        gameBoard->players[i]->setCombinationEngine(
                CombinationsEngineFactory().getEngine(gameBoard->players[i]->getPlayingCards(),
                                                      cardsCountForCalculateChance));
    }
}

bool PokerGame::manualPlayerCanGame() {
    return (gameBoard->players[0]->gameStatistics.inGame);
}

void PokerGame::printPlayerCannotGame() {
    //todo make red;
    std::cout << "You lose." << std::endl;
}

void PokerGame::restartCheck() {
    for (int i = 0; i < gameBoard->playersCount; i++) {
        gameBoard->players[i]->gameStatistics.check = false;
    }

}

void PokerGame::showPlayerStep(std::pair<ENextStep, int> step, int playerID) {
    std::string strStep;
    switch (step.first) {
        case BET:
            strStep = "BET";
            break;
        case CHECK:
            strStep = "CHECK";
            break;
        case RAISE:
            strStep = "RAISE";
            break;
        case CALL:
            strStep = "CALL";
            break;
        case ALL_IN:
            strStep = "ALL_IN";
            break;
        case FOLD:
            strStep = "FOLD";
            break;
        case ALL:
            strStep = "ALL";
            break;
        case EXIT:
            strStep = "EXIT";
            break;
    }
    std::cout <<"Player " << gameBoard->players[playerID]->getName() << " " << strStep << " (" << std::to_string((step.first == ENextStep::EXIT || step.first == ENextStep::FOLD || step.first == ENextStep::CHECK) ? 0 : step.second) << ")" << std::endl;
}

void PokerGame::restartFold() {
    for (int i = 0; i < gameBoard->playersCount; i++) {
        gameBoard->players[i]->gameStatistics.fold = false;
    }

}


