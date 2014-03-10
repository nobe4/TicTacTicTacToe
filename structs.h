#ifndef STRUCTS_H
#define STRUCTS_H

#include <string>

/**
 * @brief The dimension structure handle width and height representation for the matrix size (does not handle integrity verifications)
 */
typedef struct _dimension{
    int w,h;
}dimension;

/**
 * @brief The ACTION_TYPE enum is a enumeration listing all type of actions possible during the game
 */
enum ACTION_TYPE {QUIT,PLAY,ERROR/*,SURRENDER*/};

/**
 * @brief The Player enum is an enum to check whether it's the human turn or the machine turn
 */
enum Player{HUMAN, MACHINE, NONE};

inline std::string str(Player p) {
    switch (p) {
        case HUMAN:
            return "human";
        case MACHINE:
            return "computer";
        default:
            return "NONE";
    }
}


/**
 * @brief The cell structure handle position of a cell in the matrix (does not handle integrity verifications)
 */
typedef struct _cell{
    int col, line;
}Cell;

typedef struct _action{
    ACTION_TYPE type;
    Cell cell;
}action;

/**
 * @brief The INPUT_TYPE enum is a type which represente the type of an input for parsing integer
 */
enum INPUT_TYPE{OK,NEG,NNUM}; // ok, negative, non integer, non number

typedef struct _parsedInt{
    INPUT_TYPE type;
    int value;
}parsedInt;



#endif // STRUCTS_H
