#ifndef _LEVEL_4_H_
#define _LEVEL_4_H_
#include <string>
#include <cstdlib>
#include "level.h"
#include <vector>


class Level_4: public Level {

private:
    
        //Boolean to determune if level is random
        bool isRand;
        //File used to generate blocks when level is not random
        std::string file;
        //Vector that stores the list of block types to be generated in non-random mode
        std::vector<std::string> nextBlock;
        //Keep track of the next block to be generated and size of the nextBlock vectors, and the number of blocks added since a row has been cleared
        int pos, size, blocksAdded;
    
        //Generates the nect block using required probabilities
        std::string blockGenerate();

public:
    Level_4(int, int, std::string); //Level 4 Constructor
    
    Level_4(int, int, std::string, std::string); // Level Constructor with file for non-random

    ~Level_4(); // Level Destructor
    
    std::shared_ptr<Block> generate() override; // Returns pointer to the newest Block generated
    
    void deleteRow() override; // Tells level 4 at least one row has been
    
    //Returns a new pointer to a random level 4 or itself if level 4 is already random.
    std::shared_ptr<Level> random() override;
    
    //Returns a pointer to a new Level 4 that generates files using the file provided.
    std::shared_ptr<Level> noRandom(std::string) override;
    
    //Returns  pointer to irself since there is no level above level 4
    std::shared_ptr<Level> levelUp() override;
    
    //Returns a pointer to Level 3
    std::shared_ptr<Level> levelDown() override;
};


#endif
