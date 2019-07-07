#include "controller.h"
#include <fstream>
#include "iblock.h"
#include "jblock.h"
#include "lblock.h"
#include "oblock.h"
#include "zblock.h"
#include "sblock.h"
#include "tblock.h"


//The constructor for Controller class
Controller::Controller(bool outTypeText, int seed, int startLevel, bool noSpecial, std::string file1, std::string file2) {
    game = std::shared_ptr<Game>(new Game{outTypeText, startLevel, seed, file1, file2, noSpecial});
    
}

//The destructor for Controller class
Controller::~Controller() {}

//This function gets the command input into the Controller and determines which command should be called on game. Used for eliminating human error in input.
std::string Controller::correctCommand(std::string input) {
    int inputSize = input.size();
    if (input.substr(0, 3) == "lef") {
        return "left";
    } else if (input.substr(0, 2) == "ri") {
        return "right";
    } else if (input.substr(0, 2) == "ra") {
        return "random";
    } else if (input.substr(0, 2) == "do") {
        return "down";
    } else if (input.substr(0, 2) == "cl") {
        return "clockwise";
    } else if (input.substr(0, 2) == "co") {
        return "counterclockwise";
    } else if (input.substr(0, 2) == "dr") {
        return "drop";
    } else if ((input.substr(0, 6) == "levelu") || (input.substr(0, 6) == "levelU")) {
        return "levelUp";
    } else if ((input.substr(0, 6) == "leveld") || (input.substr(0, 6) == "levelD")) {
        return "levelDown";
    } else if (input.substr(0, 2) == "ra") {
        return "random";
    } else if (input.substr(0, 2) == "no") {
        return "norandom";
    } else if (input.substr(0, 2) == "ni") {
        return "night";
    } else if (input.substr(0, 2) == "li") {
        return "light";
    } else if (input.substr(0, 1) == "s") {
        return "sequence";
    } else if ((input.substr(0, 1) == "I") && (inputSize == 1)) {
        return "I";
    } else if ((input.substr(0, 1) == "J") && (inputSize == 1)) {
        return "J";
    } else if ((input.substr(0, 1) == "L") && (inputSize == 1)) {
        return "L";
    } else if ((input.substr(0, 1) == "O") && (inputSize == 1)) {
        return "O";
    } else if ((input.substr(0, 1) == "S") && (inputSize == 1)) {
        return "S";
    } else if ((input.substr(0, 1) == "Z") && (inputSize == 1)) {
        return "Z";
    } else if ((input.substr(0, 1) == "T") && (inputSize == 1)){
        return "T";
    } else if (input.substr(0, 1) == "b") {
        return "blind";
    } else if (input.substr(0, 1) == "h") {
        return "heavy";
    } else if (input.substr(0, 1) == "f") {
        return "force";
    } else if (input.substr(0, 2) == "re") {
        return "restart";
    } else {
        return "";
    }
}

//Gets the multiplier(number of times to execute command) attached to command, if any. 
std::string Controller::getMultiplier(std::string input) {
    std::string smultiplier;
    if (((input[0] >= 'a') && (input[0] <= 'z')) || ((input[0] >= 'A') && (input[0] <= 'Z'))) {
        smultiplier = "1";
    } else if ((input[0] >= '0') && (input[0] <= '9')) {
        int count = 1;
        smultiplier = input.substr(0, 1);
        while (true) {
            if (((input[count] >= 'a') && (input[count] <= 'z')) || ((input[count] >= 'A') && (input[count] <= 'Z'))) { break; }
            smultiplier = smultiplier + input.substr(count, 1);
            ++count;
        }
    } else { }
    return smultiplier;
}

//Forcer takes in a game pointer and a string for the block type, and forces the block onto the game calling game's force function with a block of that type.
void Controller::forcer(std::string block, std::shared_ptr<Game> game) {
    if (block == "O") {
        game->force(std::shared_ptr<Block>(new OBlock));
    } else if (block == "I") {
        game->force(std::shared_ptr<Block>(new IBlock));
    } else if (block == "J") {
        game->force(std::shared_ptr<Block>(new JBlock));
    } else if (block == "Z") {
        game->force(std::shared_ptr<Block>(new ZBlock));
    } else if (block == "L") {
        game->force(std::shared_ptr<Block>(new LBlock));
    } else if ( block == "S") {
        game->force(std::shared_ptr<Block>(new SBlock));
    } else {
        game->force(std::shared_ptr<Block>(new TBlock));
    }
}



