#include "bombblock.h"

//constructor
BombBlock::BombBlock() {
    setType('B');
    update();
}

//updates cells based on direction
void BombBlock::update() {
    setCell(0, 0, 0);
}
