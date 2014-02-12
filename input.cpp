#include <iostream>
#include <sstream>

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

    // check for input integrity :
    // (1) no negative number
    // (2) no float number
    // ...

    d.w = w;
    d.h = h;
    return d;
}

action Input::inputAction(){
    action a = {ERROR,{-1,-1}};

    parsedInt i;
    string s; // used for parsing input

    cout << "Choose an action to performe : (Q)UIT/(P)LAY :";
    cin >> s;

    if(s == "P" || s == "PLAY"){
        cout << "Input x for your play : ";
        cin >> s;
        i = parseInputStringToInteger(s);

        if(i.type == OK){
            a.c.x = i.value;
            cout << "Input y for your play : ";
            cin >> s;
            i = parseInputStringToInteger(s);
            if(i.type == OK){
                a.type = PLAY;
                a.c.y = i.value;
                cout << "Inputed : " << a.c.x << " " << a.c.y << endl;
            }else{
                cout << "Error in y input, aborting..." << endl;
            }
        }else{
            cout << "Error in x input, aborting..." << endl;
        }
    }else if(s == "QUIT" || s == "Q"){
        cout << "Quitting Game ..."<< endl;
        a.type = QUIT;
    }else{
        cout << "Input unknown, aborting...";
    }

    return a;
}

parsedInt Input::parseInputStringToInteger(const string input){
    stringstream stream;
    stream << input;
    int n = 0; // temporary int for parsing
    parsedInt i; // returned parsed int
    i.value = 0;

    if (!(stream >> n)){ // parsing string to int
        cout << "Error parsing : Not a Number" << endl;
        i.type = NNUM;
    }else{
        cout << "Parsed int : " << n << endl;
        if(n < 0){
            cout << "Error : negative value" << endl;
            i.type = NEG;
        }else{
            i.type = OK;
            i.value = n;
        }
    }

    return i;
}
