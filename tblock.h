#ifndef _TBLOCK_H
#define _TBLOCK_H

#include "block.h"

class TBlock: public Block {
		void update(); //updates cells based on direction
    public:
        TBlock(); //constructor
        
}; 

#endif
