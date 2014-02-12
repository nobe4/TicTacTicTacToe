#ifndef GAME_H
#define GAME_H

#include <vector>

#include "board.h"
#include "structs.h"

class Game
{
private:
   Board *_board; ///< playing board
   vector<action> _history; ///< history of the played moves
   int _winLength; ///< lenght of alignment for winning

   /**
    * @brief The CURR_PLAYER enum is an enum to check whether it's the human turn or the machine turn
    */
   enum CURR_PLAYER{HUMAN,MACHINE};
   CURR_PLAYER _currentPlayer; ///< current player

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

    ~Game();
};

#endif // GAME_H
