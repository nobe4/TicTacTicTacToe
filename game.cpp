#include "game.h"

#include "output.h"

Game::Game(){
}

void Game::Initialisation(){
    // board initialisation
    _board = new Board();
    Output::displayBoard(_board);

    // set min to be the minimal of board width and board heigth
    int min = _board->h();
    if(_board->w() < min) min = _board->w();

    // initialisation of minimal length to win
    _winLength = Input::inputWinLength(min);

    // choice of the first player
    // by default it's the human
}

void Game::gameLoop(){
    while(this->newMove() == PLAY){
        Output::displayBoard(this->_board);
    }
}

ACTION_TYPE Game::newMove(){
    cout << "New move : " << endl;
    action a = Input::inputAction();

    if(a.type == QUIT){
        cout << "No new move : quitting game..." << endl;
    }else if(a.type == ERROR){
        cout << "Error in input" << endl;
    }else if(a.type == PLAY){
        playMove(a.c);
    }else{
        cout << "Error : invalid action" << endl;
        return ERROR;
    }

    return a.type;
}


void Game::playMove(cell c){
    // use c to place a new move on the board
    this->_board->set(c.x,c.y,1);
    // verifications ?
}

Game::~Game(){
    delete _board;
}
