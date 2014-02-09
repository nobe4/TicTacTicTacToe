#include "output.h"

Output::Output(){}

void Output::displayBoard(Board b)
{
    cout << "Display of a " << b.h() << "x" << b.w() << " matrix : " << endl;
    for(int i = 0; i < b.h(); i ++){
        for(int j = 0; j < b.w(); j ++){
            cout << b.get(i,j) << "\t";
        }
        cout << "\n";
    }
}
