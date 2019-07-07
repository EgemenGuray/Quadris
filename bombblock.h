#ifndef _BOMBBLOCK_H
#define _BOMBBLOCK_H

#include "block.h"

class BombBlock: public Block {
		void update(); //updates cells based on direction
    public:
        BombBlock(); //constructor
        
};

#endif
