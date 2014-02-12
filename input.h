#ifndef INPUT_H
#define INPUT_H

/**
 * @brief The dimension structure handle width and height representation for the matrix size (does not handle integrity verifications)
 */
typedef struct _dimension{
    int w,h;
}dimension;

/**
 * @brief The ACTION_TYPE enum is a enumeration listing all type of actions possible during the game
 */
enum ACTION_TYPE{QUIT,PLAY,ERROR/*,SURRENDER*/};

/**
 * @brief The cell structure handle position of a cell in the matrix (does not handle integrity verifications)
 */
typedef struct _cell{
    int x, y;
}cell;

typedef struct _action{
    ACTION_TYPE type;
    cell c;
}action;

/**
 * @brief The INPUT_TYPE enum is a type which represente the type of an input for parsing integer
 */
enum INPUT_TYPE{OK,NEG,NNUM}; // ok, negative, non integer, non number

typedef struct _parsedInt{
    INPUT_TYPE type;
    int value;
}parsedInt;


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
