#include "board.h"

Board::Board(int w, int h):_w(w),_h(h)
{
    _cells.resize(w);
    for(int i = 0; i < w; i ++){
        _cells[i].resize(h);
        for(int j = 0; j < h; j ++){
            _cells[i][j] = -1;
        }
    }
}
