#ifndef INPUT_H
#define INPUT_H

#include "structs.h"

/**
 * @brief The Input class handle input from keyboard and return data structure with valid datas
 */
class Input
{
public:
    Input();
    /**
     * @brief inputMatrixDimension parse input from console and return an instance of the dimension struct
     * @return instance of the dimension struct
     */
    static dimension inputMatrixDimension();
    /**
     * @brief inputAction parse input from console and return an instance of the action structure
     * @return instance of the action structure
     */
    static action inputAction();

    /**
     * @brief parseInputStringToInteger convert a string into a integer that follow rules of the game
     * @param input is the inputed string
     * @return a parsedInt that has a type and a value
     */
    static parsedInt parseInputStringToInteger(const std::string input);
};

#endif // INPUT_H
