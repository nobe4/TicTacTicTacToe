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
        
        bool winner2 = _board->detectEndgame2(lastAction.cell.line,lastAction.cell.col);
        if(winner2){
            cout << "End game" << endl;
            cont = false;
        }

        if(this->_history.size() == (unsigned int) this->_board->h()*this->_board->w()){
            cout << "End of game with a draw because no more space is available !" << endl;
            cont = false;
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
                if(this->_board->get(a.cell.line,a.cell.col) != NONE){ // if the cell is not empty
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
        this->_board->set(a.cell.line, a.cell.col, _currentPlayer);
        switchPlayer();
    }
    
    return a.type;
}

//action Game::nextAction() {
//    return minmax();
////    return random();
//}


action Game::nextAction() {
	action testPruning = minmaxWithPruning();
	cout << "Pruning : " << testPruning.type << " | " << testPruning.cell.line << " | " << testPruning.cell.col << " | " << endl;

	action b = minmax();
	cout << "Normal : " << b.type << " | " << b.cell.line << " | " << b.cell.col << " | " << endl;

	action testNew = minmaxNew();
	cout << "NewHeuristic (PLAYED): " << testNew.type << " | " << testNew.cell.line << " | " << testNew.cell.col << " | " << endl;

	return testNew;			//previously "return minmax();"
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

//int Game::heuristicValue(int x, int y) const {
//    //look around this cell, d cells away, ..., 2 cells away, and 1 cell away
//    int d = 1;
//    int value = 0;
//    //                    for (int d = 2, coef = 1; d >= 0; --d, coef *= 3) {
//    for (int x2 = std::max(0, x - d); x2 < std::min(_board->h(), x + d); ++x2) {
//        for (int y2 = std::max(0, y - d); y2 < std::min(_board->h(), y + d); ++y2) {
//            if (_board->get(x2, y2) == _currentPlayer) {
//                ++value;
//            }
//        }
//    }
//    //                    }
//    return value;
//}

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
                    a.cell.line = x;
                    a.cell.col = y;
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

   for(unsigned int i = 0; i < this->_history.size(); i++){
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



//
////Recursive implementation (base on previous heuristic and check only based on the action played
//int Game::heuristicRecursive(int prevHeurist, action prevAction) const
//{
//
//	//Check around the new action
//	cell point = prevAction.c;
//
//
//	//We check around the new point while there is not any ennemy point
//	//if (_board.recur)
//
//
//	//check history length in order to have the number of turns played
//	int nbturns = _history.size();
//
//	for (int i = 0; i < _board->h(); i++)
//	{
//		for (int j = 0; j < _board->w(); j++)
//		{
//			
//		}
//
//	}
//	//plus on a de casses libres, plus on a des variations fortes --> d�croissant selon nb tours
//
//
//	//test si on a n-1 elements alignes (avec n le nb de pions necessaires a aligner) avec une case libre sur un bord
//
//	//
//	
//	//
//	
//	//si on a plus de cases dispo, heuristique = 0 (draw)
//
//
//	
//
//}

//int Game::heuristicValue(int x, int y) const {
//    //look around this cell, d cells away, ..., 2 cells away, and 1 cell away
//    int d = 1;
//    int value = 0;
//    //                    for (int d = 2, coef = 1; d >= 0; --d, coef *= 3) {
//    for (int x2 = std::max(0, x - d); x2 < std::min(_board->h(), x + d); ++x2) {
//        for (int y2 = std::max(0, y - d); y2 < std::min(_board->h(), y + d); ++y2) {
//            if (_board->get(x2, y2) == _currentPlayer) {
//                ++value;
//            }
//        }
//    }
//    //                    }
//    return value;
//}

//
////Recursive implementation (base on previous heuristic and check only based on the action played
//int Game::heuristicRecursive(int prevHeurist, action prevAction) const
//{
//
//	//Check around the new action
//	cell point = prevAction.c;
//
//
//	//We check around the new point while there is not any ennemy point
//	//if (_board.recur)
//
//
//	//check history length in order to have the number of turns played
//	int nbturns = _history.size();
//
//	for (int i = 0; i < _board->h(); i++)
//	{
//		for (int j = 0; j < _board->w(); j++)
//		{
//			
//		}
//
//	}
//	//plus on a de casses libres, plus on a des variations fortes --> d�croissant selon nb tours
//
//
//	//test si on a n-1 elements alignes (avec n le nb de pions necessaires a aligner) avec une case libre sur un bord
//
//	//
//	
//	//
//	
//	//si on a plus de cases dispo, heuristique = 0 (draw)
//
//
//	
//
//}

double Game::heuristic2()
{
	vector<double> heuristics(2);

	int nbHoles = 0, chain = 0, heuristic = 0, pattern = 0;
	double out = 0;
	Player playerCase = NONE;

	//go throw all cases of the board
	for (int x = 0; x < _board->h(); x++)
	{
		for (int y = 0; y < _board->w(); y++)
		{
			playerCase = _board->get(x, y);
			if(playerCase != NONE)
			{
				//check each directions
				for (int cpt = 0; cpt < 4; cpt++)
				{
					//reset variables
					nbHoles = chain = 0;


					switch (cpt)
					{
						//vertical win
					case 0:
						pattern = _board->recursiveCountHoleAllowed(x, y, 0, -1, _currentPlayer, nbHoles, chain) + 1
							+ _board->recursiveCountHoleAllowed(x, y, 0, 1, _currentPlayer, nbHoles, chain);
						break;

						//bottom left to up right win
					case 1:
						pattern = _board->recursiveCountHoleAllowed(x, y, 1, -1, _currentPlayer, nbHoles, chain) + 1
							+ _board->recursiveCountHoleAllowed(x, y, -1, 1, _currentPlayer, nbHoles, chain);

						break;

						//horizontal win
					case 2:
						pattern = _board->recursiveCountHoleAllowed(x, y, 1, 0, _currentPlayer, nbHoles, chain) + 1
							+ _board->recursiveCountHoleAllowed(x, y, -1, 0, _currentPlayer, nbHoles, chain);

						break;

						//up left to bottom right win
					case 3:
						pattern = _board->recursiveCountHoleAllowed(x, y, 1, 1, _currentPlayer, nbHoles, chain) + 1
							+ _board->recursiveCountHoleAllowed(x, y, -1, -1, _currentPlayer, nbHoles, chain);
						break;

						//unusual value spotted
					default:
						cout << "error : unexpected value of cpt in heuristic2() (cpt = " << cpt << " (usually cpt in [0;3])" << endl;
						break;
					}

					//calculate the heuristic of the box based on its win possibilities

					if (pattern >= _winLength) //Previously pattern size but seems to be the same
					{
						//know if the player already won
						if ((chain) >= _winLength) //same as previous condition comment
							heuristics[playerCase] = std::numeric_limits<double>::max();	//HUMAN is 0, MACHINE is 1
						else
						{
							//we don't have a winner, so we have to calculate the heuristic
							//1- the more there are points aligned, the more you have chances to win
							//2- if you have empty box between/next to these points, that's ever better
								heuristics[playerCase] += chain * _winLength + (pattern - chain - nbHoles) * (_winLength/2 + 1) + nbHoles;
						}
					}
					else
					{
						//useless to try because not enough space to win
						heuristics[playerCase] = 0;
					}

				}
			}
		}
	}

	//Calculate the heuristic by substracting the two results
	if (_currentPlayer == HUMAN)
		out = heuristics[0] - heuristics[1];
	else if (_currentPlayer == MACHINE)
		out = heuristics[1] - heuristics[0];

	return out;
	
	//If two cases at n-1 points aligned, instant win (in specific cases)

}

action Game::minmaxNew() {
	numberOfMinMaxFunctionCalls = 0;

	action a;
	computeActionWithExtremeValueNew(minmaxDepth, a);

	cout << "numberOfMinMaxFunctionCalls : " << numberOfMinMaxFunctionCalls << endl;

	return a;
}

double Game::minmaxNew(int depth) {
	numberOfMinMaxFunctionCalls++;

	//int heuristic = heuristicValue();

	//TEST
	double heuristic = heuristic2();
	//cout << "Heuristic = " << test << endl;
	//

	if (depth == 0 || _board->detectEndgame() != NONE) {
		return heuristic;
	}
	else {
		action a;
		double extremeValue = computeActionWithExtremeValueNew(depth, a);
		if (a.type == ERROR) {
			return heuristic;
		}
		else {
			return extremeValue;
		}
	}
}

double Game::computeActionWithExtremeValueNew(int depth, action &a) {
	a.type = ERROR;

	//TODO : have to be initialized
	double extremeValue = 0;

	// Find the best action
	for (int x = 0; x < _board->h(); ++x) {
		for (int y = 0; y < _board->w(); ++y) {
			if (_board->get(x, y) == NONE) { //for each empty cell

				// Play
				_board->set(x, y, _currentPlayer);
				switchPlayer();

				// Evaluate
				double value = minmaxNew(depth - 1);

				if (a.type == ERROR ||
					(_currentPlayer == MACHINE && value < extremeValue) ||
					(_currentPlayer == HUMAN   && value > extremeValue)
					) {
					extremeValue = value;
					a.cell.line = x;
					a.cell.col = y;
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







action Game::minmaxWithPruning() {
	numberOfMinMaxFunctionCalls = 0;

	action a;

	int alpha = std::numeric_limits<int>::min();
	int beta = std::numeric_limits<int>::max();
	computeActionWithPruning(minmaxDepth, a, alpha, beta);

	cout << "numberOfMinMaxFunctionCalls (with Pruning): " << numberOfMinMaxFunctionCalls << endl;

	return a;
}


//action Game::minmaxWithPruning() {
//	numberOfMinMaxFunctionCalls = 0;
//
//	action a;
//	int alpha = std::numeric_limits<int>::min();
//	int beta = std::numeric_limits<int>::max();
//	int out = 
//
//	for (int x = 0; x < _board->h(); ++x) {
//	{
//		for (int y = 0; y < _board->w(); ++y)
//		{
//			//Reset alpha/beta values
//			alpha = std::numeric_limits<int>::min();
//			beta = std::numeric_limits<int>::max();
//
//			//Call minmax with independent reset alpha/beta values 
//			//(i.e independent minmax for all root childs.
//			minmaxWithPruning(minmaxDepth, alpha, beta);
//			//computeActionWithPruning(minmaxDepth, a, alpha, beta);
//			cout << "numberOfMinMaxFunctionCalls (with Pruning): " << numberOfMinMaxFunctionCalls << endl;
//		}
//	}
//
//
//	
//
//	return a;
//}


int Game::minmaxWithPruning(int depth, int alpha, int beta) {
	numberOfMinMaxFunctionCalls++;


	//TODO / do not calculate heuristic for all states, only the two first "if"
	int heuristic = heuristicValue();

	if (depth == 0 || _board->detectEndgame() != NONE) {
		return heuristic;
	}
	else {
		action a;
		int returnValue;

		computeActionWithPruning(depth, a, alpha, beta);
		if (a.type == ERROR) {
			return heuristic;
		}
		else {
			if (_currentPlayer == HUMAN)
			{
				//We are at a a max point, so returnValue is an alpha
				returnValue = alpha;
			}
			else if (_currentPlayer == MACHINE)
			{
				returnValue = beta;
			}

			return returnValue;
		}

	}
}

void Game::computeActionWithPruning(int depth, action &a, int& alpha, int& beta) {
	a.type = ERROR;

	bool pruning = false;

	int x = 0;
	int y = 0;
	bool end = false;
	// Find the best action

	while ((alpha < beta) && !end)
	{
		if (_board->get(x, y) == NONE) { //for each empty cell

			// Play
			_board->set(x, y, _currentPlayer);
			switchPlayer();

			// Evaluate
			int value = minmaxWithPruning(depth - 1, alpha, beta);

			if (a.type == ERROR)
			{
				if (_currentPlayer == MACHINE && value < beta)
					beta = value;
				else if (_currentPlayer == HUMAN && value > alpha)
					alpha = value;
				//else

				a.cell.line = x;
				a.cell.col = y;
				a.type = PLAY;
			}

			// Get back to former state
			_board->set(x, y, NONE);
			switchPlayer();
		}
		y++;

		if (y == _board->w())
		{
			y = 0;
			x++;
		}
		if (x == _board->h())
			end = true;
	}
}



Game::~Game(){
    delete _board;
}
