#include "oblock.h"

//constructor
OBlock::OBlock() {
    setType('O');
    update();
}

//updates cells based on direction
void OBlock::update() {
    //CELL 1
    setCell(0, 0, 0);
	//CELL 2
    setCell(1, 0, 1);
    //CELL 3
    setCell(2, 1, 0);
    //CELL 4
    setCell(3, 1, 1);
}
