#ifndef GAME_H
#define GAME_H

#include <vector>

#include "board.h"
#include "structs.h"

class Game
{
private:
   Board *board; // playing board
   vector<action> history; // history of the played moves

   // create a player/machine ?

public:
    Game();
    /**
     * @brief Initialisation initialize the game with board size and first player
     */
    void Initialisation();

    ~Game();
};

#endif // GAME_H
