#include <iostream>
using namespace std;

#include "output.h"
#include "board.h"

int main(){
    Output o;
    o.displayBoard(Board(3,3));

    o.displayBoard(Board(4,6));
    return 0;
}

