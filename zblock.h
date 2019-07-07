#ifndef _ZBLOCK_H
#define _ZBLOCK_H

#include "block.h"

class ZBlock: public Block {
		void update(); //updates cells based on direction
    public:
        ZBlock(); //constructor
        
};

#endif
