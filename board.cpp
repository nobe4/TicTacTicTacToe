#include "board.h"

Board::Board(){
    cout << "Initalisation of the Board" << endl;

    //Input the dimention of the board
    dimension d = Input::inputMatrixDimension();

    if(d.w < 1){
        cout << "/!\\ Error : width null or negative" << endl;
        _w = 3; // default value
    }else{
        _w = d.w;
    }
    if(d.h < 1){
        cout << "/!\\ Error : heigth null or negative" << endl;
        _h = 3; // default value
    }else{
        _h = d.h;
    }

    _cells.resize(_h);
    for(int i = 0; i < _h; i ++){
        _cells[i].resize(_w);
        for(int j = 0; j < _w; j ++){
           // cout << "[" << i << ":" << j << "] = " << i+j << endl;
            _cells[i][j] = NONE;
        }
    }
}

Player Board::get(int i, int j) const{
    //    cout << "Try access to : [" << i << ":" << j << "]" << endl;

    if(i < 0){
        cout << "/!\\ Error : line null or negative" << endl;
        return NONE;
    }else if(i > this->_h){
        cout << "/!\\ Error : line too big" << endl;
        return NONE;
    }
    if(j < 0){
        cout << "/!\\ Error : column null or negative" << endl;
        return NONE;
    }else if(j > this->_w){
        cout << "/!\\ Error : column too big" << endl;
        return NONE;
    }

    //    cout << this->_cells[i][j] << endl;

    return this->_cells[i][j];
}

void Board::set(int i, int j, Player v){
    this->_cells[i][j] = v;
}

Player Board::detectEndgame(){
//     need to detect horizontally between 0 and size - paternSize
    for(int i  = 0; i < this->w(); i ++){
        for(int j  = 0; j < this->h(); j ++){
            if(this->isCellWinning(i,j)){
                return this->get(i,j);
            }
        }
    }

    return NONE;
}

bool Board::detectEndgame2(int x, int y){
    if(this->isCellWinningTwo(x,y,this->get(x,y))) return true;
    return false;
}

bool Board::isCellWinningTwo(int x, int y, Player current){
    if((recursiveCount(x, y, 0, -1, current) + 1 + recursiveCount(x, y, 0, 1, current) >= this->_patternSize))
        return true;
        //Vertical win

    if((recursiveCount(x, y, 1, -1, current) + 1 + recursiveCount(x, y, -1, 1, current) >= this->_patternSize))
        return true;
        //bottom left to up right win

    if((recursiveCount(x, y, 1, 0, current) + 1 + recursiveCount(x, y, -1, 0, current) >= this->_patternSize))
        return true;
        //Horizontal win

    if((recursiveCount(x, y, 1, 1, current) + 1 + recursiveCount(x, y, -1, -1, current) >= this->_patternSize))
        return true;
        //up left to bottom right win

    return false;
    //If nothing
}

int Board::recursiveCount(int x, int y, int xdirection, int ydirection, Player current){
    x = x + xdirection;
    y = y + ydirection;
    if((0 <= x) && (x < this->w()) && (0 <= y) && (y < this->h())){
        if(this->_cells[x][y] == current)
            return (recursiveCount(x, y, xdirection, ydirection, current)+1);
        return 0;
    }
    return 0;
}

