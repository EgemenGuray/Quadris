#ifndef _CELL_H_
#define _CELL_H_

struct Cell {
	char type; //Type of block
	int level; //Level it was created in, for scoring
	int blockId; //unique id of dropped block 
};

#endif
