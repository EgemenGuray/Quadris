#ifndef _IBLOCK_H
#define _IBLOCK_H

#include "block.h"

class IBlock: public Block {
		void update(); //updates cells based on direction
    public:
        IBlock(); //constructor 
}; 

#endif
