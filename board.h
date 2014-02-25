#ifndef BOARD_H
#define BOARD_H

#include <iostream>
using namespace std;

#include <vector>

#include "input.h"

/**
 * @brief dPoint struct define a x/y difference for patern matching
 */
typedef struct _{int dx,dy;}dPoint;

/**
 * @brief The Board class
 * Define the matrix used for playing tictactoe but with arbitrary size
 */
class Board
{
private:

    /**
     * @brief _cells is a matrix of integer
     */
    std::vector<std::vector<Player> > _cells;
    int _w, ///< width of the matrix
        _h; ///< heigth of the matrix

    int _patternSize; ///< size of the patterns

    // the patterns for endgame detection
    vector<dPoint> _horizontalPattern;
    vector<dPoint> _verticalPattern;
    vector<dPoint> _diagoRigthPattern;   // up left to bottom rigth
    vector<dPoint> _diagoLeftPattern;    // up rigth to bottom left

public:
    /**
     * @brief Board constructor
     */
    Board();

    /**
     * @brief h
     * @return the heigth of the matrix
     */
    inline int h() const {return _h;}

    /**
     * @brief w
     * @return the width of the matrix
     */
    inline int w() const {return _w;}

    /**
     * @brief get
     * @param i the line wanted
     * @param j the column wanted
     * @return the value of the matrix at the line i and column j
     */
    Player get(int i, int j) const; // TODO : need to check that i and j are valid

    /**
     * @brief set
     * @param i the line wanted
     * @param j the column wanted
     * @param v the value wanted
     */
    void set(int i, int j, Player v); // todo : check if i and j are valid

    /**
     * @brief detectEndgame verify if one of the two player is winning the game
     * @param size is the min length to win
     * @return the number of the winner 0/1, or -1 in case the game hasn't reach the end.
     */
    Player detectEndgame();

    /**
     * @brief isCellWinning check if a cell is winning over the 4 patterns, will be called by detectEndgame()
     * @param x
     * @param y
     * @return true if the current cell is winning
     */
    bool isCellWinning(int x, int y);

    /**
     * @brief createPatterns create patterns that will be used to detect endgame
     * @param size is the min length to win
     */
    void createPatterns(int patternSize);
};

#endif // BOARD_H
