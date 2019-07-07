#ifndef _SBLOCK_H
#define _SBLOCK_H

#include "block.h"

class SBlock: public Block {
		void update(); //updates cells based on direction
    public:
        SBlock(); //constructor
        
};

#endif
