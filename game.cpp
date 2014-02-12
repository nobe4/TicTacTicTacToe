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

}

void Game::newMove(){

}

Game::~Game(){
    delete _board;
}
