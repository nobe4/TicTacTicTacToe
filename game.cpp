#include "game.h"

#include "output.h"

Game::Game(){
}

void Game::Initialisation(){
    // board initialisation
    board = new Board();
    Output::displayBoard(board);
    // choice of the first player
}

Game::~Game(){
    delete board;
}
