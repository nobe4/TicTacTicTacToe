#include <iostream>
using namespace std;

#include "output.h"
#include "input.h"
#include "board.h"
#include "game.h"

int main(){
        Game g;
        g.Initialisation();
        g.gameLoop();

//        dimension d = Input::inputMatrixDimension();
//        Output::displayBoard(Board(d.w,d.h));
//        Input::inputAction();
//    Input::parseInputStringToInteger("23");
//    Input::parseInputStringToInteger("23.5");
//    Input::parseInputStringToInteger("-23");
//    Input::parseInputStringToInteger("-23.5");
//    Input::parseInputStringToInteger("2e3");
//    Input::parseInputStringToInteger("2e-3");
//    Input::parseInputStringToInteger("A");
//    Input::parseInputStringToInteger("23");
    return 0;
}