bool Board::isCellWinning(int x, int y){
    // in this function all cell will be call, need to check over the position to determine if we apply the 4 patterns
    // horizontal rule : x < this->w() - _patternSize
    // vertical rule : y < this->h() - _patternSize
    // diagoR rule : x < this->w() - _patternSize && y < this->h() - _patternSize
    // diagoL rule : x < this->w() - _patternSize && y < this->h() - _patternSize

    int value = this->get(x,y);

    if(value == -1){
         cout << "Cell " << x << " " << y  <<  " empty, passing ... "<< endl;
        return false;
    }

    bool winning = false;
    int i = 0;

    // horizontal check
    if(y < this->h() - _patternSize + 1){
//         cout << "Horizontal check : " << x << " " << y <<endl ;
        winning = true;
        i = 0;
        do{
//             cout <<             x + _horizontalPattern.at(i).dx << " : " << y + _horizontalPattern.at(i).dy     << " => "
//                  << this->get(  x + _horizontalPattern.at(i).dx ,           y + _horizontalPattern.at(i).dy)    << " ?= " << value << endl;
            if(this->get(x + _horizontalPattern.at(i).dx , y + _horizontalPattern.at(i).dy) != value){
                winning = false;
            }
            ++i;
        }while(i < this->_patternSize && winning == true);
    }

    // vertical check
    if(x < this->w() - _patternSize + 1 && winning == false){
//         cout << "Vertical check : " << x << " " << y <<endl ;
        winning = true;
        i = 0;
        do{
//             cout <<             x + _verticalPattern.at(i).dx << " : " << y + _verticalPattern.at(i).dy     << " => "
//                  << this->get(  x + _verticalPattern.at(i).dx ,           y + _verticalPattern.at(i).dy)    << " ?= " << value << endl;
            if(this->get(x + _verticalPattern.at(i).dx , y + _verticalPattern.at(i).dy) != value){
                winning = false;
            }
            ++i;
        }while(i < this->_patternSize && winning == true);
    }

    // diagoR check
    if(x < this->w() - _patternSize + 1 && y < this->h() - _patternSize + 1 && winning == false){
//         cout << "Diago Rigth check : " << x << " " << y <<endl ;
        winning = true;
        i = 0;
        do{
//             cout <<             x + _diagoRigthPattern.at(i).dx << " : " << y + _diagoRigthPattern.at(i).dy     << " => "
//                  << this->get(  x + _diagoRigthPattern.at(i).dx ,           y + _diagoRigthPattern.at(i).dy)    << " ?= " << value << endl;
            if(this->get(x + _diagoRigthPattern.at(i).dx , y + _diagoRigthPattern.at(i).dy) != value){
                winning = false;
            }
            ++i;
        }while(i < this->_patternSize && winning == true);
    }

    // diagoL check
    if(x < this->w() - _patternSize + 1 && y < this->h() - _patternSize + 1 && winning == false){
//        cout << "Diago Left check : " << x << " " << y <<endl ;
        value = this->get(x + _diagoLeftPattern.at(0).dx , y + _diagoLeftPattern.at(0).dy); // update the value
        if(value != NONE){
            winning = true;
            i = 0;
            do{
//                 cout <<             x + _diagoLeftPattern.at(i).dx << " : " << y + _diagoLeftPattern.at(i).dy     << " => "
//                      << this->get(  x + _diagoLeftPattern.at(i).dx ,           y + _diagoLeftPattern.at(i).dy)    << " ?= " << value << endl;
                if(this->get(x + _diagoLeftPattern.at(i).dx , y + _diagoLeftPattern.at(i).dy) != value){
                    winning = false;
                }
                ++i;
            }while(i < this->_patternSize && winning == true);
        }
    }

    return winning;
}

void Board::createPatterns(int patternSize){
    cout << "Create the patterns for endgame matching" << endl;
    //     construct the 4 patterns
    //     a pattern is a list of additive integer to parse every cell in the possible solution

    //        example for a size of 3 :
    //        x is the cell checked and 0 1 2 the cells checked for this cell

    //        [   [X0]
    //            [1]
    //            [2]       ]

    //        [   [X0][1][2] ]

    //        [ [X0]
    //             [1]
    //                [2]   ]

    //        [  X    [2]
    //             [1]
    //          [0]         ]

    _patternSize = patternSize;

    _horizontalPattern.resize(_patternSize);
    _verticalPattern.resize(_patternSize);
    _diagoRigthPattern.resize(_patternSize);
    _diagoLeftPattern.resize(_patternSize);

    for(int i = 0; i < _patternSize; i ++){
        _horizontalPattern.at(i) = {0,i};
        _verticalPattern.at(i) = {i,0};
        _diagoRigthPattern.at(i) = {i,i};
        _diagoLeftPattern.at(i) = {_patternSize - i - 1, i};
    }

    //    for(int i = 0; i < _patternSize; i ++)
    //        cout << _horizontalPattern.at(i).dx << " " << _horizontalPattern.at(i).dy << endl;
    //    for(int i = 0; i < _patternSize; i ++)
    //        cout << _verticalPattern.at(i).dx << " " << _verticalPattern.at(i).dy << endl;
    //    for(int i = 0; i < _patternSize; i ++)
    //        cout << _diagoRigthPattern.at(i).dx << " " << _diagoRigthPattern.at(i).dy << endl;
    //    for(int i = 0; i < _patternSize; i ++)
    //        cout << _diagoLeftPattern.at(i).dx << " " << _diagoLeftPattern.at(i).dy << endl;
}
