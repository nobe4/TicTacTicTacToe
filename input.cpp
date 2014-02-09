#include <iostream>
using namespace std;

#include "input.h"

Input::Input()
{
}

dimension Input::inputMatrixDimension(){
    int w = 0;
    int h = 0;
    dimension d;

    cout << "Choose a width for your matrix : ";
    cin >> w;
    cout << "Choose a heigth for your matrix : ";
    cin >> h;

    // check for data integrity
    // of let the matrix creation set the integrity ?

    d.w = w;
    d.h = h;
    return d;
}
