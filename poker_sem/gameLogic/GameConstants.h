
#ifndef SEM_ALI_GAMECONSTANTS_H
#define SEM_ALI_GAMECONSTANTS_H

#include <string>

/**
 * Game settings constants
 */


const std::string PC_PLAYER_NAME[5] = {"Player 1", "Player 2", "Player 3", "Player 4", "Player 5"};
const std::string PLAYER_NAME = "You";

//// todo check int or string

///1 - all chance player, 2 - best chance player, 3 - random player(only for fun)
const int PLAYER_MODELS[5] = {1, 2, 1, 2, 1};
/////

// todo comment
const bool CHOOSE_RANDOM_PLAYER_MODEL = false;
const int PLAYER_MODEL_COUNT = 2;


const int MAX_CARD_ON_PLAYER_HANDS = 2;
const int MAX_CARD_ON_TABLE = 5;
const int DEFAULT_MONEY_WHEN_GAME_START = 2000;

const int MIN_PLAYERS = 2;
const int MAX_PLAYERS = 6;

const int MIN_BET = 10;
const int MULTIPLY_BET = 2;

const int BET_CYCLES = 2;

const int CARD_IN_CARD_STOCK = 52;

const int CARD_RANKS = 13;
const int CARD_SUITES = 4;

const double CHANCE_SIMILAR_SUITES = (13 / (52.) * 12 / (51.) * 11 / (50.) * 10 / (49.) * 9 / (48.));
const int MAX_BET_COUNT = 3;

const std::string red = "\033[1;31m";
const std::string green = "\033[1;32m";
const std::string blue = "\033[1;34m";
const std::string original = "\033[1;0m";

#endif //SEM_ALI_GAMECONSTANTS_H
