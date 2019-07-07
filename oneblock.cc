#include "oneblock.h"

//constructor
OneBlock::OneBlock() {
    setType('1');
    update();
}

//updates cells based on direction
void OneBlock::update() {
    setCell(0, 0, 0);
}
