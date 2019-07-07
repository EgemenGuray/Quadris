#ifndef _OBLOCK_H
#define _OBLOCK_H

#include "block.h"

class OBlock: public Block {
		void update(); //updates cells based on direction
    public:
        OBlock(); //constructor
        
};

#endif
