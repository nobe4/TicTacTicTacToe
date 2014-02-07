#ifndef BOARD_H
#define BOARD_H

#include <iostream>
using namespace std;
#include <vector>

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
    std::vector<std::vector<int> > _cells;
    int _w, ///< width of the matrix
        _h; ///< heigth of the matrix
public:
    /**
     * @brief Board
     * @param w initial width
     * @param h initial height
     */
    Board(int w = 3, int h = 3);

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
    int get(int i, int j) const; // TODO : need to check that i and j are valid
};

#endif // BOARD_H
