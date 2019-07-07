#ifndef _LBLOCK_H
#define _LBLOCK_H

#include "block.h"

class LBlock: public Block {
		void update(); //updates cells based on direction
    public:
        LBlock(); //constructor
        
};

#endif
