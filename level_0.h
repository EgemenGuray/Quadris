#ifndef _LEVEL_0_H_
#define _LEVEL_0_H_
#include <string>
#include "level.h"
#include <memory>
#include <vector>

class Level_0: public Level {
    std::vector<std::string> nextBlock;
    int pos, size;

public:
    
    //The constructor
    Level_0(int, int, std::string);
    
    //Destructor
    ~Level_0();
    
    //Retruns a pointer to the next block
    std::shared_ptr<Block> generate() override;
    
    //Tells level at least one row has been deleted. Relevant in Level 4 only.
    void deleteRow() override;
    
    //Tells level to generate blocks in random order. Relevant in Level 3 and 4 only
    std::shared_ptr<Level> random() override;
    
    //Tells level to generate blocks in the order given in file provided. Relevant in level 3 and 4 only.
    std::shared_ptr<Level> noRandom(std::string) override;
    
    //Returns a pointer to Level 1
    std::shared_ptr<Level> levelUp() override;
    
    //Since no level below level 0, returns a NULL pointer
    std::shared_ptr<Level> levelDown() override;
};


#endif
