#ifndef _TEXTWINDOW_H
#define _TEXTWINDOW_H

#include <vector>
#include "board.h"

class TextWindow{
    

public:
	// draw method gets two Board pointers p1 for player p2 for player, 
	// highscore as integer, turn as boolean, and number of eliminated 
	// rows as integer Then the method prints the game by extracting the grid, 
	// currentBlock, nextBlock, score, and level fields of the both boards and prints 
	// them to the command line along with the highscore. According to the turn and eliminated 
	// rows method prints useful notifications for the user
    void draw(std::shared_ptr<Board> p1, std::shared_ptr<Board> p2,  int highScore, bool turn, int eliminatedRows);
};

// counts the number of digits in intege
int how_many(int x);

#endif
