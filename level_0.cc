#include "level_0.h"
#include "level_1.h"

//The constructor for Level 0 class
Level_0::Level_0(int lev, int seed, std::string file): Level{lev, seed, file}, pos{0} {
    std::ifstream fin {file};
    std::string block;
    while(fin>>block) {
        nextBlock.emplace_back(block);
    }
    size = nextBlock.size();
}

//The destructor for Level 0 class
Level_0::~Level_0() {}

//This functions generates the next block by using the block file provided
std::shared_ptr<Block> Level_0::generate() {
    std::string block;
    if (pos == size) {
        pos = 0;
    }
    block = nextBlock[pos];
    ++pos;
    if (block == "I") {
        return std::shared_ptr<Block>(new IBlock);
    } else if (block == "J") {
        return std::shared_ptr<Block>(new JBlock);
    } else if (block == "L") {
        return std::shared_ptr<Block>(new LBlock);
    } else if (block == "O") {
        return std::shared_ptr<Block>(new OBlock);
    } else if (block == "Z") {
        return std::shared_ptr<Block>(new ZBlock);
    } else if (block == "S") {
        return std::shared_ptr<Block>(new SBlock);
    } else {
        return std::shared_ptr<Block>(new TBlock);
    }
}

//Tells level at least one row has been deleted. Relevant in Level 4 only.
void Level_0::deleteRow() {}

//Tells level to generate blocks in random order. Relevant in Level 3 and 4 only
std::shared_ptr<Level> Level_0::random() { return NULL;}

//Tells level to generate blocks in the order given in file provided
std::shared_ptr<Level> Level_0::noRandom(std::string fileName) { return NULL;}

//Returns a pointer to Level 1
std::shared_ptr<Level> Level_0::levelUp() {
    return std::shared_ptr<Level>(new Level_1{1, getSeed(), getLevel0File()});
}

//Since no level below level 0, returns a NULL pointer
std::shared_ptr<Level> Level_0::levelDown() { return NULL;}
