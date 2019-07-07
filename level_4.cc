#include "level_4.h"
#include "level_3.h"


//Level 4 Constructor
Level_4::Level_4(int lev, int seed, std::string level0File): Level{lev, seed, level0File}, isRand{true}, blocksAdded{0} {
    std::srand(seed);
}

// Level 4 Constructor with file for non-random
Level_4::Level_4(int lev, int seed, std::string level0File, std::string file): Level{lev, seed, level0File}, isRand{false}, file{file}, pos{0}, blocksAdded{0} {
    
    std::ifstream fin {file};
    std::string block;
    while (fin>>block) {
        nextBlock.emplace_back(block);
    }
    size = nextBlock.size();
}

// Level 4 Destructor
Level_4::~Level_4() {}

//Generates the nect block using required probabilities
std::string Level_4::blockGenerate() {
    int num = ((rand() % 9) + 1);
    if (num == 1) {
        return "I";
    } else if (num == 2) {
        return "J";
    } else if (num == 3) {
        return "L";
    } else if (num == 4) {
        return "O";
    } else if ((num == 5) || (num == 6)) {
        return "S";
    } else if ((num == 7) || (num == 8)) {
        return "Z";
    } else {
        return "T";
    }
}

//Returns a new pointer to a random level 4 or itself if level 4 is already random.
std::shared_ptr<Block> Level_4::generate() {
    
    std::shared_ptr<Block> current;
    std::string block;
    
    if ((blocksAdded/5 > 0) && (blocksAdded%5 == 1)) {
        blocksAdded = 1;
        return std::shared_ptr<Block>(new OneBlock);
    }
    
    if (isRand) {
        block = blockGenerate();
    } else {
        if (pos == size) {
            pos = 0;
        }
        block = nextBlock[pos];
        ++pos;
    }
    
    if (block == "I") {
        current = std::shared_ptr<Block>(new IBlock);
    } else if (block == "J") {
        current = std::shared_ptr<Block>(new JBlock);
    } else if (block == "L") {
        current = std::shared_ptr<Block>(new LBlock);
    } else if (block == "O") {
        current = std::shared_ptr<Block>(new OBlock);
    } else if (block == "Z") {
        current =  std::shared_ptr<Block>(new ZBlock);
    } else if (block == "S") {
        current = std::shared_ptr<Block>(new SBlock);
    } else {
        current = std::shared_ptr<Block>(new TBlock);
    }

    current->increaseHeavy();
    ++blocksAdded;
    return current;
}

// Tells level 4 at least one row has been
void Level_4::deleteRow() {
    blocksAdded = 1;
}

//Returns a new pointer to a random level 4 or itself if level 4 is already random.
std::shared_ptr<Level> Level_4::random() {
    if (isRand) {
        return NULL;
    } else {
        return std::shared_ptr<Level>(new Level_4{4, getSeed(), getLevel0File()});
    }
}

//Returns a pointer to a new Level 4 that generates files using the file provided.
std::shared_ptr<Level> Level_4::noRandom(std::string file) {
    return std::shared_ptr<Level>(new Level_4{4, getSeed(), getLevel0File(), file});
}

//Returns  a Null pointer since there is no level above level 4
std::shared_ptr<Level> Level_4::levelUp() {
    return NULL;
}

//Returns a pointer to Level 3
std::shared_ptr<Level> Level_4::levelDown() {
    return std::shared_ptr<Level>(new Level_3{3, getSeed(), getLevel0File()});
}
