#include <iostream>
using namespace std;

#include "output.h"
#include "board.h"

int main(){
    Output o;
    cout << "coucou" << endl;
    o.displayBoard(Board(3,3));
    return 0;
}

