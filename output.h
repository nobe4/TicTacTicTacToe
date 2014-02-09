#ifndef OUTPUT_H
#define OUTPUT_H

#include <iostream>
using namespace std;

#include "board.h"

/**
 * @brief The Output class
 * Used for all graphical output (mostly console)
 */
class Output
{
public:
    Output();
    static void displayBoard(Board b);

};

#endif // OUTPUT_H
