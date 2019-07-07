#ifndef _LEVEL_1_H_
#define _LEVEL_1_H_
#include <string>
#include <cstdlib>
#include "level.h"


class Level_1: public Level {
private:
    
    //Uses probabilities required to determine and return type of next block
    std::string blockGenerate();

public:
    
    //Constructor
    Level_1(int, int, std::string);
    
    //Destructor
    ~Level_1();

    //Retruns a pointer to the next block
    std::shared_ptr<Block> generate() override;
    
    //Tells level at least one row has been deleted. Relevant in Level 4 only.
    void deleteRow() override;
    
    //Tells level to generate blocks in random order. Relevant in Level 3 and 4 only.
    std::shared_ptr<Level> random() override;
    
    //Tells level to generate blocks in the order given in file provided. Relevant in level 3 and 4 only.
    std::shared_ptr<Level> noRandom(std::string) override;
    
    //Returns a pointer to Level 2
    std::shared_ptr<Level> levelUp() override;
    
    //Returns a pointer to Level 0
    std::shared_ptr<Level> levelDown() override;
};


#endif
