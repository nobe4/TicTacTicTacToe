#include <iostream>
using namespace std;

#include "output.h"
#include "input.h"
#include "board.h"

int main(){
    dimension d = Input::inputMatrixDimension();
    Output::displayBoard(Board(d.w,d.h));
    return 0;
}

