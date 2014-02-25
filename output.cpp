#include "output.h"

Output::Output(){}

void Output::displayBoard(const Board *b){
    int t = 0;
    cout << "Display of a " << b->h() << "x" << b->w() << " matrix : " << endl;
    cout << "y/x\t";
    for(int j = 0; j < b->w(); j ++){
        cout << j << "\t";
    }
    cout << endl;

    for(int i = 0; i < b->h(); i ++){
        cout << i << "\t";
        for(int j = 0; j < b->w(); j ++){
            t = b->get(i,j);
            if(t == NONE) cout << "_\t";
            else if(t == HUMAN) cout <<"O\t";
            else cout <<"X\t";
        }
        cout << "\n";
    }
}
