#include "sblock.h"

//constructor
SBlock::SBlock() {
    setType('S');
    update();
}

//updates cells based on direction
void SBlock::update() {
    if(getDirection() == 0) {
        
        //CELL 1
        setCell(0, 0, 0);
        //CELL 2
        setCell(1, 1, 0);
        //CELL 3
        setCell(2, 1, 1);
        //CELL 4
        setCell(3, 2, 1);
        
    } else if (getDirection() == 1) {
        
        //CELL 1
        setCell(0, 1, 0);
        //CELL 2
        setCell(1, 1, 1);
        //CELL 3
        setCell(2, 0, 1);
        //CELL 4
        setCell(3, 0, 2);
        
    } else if (getDirection() == 2) {
        
        //CELL 1
        setCell(0, 0, 0);
        //CELL 2
        setCell(1, 1, 0);
        //CELL 3
        setCell(2, 1, 1);
        //CELL 4
        setCell(3, 2, 1);
        
    } else if (getDirection() == 3) {
        
        //CELL 1
        setCell(0, 1, 0);
        //CELL 2
        setCell(1, 1, 1);
        //CELL 3
        setCell(2, 0, 1);
        //CELL 4
        setCell(3, 0, 2);
        
    }
}
