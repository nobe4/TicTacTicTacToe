#include "board.h"

Board::Board(int w, int h){
    if(w < 1){
        cout << "Error : width null or negative" << endl;
        _w = 3; // default value
    }else{
        _w = w;
    }

    if(h < 1){
        cout << "Error : heigth null or negative" << endl;
        _h = 3; // default value
    }else{
        _h = h;
    }

    _cells.resize(h);
    for(int i = 0; i < h; i ++){
        _cells[i].resize(w);
        for(int j = 0; j < w; j ++){
            cout << "[" << i << ":" << j << "] = " << i+j << endl;
            _cells[i][j] = i+j;
        }
    }
}

int Board::get(int i, int j) const{
    cout << "Try access to : [" << i << ":" << j << "]" << endl;


    if(i < 0){
        cout << "Error : line null or negative" << endl;
        return -1;
    }else if(i > this->_h){
        cout << "Error : line too big" << endl;
        return -1;
    }

    if(j < 0){
        cout << "Error : column null or negative" << endl;
        return -1;
    }else if(j > this->_w){
        cout << "Error : column too big" << endl;
        return -1;
    }

    return this->_cells[i][j];
}
