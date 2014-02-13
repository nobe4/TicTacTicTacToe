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
            cout << "[" << i << ":" << j << "] = " << i+j << endl;
            _cells[i][j] = -1;
        }
    }
}

int Board::get(int i, int j) const{
    //    cout << "Try access to : [" << i << ":" << j << "]" << endl;


    if(i < 0){
        cout << "/!\\ Error : line null or negative" << endl;
        return -1;
    }else if(i > this->_h){
        cout << "/!\\ Error : line too big" << endl;
        return -1;
    }

    if(j < 0){
        cout << "/!\\ Error : column null or negative" << endl;
        return -1;
    }else if(j > this->_w){
        cout << "/!\\ Error : column too big" << endl;
        return -1;
    }

    //    cout << this->_cells[i][j] << endl;

    return this->_cells[i][j];
}

void Board::set(int i, int j, int v){
    this->_cells[i][j] = v;
}

int Board::detectEndgame(){
    // need to detect horizontally between 0 and size - paternSize
    return
}

bool Board::isCellWinning(int x, int y){
    // in this function all cell will be call, need to check over the position to determine if we apply the 4 patterns
    // horizontal rule : x < this->w() - _patternSize
    // vertical rule : y < this->h() - _patternSize
    // diagoR rule : x < this->w() - _patternSize && y < this->h() - _patternSize
    // diagoL rule : x < this->w() - _patternSize && y > _patternSize
}

void Board::createPatterns(int patternSize){
    cout << "Create the patterns for endgame matching" << endl;
    // construct the 4 patterns
    // a pattern is a list of additive integer to parse every cell in the possible solution

    //    example for a size of 3 :
    //    [   [0]
    //        [1]
    //        [2]       ]

    //    [   [0][1][2] ]

    //    [ [0]
    //         [1]
    //            [2]   ]

    //    [       [2]
    //         [1]
    //      [0]         ]

    _patternSize = patternSize;

    _horizontalPattern.resize(_patternSize);
    _verticalPattern.resize(_patternSize);
    _diagoRigthPattern.resize(_patternSize);
    _diagoLeftPattern.resize(_patternSize);

    for(int i = 0; i < _patternSize; i ++){
        _horizontalPattern.at(i) = {i,0};
        _verticalPattern.at(i) = {0,i};
        _diagoRigthPattern.at(i) = {i,i};
        _diagoLeftPattern.at(i) = {_patternSize - i - 1, i};
    }

    for(int i = 0; i < _patternSize; i ++)
        cout << _horizontalPattern.at(i).dx << " " << _horizontalPattern.at(i).dy << endl;
    for(int i = 0; i < _patternSize; i ++)
        cout << _verticalPattern.at(i).dx << " " << _verticalPattern.at(i).dy << endl;
    for(int i = 0; i < _patternSize; i ++)
        cout << _diagoRigthPattern.at(i).dx << " " << _diagoRigthPattern.at(i).dy << endl;
    for(int i = 0; i < _patternSize; i ++)
        cout << _diagoLeftPattern.at(i).dx << " " << _diagoLeftPattern.at(i).dy << endl;

}
