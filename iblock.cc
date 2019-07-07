#include "iblock.h"

//constructor
IBlock::IBlock() { 
    setType('I');
    update();
}

//updates cells based on direction
void IBlock::update() {
    if(getDirection() == 0) {
        
        //CELL 1
        setCell(0, 0, 0);
        //CELL 2
        setCell(1, 1, 0);
        //CELL 3
        setCell(2, 2, 0);
        //CELL 4
        setCell(3, 3, 0);
        
    } else if (getDirection() == 1) {
        
        //CELL 1
        setCell(0, 0, 0);
        //CELL 2
        setCell(1, 0, 1);
        //CELL 3
        setCell(2, 0, 2);
        //CELL 4
        setCell(3, 0, 3);
        
    } else if (getDirection() == 2) {
        
        //CELL 1
        setCell(0, 0, 0);
        //CELL 2
        setCell(1, 1, 0);
        //CELL 3
        setCell(2, 2, 0);
        //CELL 4
        setCell(3, 3, 0);
        
    } else if (getDirection() == 3) {
        
        //CELL 1
        setCell(0, 0, 0);
        //CELL 2
        setCell(1, 0, 1);
        //CELL 3
        setCell(2, 0, 2);
        //CELL 4
        setCell(3, 0, 3);
        
    }
}
