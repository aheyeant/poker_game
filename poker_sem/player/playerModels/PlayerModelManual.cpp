
#include <utility>
#include "PlayerModelManual.h"

PlayerModelManual::PlayerModelManual(std::string playerName) : PlayerAbstract(std::move(playerName)) {}

std::pair<ENextStep, int> PlayerModelManual::getNextStep(ENextStep nextStep, int bet) {
    switch (nextStep) {
        case BET:
            return makeBet();
        case CHECK:
            return makeBet();
        case RAISE:
            return makeBet();
        case CALL:
            return makeCall(bet);
        case ALL_IN:
            return makeAlIn();
        case FOLD:
            return makeBet();
        case ALL:
            return makeBet();
        case EXIT:
            return makeBet();
    }
}

std::pair<ENextStep, int> PlayerModelManual::makeStep() {
    int readValue = 0;
    if (gameStatistics.playerMoney < MULTIPLY_BET * MIN_BET) {
        while (true) {
            std::cout << "1: Bet(" << std::to_string(MIN_BET) << ") 2: Fold 3: All-in("
                      << std::to_string(gameStatistics.playerMoney) << ") 4: Check 6:Exit\n";
            std::cin >> readValue;
            if (readValue == 1 || readValue == 2 || readValue == 3 || readValue == 5 || readValue == 6) {
                switch (readValue) {
                    case 1:
                        return std::pair<ENextStep, int>{ENextStep::BET, MIN_BET};
                    case 2:
                        return std::pair<ENextStep, int>{ENextStep::FOLD, 0};
                    case 3:
                        return std::pair<ENextStep, int>{ENextStep::ALL_IN, gameStatistics.playerMoney};
                    case 4:
                        return std::pair<ENextStep, int>{ENextStep::CHECK, 0};
                    case 6:
                        return std::pair<ENextStep, int>{ENextStep::EXIT, 0};
                    default:
                        throw std::logic_error("Undefined error.");
                }
            } else {
                std::cout << "Please write num 1, 2, 3, 4 or 5\n";
            }
        }
    }

    while (true) {
        std::cout << "1: Bet(" << std::to_string(MIN_BET) <<") 2: Raise(" << std::to_string(MULTIPLY_BET) << " x " << std::to_string(MIN_BET) << ") 3: Fold 4: All-in(" << std::to_string(gameStatistics.playerMoney) << ") 5:Exit\n";
        std::cin >> readValue;
        if (readValue > 0 && readValue < 6) {
            switch (readValue) {
                case 1:
                    return std::pair<ENextStep, int>{ENextStep::BET, MIN_BET};
                case 2:
                    return std::pair<ENextStep, int>{ENextStep::RAISE, MULTIPLY_BET * MIN_BET};
                case 3:
                    return std::pair<ENextStep, int>{ENextStep::FOLD, 0};
                case 4:
                    return std::pair<ENextStep, int>{ENextStep::ALL_IN, gameStatistics.playerMoney};
                case 5:
                    return std::pair<ENextStep, int>{ENextStep::EXIT, 0};
                default: throw std::logic_error("Undefined error.");
            }
        } else {
            std::cout << "Please write num 1 - 5\n";
        }

    }

    //std::cout << "1: Call(" << std::to_string(MIN_BET) <<") 2: Raise(x" << std::to_string(MIN_BET) << ") 3: Fold 4: All-in(" << std::to_string(gameStatistics.playerMoney) << ")\n";
}

