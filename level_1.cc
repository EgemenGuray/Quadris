#include "level_1.h"
#include "level_0.h"
#include "level_2.h"

//Constructor
Level_1::Level_1(int lev, int seed, std::string level0File): Level{lev, seed, level0File} {
    std::srand(seed);
}

//Destructor
Level_1::~Level_1() {}

//Uses probabilities required to determine and return type of next block
std::string Level_1::blockGenerate() {
    //12 used since all blocks have double probability of being chosen over S or Z, thus 12 options.
    int num = ((rand() % 12) + 1);
    if ((num == 1) || (num == 2)) {
        return "I";
    } else if ((num == 3) || (num == 4)) {
        return "J";
    } else if ((num == 5) || (num == 6)) {
        return "L";
    } else if ((num == 7) || (num == 8)) {
        return "O";
    } else if ((num == 9) || (num == 10)) {
        return "T";
    } else if (num == 11) {
        return "Z";
    } else {
        return "S";
    }
}

//Retruns a pointer to the next block
std::shared_ptr<Block> Level_1::generate() {
    std::string block = blockGenerate();
    
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
void Level_1::deleteRow() {}

//Returns pointer to a new random level. Relevant in Level 3 and 4 only, thus this returns a NULL pointer
std::shared_ptr<Level> Level_1::random() {return NULL;}

//Returns pointer to a new non-random level that generates files using file given. Relevant in Level 3 and 4 only, thus this returns a NULL pointer
std::shared_ptr<Level> Level_1::noRandom(std::string blocksFile) {return NULL;}

//Returns a pointer to Level 2
std::shared_ptr<Level> Level_1::levelUp() {
    return std::shared_ptr<Level>(new Level_2{2, getSeed(), getLevel0File()});
}

//Returns a pointer to Level 0
std::shared_ptr<Level> Level_1::levelDown() {
    return std::shared_ptr<Level>(new Level_0{0, getSeed(), getLevel0File()});
}
