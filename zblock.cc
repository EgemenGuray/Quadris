#include "zblock.h"

//constructor
ZBlock::ZBlock() {
    setType('Z');
    update();
}

//updates cells based on direction
void ZBlock::update() { 
    if(getDirection() == 0) {
        
        //CELL 1
        setCell(0, 0, 1);
        //CELL 2
        setCell(1, 1, 1);
        //CELL 3
        setCell(2, 1, 0);
        //CELL 4
        setCell(3, 2, 0);
        
    } else if (getDirection() == 1) {
        
        //CELL 1
        setCell(0, 1, 2);
        //CELL 2
        setCell(1, 0, 1);
        //CELL 3
        setCell(2, 1, 1);
        //CELL 4
        setCell(3, 0, 0);
        
    } else if (getDirection() == 2) {
        
        //CELL 1
        setCell(0, 0, 1);
        //CELL 2
        setCell(1, 1, 1);
        //CELL 3
        setCell(2, 1, 0);
        //CELL 4
        setCell(3, 2, 0);
        
    } else if (getDirection() == 3) {
        
        //CELL 1
        setCell(0, 1, 2);
        //CELL 2
        setCell(1, 0, 1);
        //CELL 3
        setCell(2, 1, 1);
        //CELL 4
        setCell(3, 0, 0);
        
    }
}
