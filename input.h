#ifndef INPUT_H
#define INPUT_H

/**
 * @brief The dimension structure handle width and height representation for the matrix size
 */
typedef struct _dimension{
    int w,h;
}dimension;

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
};

#endif // INPUT_H
