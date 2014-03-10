#ifndef GAME_H
#define GAME_H

#include <vector>

#include "board.h"
#include "structs.h"

class Game
{
private:
    int minmaxDepth; ///< depth used by minmax algorithm.
    Board *_board; ///< playing board
    vector<action> _history; ///< history of the played moves
    int _winLength; ///< lenght of alignment for winning
    int numberOfMinMaxFunctionCalls;

    Player _firstPlayer; ///< first player to play

    Player _currentPlayer; ///< current player
    
    /**
     * @brief returns the value of the board, or its derived possibilities, based on depth value
     */
    int minmax(int depth);
    
    /**
     * @brief switches _currentPlayer from MACHINE to human, and the opposite.
     */
    inline void switchPlayer() {_currentPlayer = _currentPlayer == HUMAN ? MACHINE : HUMAN;};
    int computeActionWithExtremeValue(int depth, action &a);

public:
    Game();
    /**
     * @brief Initialisation initialize the game with board size and first player
     */
    void Initialisation();

    /**
     * @brief gameLoop is the main function of the game : turns will be played in
     */
    void gameLoop();

    /**
     * @brief newMove parse the move input and decide to play a move, to surrender or to quit the game
     */
     ACTION_TYPE newMove();
    
    /**
     * @brief returns the next action to play by the current player
     *
     */
    action nextAction();
    
    /**
     * @brief returns a random (and correct) action to play by the current player
     */
    action random();
    
    /**
     * @brief returns an action to play by the current player, based on minmax algorithm.
     */
    action minmax();
    
//    /**
//     * @brief returns an heuristic value for playing (x, y)
//     */
//    int heuristicValue(int x, int y) const;
    
    /**
     * @brief returns an heuristic value corresponding to the current board and player.
     */
    int heuristicValue() const;

    void displayHistoric();

    ~Game();
};

#endif // GAME_H
