#include "block.h"

Block::Block() {
    direction = 0;
    heavy = 0;
    //CREATES CELLS
    for(int i = 0; i < 4; i++) {
        std::pair<int, int> p;
        p.first = 0;
        p.second = 0;
        cells.push_back(p);
    }
}

// sets the blocks heaviness externally
void Block::setHeavy(int heaviness){
    heavy = heaviness;
}

//Turns the block clockwise
void Block::clockwise() {
    direction++;
    if(direction == 4) direction = 0;
    update();
}

//Turns the lbock counterclockwise
void Block::cclockwise() {
    direction--;
    if(direction == -1) direction = 3;
    update();
}

//Increases the heavy value of the block, with the upper limit of 25
void Block::increaseHeavy() {
    if(heavy < 25) heavy++;
}

//Returns the cell values
std::vector<std::pair<int, int>> Block::getCells() {
    return cells;
}

//Returns the block type as a character
char Block::getType() {
    return type;
}

//Sets type of block
void Block::setType(char t) {
	type = t;
}

//Returns the heaviness of the block
int Block::getHeavy() {
    return heavy;
}

//Returns the direction
int Block::getDirection() {
	return direction;
}

//Sets a cell to a given value
void Block::setCell(int cell, int x, int y) {
	cells[cell].first = x;
	cells[cell].second = y;
}
