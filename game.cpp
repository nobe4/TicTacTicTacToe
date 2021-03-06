#include <algorithm>
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

    minmaxDepth = Input::getMinMaxDepth();

    _firstPlayer= Input::inputFirstPLayer();
    Output::displayBoard(this->_board);

    _currentPlayer = _firstPlayer;
}

void Game::gameLoop(){
    bool cont = true;
    while(cont && this->newMove() != QUIT){

        action lastAction = (this->_history.at(this->_history.size() - 1)); // get last move played

        Output::displayBoard(this->_board);

        bool winner2 = _board->detectEndgame2(lastAction.cell.col,lastAction.cell.line);
        if(winner2){
            cout << "End game" << endl;
            cont = false;
        }

        if(this->_history.size() == (unsigned int) this->_board->h()*this->_board->w()){
            //CHeck que le plateau ne soit pas gagnant
            bool winner2 = _board->detectEndgame2(lastAction.cell.col,lastAction.cell.line);
            if(winner2){
                cont = false;
            }
            else{
                cout << "End of game with a draw because no more space is available !" << endl;
                cont = false;
            }
        }
    }

    displayHistoric();
    cout << "Project realised by" << endl;
    cout << "\tVictor Haffreingue" << endl;
    cout << "\tMatthieu de La Roche Saint Andre" << endl;
    cout << "\tDavid Auriac" << endl;
    cout << "\tSébastien Morinière" << endl;
    cout << "\t(c) 2014" << endl;
}

ACTION_TYPE Game::newMove(){
    cout << "##################################################" << endl;
    cout << "New move for the " << str(_currentPlayer) << endl;

    action a;
    a.type = ERROR;

    if(_currentPlayer == HUMAN) {
        a = Input::inputAction();

        if(a.type == QUIT){ // if action is quitting
            cout << "Thanks for playing !" << endl;
        }else if(a.type == ERROR){ // if there is an error in the action
            cout << "/!\\ Error in input" << endl;
        }else if(a.type == PLAY){ // if the action is playing
            if(a.cell.col >= this->_board->w() || a.cell.line >= this->_board->h()){ // if the cell is not inside the board
                cout << "/!\\ Error : cell out of the matrix" << endl;
                a.type = ERROR;
            }else{
                if(this->_board->get(a.cell.col,a.cell.line) != NONE){ // if the cell is not empty
                    cout << "/!\\ Error : cell is not empty" << endl;
                    a.type = ERROR;
                }
            }
        }else{
            cout << "/!\\ Error : invalid action" << endl;
            return ERROR;
        }
    }else{
        a = nextAction();
    }

    if (a.type == PLAY) {
        this->_history.push_back(a);
        this->_board->set(a.cell.col, a.cell.line, _currentPlayer);
        switchPlayer();
    }

    return a.type;
}

action Game::nextAction() {
    return minmax();
//    return random();
}

action Game::random() {
    action a;
    a.type = ERROR;
    bool foundEmpty = false;
    for (int x = 0; x < _board->h() && !foundEmpty; ++x) {
        for (int y = 0; y < _board->w() && !foundEmpty; ++y) {
            if (_board->get(x, y) == NONE) {
                a.cell.col = x;
                a.cell.line = y;
                a.type = PLAY;
                foundEmpty = true;
            }
        }
    }
    return a;
}

int Game::heuristicValue() const {
    Player winner = _board->detectEndgame();
    switch (winner) {
        case HUMAN:
            return 0;
            break;
        case MACHINE:
            return 1000;
            break;
        default:
            int d = 1;
            int value = 50;

            for (int x = 0; x < _board->h(); ++x) {
                for (int y = 0; y < _board->w(); ++y) {

                    //                    for (int d = 2, coef = 1; d >= 0; --d, coef *= 3) {
                    for (int x2 = std::max(0, x - d); x2 < std::min(_board->h(), x + d); ++x2) {
                        for (int y2 = std::max(0, y - d); y2 < std::min(_board->h(), y + d); ++y2) {
                            if (_board->get(x2, y2) == NONE) {
                                value += 1;
                            }else if (_board->get(x2, y2) == _currentPlayer) {
                                value += 3;
                            }
                        }
                    }
                    //                    }

                }
            }

            //cout << value << endl;
            return value;
            break;
    }
}

action Game::minmax() {
    numberOfMinMaxFunctionCalls = 0;

    action a;
    computeActionWithExtremeValue(minmaxDepth, a);

    cout << "numberOfMinMaxFunctionCalls : " << numberOfMinMaxFunctionCalls << endl;

    return a;
}

int Game::minmax(int depth) {
    numberOfMinMaxFunctionCalls++;

    int heuristic = heuristicValue();

    // if we've reached maximum depth or if a player wins
    if (depth == 0 || _board->detectEndgame() != NONE) {
        return heuristic;
    } else {
        action a;
        int extremeValue = computeActionWithExtremeValue(depth, a);
        if (a.type == ERROR) {
            return heuristic;
        } else {
            return extremeValue;
        }
    }
}

int Game::computeActionWithExtremeValue(int depth, action &a) {
    a.type = ERROR;
    // extremeValue is either the maximum or the minimum value
    // depending on the current player.
    // If ever extremeValue is not initialized later, extremeValue won't be used anyway
    // because a.type will be ERROR.
    // We initialize it here, with whatever value, to make sure that Visual Studio debuger will shut up.
    int extremeValue = 0;

    // Find the best action
    for (int x = 0; x < _board->h(); ++x) {
        for (int y = 0; y < _board->w(); ++y) {
            if (_board->get(x, y) == NONE) { //for each empty cell

                // Play
                _board->set(x, y, _currentPlayer);
                switchPlayer();

                // Evaluate
                int value = minmax(depth - 1);

                if (a.type == ERROR ||
                    (_currentPlayer == MACHINE && value < extremeValue) ||
                    (_currentPlayer == HUMAN   && value > extremeValue)) {
                    extremeValue = value;
                    a.cell.col = x;
                    a.cell.line = y;
                    a.type = PLAY;
                }

                // Get back to former state
                _board->set(x, y, NONE);
                switchPlayer();
            }
        }
    }

    return extremeValue;
}

void Game::displayHistoric(){
    bool playerPlaying = (_firstPlayer == HUMAN);

   for(int i = 0; i < this->_history.size(); i++){
        if(this->_history.at(i).type == PLAY){
            if(playerPlaying == true){
                cout << "The player  played : \t(" << this->_history.at(i).cell.col << ", " << this->_history.at(i).cell.line << ")" << endl;
            }
            else{
                cout << "The machine played : \t(" << this->_history.at(i).cell.col << ", " << this->_history.at(i).cell.line << ")" << endl;
            }
        }
        else if(this->_history.at(i).type == QUIT){
            cout << "The player left the game" << endl;
        }
        else{
            cout << "The player surrendered" << endl;
        }

        playerPlaying = !playerPlaying;
   }
   if(playerPlaying == false)
       cout << "The player won the game." << endl;
   else
       cout << "The machine won the game." << endl;
}
Game::~Game(){
    delete _board;
}
