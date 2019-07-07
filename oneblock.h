#ifndef _ONEBLOCK_H
#define _ONEBLOCK_H

#include "block.h"

class OneBlock: public Block {
		void update(); //updates cells based on direction
    public:
        OneBlock(); //constructor
        
};

#endif
