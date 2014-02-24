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
    while(cont && this->newMove() != QUIT){
        Output::displayBoard(this->_board);

        if(_board->detectEndgame() != -1){
            cout << "End game" << endl;
            cont = false;
        }

        if(this->_history.size() == (unsigned int) this->_board->h()*this->_board->w()){
            cout << "End of game with a draw because no more space is available !" << endl;
            cont = false;
        }
    }

    cout << "Project realised by" << endl;
    cout << "\tVictor Haffreingue" << endl;
    cout << "\tMatthieu de La Roche Saint Andre" << endl;
    // add your name here
    cout << "\t(c) 2014" << endl;
}

ACTION_TYPE Game::newMove(){
    cout << "##################################################" << endl;
    cout << "New move for the ";
    
    action a;
    
    if(_currentPlayer == HUMAN) {
        cout << "human" << endl;
        a = Input::inputAction();
        
        if(a.type == QUIT){ // if action is quitting
            cout << "Thanks for playing !" << endl;
        }else if(a.type == ERROR){ // if there is an error in the action
            cout << "/!\\ Error in input" << endl;
        }else if(a.type == PLAY){ // if the action is playing
            if(a.c.x >= this->_board->w() || a.c.y >= this->_board->h()){ // if the cell is not inside the board
                cout << "/!\\ Error : cell out of the matrix" << endl;
                return ERROR;
            }else{
                if(this->_board->get(a.c.x,a.c.y) != NONE){ // if the cell is not empty
                    cout << "/!\\ Error : cell is not empty" << endl;
                    return ERROR;
                }else{
                    this->_history.push_back(a);
                    this->_board->set(a.c.x, a.c.y, HUMAN);
                    _currentPlayer = MACHINE;
                }
            }
        }else{
            cout << "/!\\ Error : invalid action" << endl;
            return ERROR;
        }
    }else{
        cout << "machine" << endl;
        a = nextAction();
        this->_board->set(a.c.x, a.c.y, MACHINE);
        _currentPlayer = HUMAN;
    }
    
    return a.type;
}

action Game::nextAction() {
    return random();
}

action Game::random() {
    action a;
    a.type = ERROR;
    bool foundEmpty = false;
    for (int x = 0; x < _board->h() && !foundEmpty; ++x) {
        for (int y = 0; y < _board->w() && !foundEmpty; ++y) {
            if (_board->get(x, y) == NONE) {
                a.c.x = x;
                a.c.y = y;
                a.type = PLAY;
                foundEmpty = true;
            }
        }
    }
    return a;
}

Game::~Game(){
    delete _board;
}
