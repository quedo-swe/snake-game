#include <iostream>
#include "game.h"



int main()
{
    //Init srand
    srand(static_cast<unsigned>(time(NULL)));

    //Init game engine
    Game game;

    //Game loop
    while (game.running())
    {
        //Update
        game.update();

        //Render
        game.render();

    }
    //End of appliaction

    return 0;
}