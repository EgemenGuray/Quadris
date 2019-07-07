#include "level_3.h"
#include "level_2.h"
#include "level_4.h"


//Constructor
Level_3::Level_3(int lev, int seed, std::string level0File): Level{lev, seed, level0File}, isRand{true} {
    std::srand(seed);
}

//Alternate Constructor for a non-random level 3.
Level_3::Level_3(int lev, int seed, std::string level0File, std::string file): Level{lev, seed, level0File}, isRand{false}, file{file}, pos{0} {
    std::ifstream fin {file};
    std::string block;
    while (fin>>block) {
        nextBlock.emplace_back(block);
    }
    size = nextBlock.size();
}

//Destructor
Level_3::~Level_3() {}

//Generates the nect block using required probabilities
std::string Level_3::blockGenerate() {
    //Number 9 used since Z and S have double chance of being generated
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

//Retruns a pointer to the next block
std::shared_ptr<Block> Level_3::generate() {
    std::shared_ptr<Block> current;
    std::string block;
    
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
    return current;
}

//Tells level at least one row has been deleted. Relevant in Level 4 only.
void Level_3::deleteRow() {}

//Returns a new pointer to a random level 3 or itself if level 3 is already random.
std::shared_ptr<Level> Level_3::random() {
    if (isRand) {
        return NULL;
    } else {
        return std::shared_ptr<Level>(new Level_3{3, getSeed(), getLevel0File()});
    }
}

//Returns a pointer to a new Level 3 that generates files using the file provided.
std::shared_ptr<Level> Level_3::noRandom(std::string file) {
    return std::shared_ptr<Level>(new Level_3{3, getSeed(), getLevel0File(), file});
}

//Returns a pointer to Level 4
std::shared_ptr<Level> Level_3::levelUp() {
    return std::shared_ptr<Level>(new Level_4{4, getSeed(), getLevel0File()});
}

//Returns a pointer to Level 2
std::shared_ptr<Level> Level_3::levelDown() {
    return std::shared_ptr<Level>(new Level_2{2, getSeed(), getLevel0File()});
}
