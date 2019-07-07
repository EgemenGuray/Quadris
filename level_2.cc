#include "level_2.h"
#include "level_1.h"
#include "level_3.h"


//Constructor
Level_2::Level_2(int lev, int seed, std::string level0File): Level{lev, seed, level0File} {
    std::srand(seed);
}

//Destructor
Level_2::~Level_2() {}

//Uses probabilities required to determine and return type of next block
std::string Level_2::blockGenerate() {
    //Number 7 used since each block has equal probability
    int num = ((rand() % 7) + 1);
    if (num == 1) {
        return "I";
    } else if (num == 2) {
        return "J";
    } else if (num == 3) {
        return "L";
    } else if (num == 4) {
        return "O";
    } else if (num == 5) {
        return "T";
    } else if (num == 6) {
        return "Z";
    } else {
        return "S";
    }
}

//Retruns a pointer to the next block
std::shared_ptr<Block> Level_2::generate() {
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
void Level_2::deleteRow() {}

//Returns pointer to a new random level. Relevant in Level 3 and 4 only, thus thi s returns a Null pointer
std::shared_ptr<Level> Level_2::random() {return NULL;}

//Returns pointer to a new non-random level that generates blocks in the order given in file provided. Relevant in level 3 and 4 only, thus this return a Null pointer.
std::shared_ptr<Level> Level_2::noRandom(std::string blocksFile) {return NULL;}

//Returns a pointer to Level 3
std::shared_ptr<Level> Level_2::levelUp() {
    return std::shared_ptr<Level>(new Level_3{3, getSeed(), getLevel0File()});
}

//Returns a pointer to Level 31
std::shared_ptr<Level> Level_2::levelDown() {
    return std::shared_ptr<Level>(new Level_1{1, getSeed(), getLevel0File()});
}
