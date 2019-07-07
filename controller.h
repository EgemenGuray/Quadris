#ifndef _CONTROLLER_H
#define _CONTROLLER_H
#include <string>
#include "game.h"

class Controller {
         std::shared_ptr<Game> game;
    
        //This function gets the command input into the Controller and determines correct command. Used for eliminating human error in input.
        std::string correctCommand(std::string);
    
        //Gets the multiplier(number of times to execute command) attached to command, if any.
        std::string getMultiplier(std::string);
    
        //Forcer takes in a game pointer and a string for the block type, and forces the block onto the game calling game's force function with a block of that type.
        void forcer(std::string, std::shared_ptr<Game>);
    
        //TestForcer takes in a game pointer and a string for the block type, and forces the block onto the game calling game's force function with a block of that type. This is used for testing the game.
        void testForcer(std::string, std::shared_ptr<Game>);
   
public:
        //Constructor
        Controller(bool, int, int, bool, std::string, std::string);
    
        //Destructor
        ~Controller();

        //Receives command from player and applies it to game.
        void applyCommand(std::string);
};


#endif
