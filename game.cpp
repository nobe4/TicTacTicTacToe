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

    _board->createPatterns(_winLength);
    // choice of the first player
    // by default it's the human
}

void Game::gameLoop(){
    bool cont = true;
    while(cont&& this->newMove() != QUIT){
        Output::displayBoard(this->_board);

        if(this->_history.size() == (unsigned int) this->_board->h()*this->_board->w()){
            cout << "End of game with a draw because no more space is available !" << endl;
            cont = false;
        }
    }

    cout << "Project realised by" << endl;
    cout << "\tVictor Haffreingue" << endl;
    // add your name here
    cout << "\t(c) 2014" << endl;
}

ACTION_TYPE Game::newMove(){
    cout << "##################################################" << endl;
    cout << "New move for the ";
    if(_currentPlayer == HUMAN) cout << "human" << endl;
    else cout << "machine" << endl;
    action a = Input::inputAction();

    if(a.type == QUIT){ // if action is quitting
        cout << "Thanks for playing !" << endl;
    }else if(a.type == ERROR){ // if there is an error in the action
        cout << "/!\\ Error in input" << endl;
    }else if(a.type == PLAY){ // if the action is playing
        if(a.c.x >= this->_board->w() || a.c.y >= this->_board->h()){ // if the cell is not inside the board
            cout << "/!\\ Error : cell out of the matrix" << endl;
            return ERROR;
        }else{
            if(this->_board->get(a.c.x,a.c.y) != -1){ // if the cell is not empty
                cout << "/!\\ Error : cell is not empty" << endl;
                return ERROR;
            }else{
                this->_history.push_back(a);
                if(_currentPlayer == HUMAN){ // if it is the human turn
                    this->_board->set(a.c.x,a.c.y,1);
                    _currentPlayer = MACHINE;
                }else{ // if this is the machine turn
                    this->_board->set(a.c.x,a.c.y,0);
                    _currentPlayer = HUMAN;
                }
            }
        }
    }else{
        cout << "/!\\ Error : invalid action" << endl;
        return ERROR;
    }

    return a.type;
}

Game::~Game(){
    delete _board;
}