//TestForcer takes in a game pointer and a string for the block type, and forces the block onto the game calling game's force function with a block of that type. This is used for testing the game.
void Controller::testForcer(std::string block, std::shared_ptr<Game> game) {
    if (block == "O") {
        game->testForce(std::shared_ptr<Block>(new OBlock));
    } else if (block == "I") {
        game->testForce(std::shared_ptr<Block>(new IBlock));
    } else if (block == "J") {
        game->testForce(std::shared_ptr<Block>(new JBlock));
    } else if (block == "Z") {
        game->testForce(std::shared_ptr<Block>(new ZBlock));
    } else if (block == "L") {
        game->testForce(std::shared_ptr<Block>(new LBlock));
    } else if ( block == "S") {
        game->testForce(std::shared_ptr<Block>(new SBlock));
    } else {
        game->testForce(std::shared_ptr<Block>(new TBlock));
    }
}


//Receives command from player and applies it to game.
void Controller::applyCommand(std::string input) {
    
    int pos;
    std::string file;
    
    std::string smultiplier = getMultiplier(input);

    int smultiplierCount = smultiplier.size();
    
    if ((input[0] >= '0') && (input[0] <= '9')) {
        input = input.substr(smultiplierCount);
    }
    
    int multiplier = std::stoi(smultiplier);
    std::string command = correctCommand(input);
    
    //We have command and multiplier

    if (command == "left") {
        game->left(multiplier);
    } else if (command == "right") {
        game->right(multiplier);
    } else if (command == "down") {
        game->down(multiplier);
    } else if (command == "drop") {
        game->drop(multiplier);
    } else if (command == "clockwise"){
        game->clockwise(multiplier);
    } else if (command == "counterclockwise") {
        game->cclockwise(multiplier);
    } else if (command == "levelUp") {
        game->levelUp(multiplier);
    } else if (command == "levelDown") {
        game->levelDown(multiplier);
    } else if (command == "norandom") {
        pos = 0;
        while (true) {
            if (input[pos] == ' ') {
                file = input.substr(++pos);
                break;
            }
            ++pos;
        }
        game->noRandom(file);
    } else if (command == "sequence") {
        pos = 0;
        while (true) {
            if (input[pos] == ' ') {
                file = input.substr(++pos);
                break;
            }
            ++pos;
        }
        std::ifstream fin {file};
        std::string read, newCommand;
        while (fin>>read) {
            pos = 0;
            while (true) {
                if ((read[pos] >= '0') && (read[pos] <= '9')) {
                    ++pos;
                    continue;
                } else {
                    newCommand = read.substr(pos);
                    break;
                }
            }
            if ((correctCommand(newCommand) == "random") || (correctCommand(newCommand) == "sequence")) {
                newCommand = read + " ";
                fin>>read;
                newCommand = newCommand + read;
                applyCommand(newCommand);
            } else {
                applyCommand(read);
            }
        }
    } else if (command == "random") {
        game->random();
    } else if (command == "night") {
        game->changeGraphicsMode(true);
    } else if (command == "light") {
        game->changeGraphicsMode(false);
    } else if (command == "restart") {
        game->restart();
    } else if (command == "blind") {
        game->blind();
    } else if (command == "heavy") {
        int moveDown = 2;
        game->heavy(moveDown);
    } else if (command == "force") {
        pos = 0;
        std::string block;
        while (true) {
            if (input[pos] == ' ') {
                block = input.substr(++pos);
                break;
            }
            ++pos;
        }
        forcer(block, game);
    } else if ((command == "I") || (command == "J") || (command == "L") || (command == "O") || (command == "Z") || (command == "S") || (command == "T")) {
        testForcer(command, game);
    } else {throw std::out_of_range{"INcorrect Command"};}
}
