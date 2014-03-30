#include <iostream>
#include <sstream>

using namespace std;

#include "input.h"

Input::Input()
{
}

dimension Input::inputMatrixDimension(){
    dimension d = {3,3}; // default values
    string s;

    cout << "Choose a width for your matrix : ";
    cin >> s;
    parsedInt i = parseInputStringToInteger(s);
    if(i.type == OK){
        if(i.value < d.w){
            cout << "Value too low : w = 3" << endl;
        }else{
            d.w = i.value;
        }
        cout << "Choose a heigth for your matrix : ";
        cin >> s;
        i = parseInputStringToInteger(s);
        if(i.type == OK){
            if(i.value < d.h){
                cout << "Value too low : h = 3" << endl;
            }else{
                d.h = i.value;
            }

            cout << "Inputed : " << d.w << " " << d.h << endl;
        }else{
            cout << "/!\\ Error in h input : h = 3" << endl;
        }
    }else{
        cout << "/!\\ Error in w input : w = 3" << endl;
    }
    return d;
}

int Input::getMinMaxDepth() {
    string input;
    int max = 3;
    
    cout << "Input the maximal depth to run MinMax algorithm : ";
    cin >> input;
    parsedInt i = parseInputStringToInteger(input);
    
    if(i.type == OK){
        if(i.value <= 0){
            cout << "/!\\ Error : Value too low : " << max << endl;
            return max;
        }else{
            cout << "Parsed value for the maximal depth to run MinMax algorithm : " << i.value << endl;
            return i.value;
        }
    }else{
        cout << "/!\\ Error : Not a number : return " << max << endl;
    }
    
    return max; // bad input : default size : max
    
}

int Input::inputWinLength(int max){
    string input;

    cout << "Input the value for the length to win : ";
    cin >> input;

    parsedInt i = parseInputStringToInteger(input);

    if(i.type == OK){
        // the value is > 0
        if(i.value > max){
            cout << "/!\\ Error : Value too big : return " << max << endl;
            return max;
        }else if(i.value < 3){
            cout << "/!\\ Error : Value too low : return " << max << endl;
            return max;
        }else{
            cout << "Parsed value for the length to win : " << i.value << endl;
            return i.value;
        }
    }else{
        cout << "/!\\ Error : Not a number : return " << max << endl;
    }

    return max; // bad input : default size : max
}

action Input::inputAction(){
    action a = {ERROR,{-1,-1}};

    parsedInt i;
    string s; // used for parsing input

    cout << "Choose an action to performe : (Q)UIT/(P)LAY :";
    cin >> s;

    if(s == "P" || s == "PLAY" || s == "p" || s == "play"){
        cout << "Input x for your play : ";
        cin >> s;
        i = parseInputStringToInteger(s);

        if(i.type == OK){
            a.cell.line = i.value;
            cout << "Input y for your play : ";
            cin >> s;
            i = parseInputStringToInteger(s);
            if(i.type == OK){
                a.type = PLAY;
                a.cell.col = i.value;
                cout << "Inputed : " << a.cell.line << " " << a.cell.col << endl;
            }else{
                cout << "/!\\ Error in y input, aborting..." << endl;
            }
        }else{
            cout << "/!\\ Error in x input, aborting..." << endl;
        }
    }else if(s == "QUIT" || s == "Q" || s == "quit" || s == "q"){
        cout << "Quitting game ..."<< endl;
        a.type = QUIT;
    }else{
        cout << "Input unknown, aborting..." << endl;
    }

    return a;
}

Player Input::inputFirstPLayer(){
    //ASK FOR THE FIRST PLAYER TO PLAY

    string s = "";
    do{
        cout << "Choose wich one start first : (M)achine/(H)Human" << endl;
        cin >> s;
    }while((s != "M") && (s != "H") && (s != "Machine") && (s != "Human"));

    if((s == "M") || (s == "Machine"))
        return MACHINE;
    else
        return HUMAN;
}

parsedInt Input::parseInputStringToInteger(const string input){
    stringstream stream;
    stream << input;
    int n = 0; // temporary int for parsing
    parsedInt i; // returned parsed int
    i.value = 0;

    if (!(stream >> n)){ // parsing string to int
        cout << "/!\\ Error parsing : Not a Number " << endl;
        i.type = NNUM;
    }else{
        cout << "Parsed int : " << n << endl;
        if(n < 0){
            cout << "/!\\ Error : negative value" << endl;
            i.type = NEG;
        }else{
            i.type = OK;
            i.value = n;
        }
    }

    return i;
}
