#ifndef _BLOCK_H
#define _BLOCK_H

#include <vector>

class Block {
    private:
        std::vector<std::pair<int, int>> cells; //The positions of the block cells
       											//relative to the block's position
        int heavy; //How heavy the block is 
        int direction; //Stores the direction of the block based on number of 
					   //clockwise turns
        char type; //The idenitifying type of the block, stored as a character
		virtual void update()=0; //Updates the cells based on direction of block
		
	protected:
		void setCell(int cell, int x, int y); //Sets a cell to a given value
		void setType(char t); //Sets type to value

    public:
        Block();
        void clockwise(); //Turns the block clockwise
        void cclockwise(); //Turns the lbock counterclockwise
        int getDirection(); //Returns the direction
        void increaseHeavy(); //Increases the heavy value of the block, with the 
							  //upper limit of 25
        void setHeavy(int heaviness);
        std::vector<std::pair<int, int>> getCells(); //Returns the cell values
        char getType(); //Returns the block type as a character
        int getHeavy(); //Returns the heaviness of the block
};

#endif