std::pair<ENextStep, int> PlayerModelManual::makeBet() {
    int readValue = 0;
    if (gameStatistics.playerMoney < MULTIPLY_BET * MIN_BET) {
        while (true) {
            std::cout << "1: Bet(" << std::to_string(MIN_BET) << ") 2: Fold 3: All-in("
                      << std::to_string(gameStatistics.playerMoney) << ") 4: Check 6: Exit\n";
            std::cin >> readValue;
            if (readValue == 1 || readValue == 2 || readValue == 3 || readValue == 5 || readValue == 6) {
                switch (readValue) {
                    case 1:
                        return std::pair<ENextStep, int>{ENextStep::BET, MIN_BET};
                    case 2:
                        return std::pair<ENextStep, int>{ENextStep::FOLD, 0};
                    case 3:
                        return std::pair<ENextStep, int>{ENextStep::ALL_IN, gameStatistics.playerMoney};
                    case 4:
                        return std::pair<ENextStep, int>{ENextStep::CHECK, 0};
                    case 6:
                        return std::pair<ENextStep, int>{ENextStep::EXIT, 0};
                    default:
                        throw std::logic_error("Undefined error.");
                }
            } else {
                std::cout << "Please write num 1, 2, 3, 4 or 6\n";
            }
        }
    }

    while (true) {
        std::cout << "1: Bet(" << std::to_string(MIN_BET) << ") 2: Raise(" << std::to_string(MULTIPLY_BET) << " x "
                  << std::to_string(MIN_BET) << ") 3: Fold 4: All-in(" << std::to_string(gameStatistics.playerMoney)
                  << ") 5: Check 6: Exit\n";
        std::cin >> readValue;
        if (readValue > 0 && readValue < 7) {
            switch (readValue) {
                case 1:
                    return std::pair<ENextStep, int>{ENextStep::BET, MIN_BET};
                case 2:
                    return std::pair<ENextStep, int>{ENextStep::RAISE, MULTIPLY_BET * MIN_BET};
                case 3:
                    return std::pair<ENextStep, int>{ENextStep::FOLD, 0};
                case 4:
                    return std::pair<ENextStep, int>{ENextStep::ALL_IN, gameStatistics.playerMoney};
                case 5:
                    return std::pair<ENextStep, int>{ENextStep::CHECK, 0};
                case 6:
                    return std::pair<ENextStep, int>{ENextStep::EXIT, 0};
                default:
                    throw std::logic_error("Undefined error.");
            }
        } else {
            std::cout << "Please write num 1, 2, 3, 4, 5 or 6\n";
        }
    }
}

std::pair<ENextStep, int> PlayerModelManual::makeCall(int bet) {
    int readValue = 0;
    if (gameStatistics.playerMoney < bet) {
        while (true) {
            std::cout << "1: Fold 6: Exit\n";
            std::cin >> readValue;
            if (readValue == 1 || readValue == 6) {
                switch (readValue) {
                    case 1:
                        return std::pair<ENextStep, int>{ENextStep::CALL, bet};
                    case 6:
                        return std::pair<ENextStep, int>{ENextStep::EXIT, 0};
                    default:
                        throw std::logic_error("Undefined error.");
                }
            } else {
                std::cout << "Please write num 1 or 6\n";
            }

        }
    }

    while (true) {
        std::cout << "1: Call(" << std::to_string(bet) << ") 2: Fold 6: Exit\n";
        std::cin >> readValue;
        if (readValue == 1 || readValue == 2 || readValue == 6) {
            switch (readValue) {
                case 1:
                    return std::pair<ENextStep, int>{ENextStep::CALL, bet};
                case 2:
                    return std::pair<ENextStep, int>{ENextStep::FOLD, 0};
                case 6:
                    return std::pair<ENextStep, int>{ENextStep::EXIT, 0};
                default:
                    throw std::logic_error("Undefined error.");
            }
        } else {
            std::cout << "Please write num 1, 2 or 6\n";
        }
    }
}

std::pair<ENextStep, int> PlayerModelManual::makeAlIn() {
    int readValue = 0;

    while (true) {
        std::cout << "1: All-in(" << std::to_string(gameStatistics.playerMoney) << ") 2: Fold 6: Exit\n";
        std::cin >> readValue;
        if (readValue == 1 || readValue == 2 || readValue == 6) {
            switch (readValue) {
                case 1:
                    return std::pair<ENextStep, int>{ENextStep::ALL_IN, gameStatistics.playerMoney};
                case 2:
                    return std::pair<ENextStep, int>{ENextStep::FOLD, 0};
                case 6:
                    return std::pair<ENextStep, int>{ENextStep::EXIT, 0};
                default:
                    throw std::logic_error("Undefined error.");
            }
        } else {
            std::cout << "Please write num 1, 2 or 6\n";
        }
    }
}
