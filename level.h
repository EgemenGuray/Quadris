#ifndef _LEVEL_H_
#define _LEVEL_H_
#include <string>
#include <fstream>
#include "block.h"
#include "iblock.h"
#include "jblock.h"
#include "lblock.h"
#include "oblock.h"
#include "sblock.h"
#include "tblock.h"
#include "zblock.h"
#include "oneblock.h"
#include <memory>


class Level {
    int level;
    int seed;
    std::string level0File;
    
    virtual std::shared_ptr<Block> generate() = 0; //Returns ptr to the next Block
    
    virtual void deleteRow() = 0; //Tells level at least one row has been removed
    
    virtual std::shared_ptr<Level> random() = 0; // Only relevant in Level 3 and 4; Level generates Blocks randomly
    
    virtual std::shared_ptr<Level> noRandom(std::string) = 0; //Only relevant in Level 3 and 4, sets level to generate upcoming blocks using file provided.
    
    virtual std::shared_ptr<Level> levelUp() = 0; // Increases the level if possible, and returns pointer to new Level
    
    virtual std::shared_ptr<Level> levelDown() = 0; // Decreases the level if possible, and returns pointer to new Level

public:
    Level(int, int, std::string); //Constructor

    virtual ~Level(); //Destructor
    
    int getLevel(); //Retruns the value of the current level
    
    std::shared_ptr<Block> levelGenerate(); //Returns ptr to the next Block
    
    void levelDeleteRow(); //Tells level at least one row has been removed
    
    std::shared_ptr<Level> levelRandom(); // Only relevant in Level 3 and 4; Level generates Blocks randomly
    
    std::shared_ptr<Level> levelNoRandom(std::string); //Only relevant in Level 3 and 4, sets level to generate upcoming blocks using file provided.
    
    std::shared_ptr<Level> doLevelUp(); // Increases the level if possible, and returns pointer to new Level
    
    std::shared_ptr<Level> doLevelDown(); // Decreases the level if possible, and returns pointer to new Level
    
protected:
    
    int getSeed(); //Returns the seed to be used to generate random Blocks
    
    std::string getLevel0File(); //Returns the name of the file to be used to generate Blocks in Level 0
    
};


#endif
