#ifndef _JBLOCK_H
#define _JBLOCK_H

#include "block.h"

class JBlock: public Block {
		void update(); //updates cells based on direction
    public:
        JBlock(); //constructor
        
}; 

#endif
