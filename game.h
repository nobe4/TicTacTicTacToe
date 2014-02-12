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

public:
    Game();
    /**
     * @brief Initialisation initialize the game with board size and first player
     */
    void Initialisation();

    void gameLoop();

    void newMove();

    ~Game();
};

#endif // GAME_H
