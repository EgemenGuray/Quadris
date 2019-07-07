#ifndef _LEVEL_3_H_
#define _LEVEL_3_H_
#include <string>
#include <cstdlib>
#include "level.h"
#include <vector>


class Level_3: public Level {
    
private:
    bool isRand; //Boolean to determune if level is random
    std::string file; //File used to generate blocks when level is not random
    std::vector<std::string> nextBlock; //Vector that stores the list of block types to be generated in non-random mode
    //Generates the nect block using required probabilities
    std::string blockGenerate();
    //Keep track of the next block to be generated and size of the nextBlock vectors
    int pos, size;
    
public:
    
    //Constructor
    Level_3(int, int, std::string);
    
    //Alternate Constructor for a non-random level 3.
    Level_3(int, int, std::string, std::string);

    //Destructor
    ~Level_3();
    
    //Retruns a pointer to the next block
    std::shared_ptr<Block> generate() override;
    
    //Tells level at least one row has been deleted. Relevant in Level 4 only.
    void deleteRow() override;
    
    //Returns a new pointer to a random level 3 or itself if level 3 is already random.
    std::shared_ptr<Level> random() override;
    
    //Returns a pointer to a new Level 3 that generates files using the file provided.
    std::shared_ptr<Level> noRandom(std::string) override;
    
    //Returns a pointer to Level 4
    std::shared_ptr<Level> levelUp() override;
    
    //Returns a pointer to Level 2
    std::shared_ptr<Level> levelDown() override;
};


#endif
