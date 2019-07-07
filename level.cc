#include "level.h"

// Level Constructor
Level::Level(int level, int seed, std::string file): level{level}, seed{seed}, level0File{file} {}

//Level Destructor
Level::~Level() {}

//Returns the Ineger value of the current level
int Level::getLevel() {
    return level;
}

//Returns an integer value of the seed to be used in generatng random Blocks
int Level::getSeed() {
    return seed;
}

//Returns name of the file which includes order of Blocks to be generated in level 0
std::string Level::getLevel0File() {
    return level0File;
}

//Returns ptr to the next Block
std::shared_ptr<Block> Level::levelGenerate() {
    return generate();
}

//Tells level at least one row has been removed
void Level::levelDeleteRow() {
    deleteRow();
}

// Only relevant in Level 3 and 4; Level generates Blocks randomly
std::shared_ptr<Level> Level::levelRandom() {
    return random();
}

//Only relevant in Level 3 and 4, sets level to generate upcoming blocks using file provided.
std::shared_ptr<Level> Level::levelNoRandom(std::string file) {
    return noRandom(file);
}

// Increases the level if possible, and returns pointer to new Level
std::shared_ptr<Level> Level::doLevelUp() {
    return levelUp();
}

// Decreases the level if possible, and returns pointer to new Level
std::shared_ptr<Level> Level::doLevelDown() {
    return levelDown();
}
