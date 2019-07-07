#ifndef Board_h
#define Board_h
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include "cell.h"
#include "level.h"
#include "block.h"
#include "iblock.h"
#include "jblock.h"
#include "lblock.h"
#include "oblock.h"
#include "sblock.h"
#include "tblock.h"
#include "zblock.h"
#include "oneblock.h"
#include "bombblock.h"

class Board{
    const int HEIGHT = 18;
    const int WIDTH = 11;
    const int MIDDLE = 5;
    const int ID_MAX = 100;
    std::vector<std::vector<Cell>> grid; //STORED AS [y][x] 
    
    int score, seed;
    int x, y;
    int blockId;
    
    bool isBlind;
    std::string level0File;
    std::shared_ptr<Level> level;
    std::shared_ptr<Block> currenBlock;
    std::shared_ptr<Block> nextBlock;
    
    bool full(int row); //Returns true if a row is full
    std::vector<Cell> emptyRow(); //Creates an empty row 
    bool collision(); //Checks if the moving block is colliding the any others in the grid
    void imprint(); //Adds the currentblock to the fallen cells in the grid. Used to drop.
    bool hitTheTop(); //Returns true if the block hits illegal rows
    
public:
    
    //Constructor   
    Board(std::vector<std::vector<Cell>> input, int score, int level, bool isBlind, int seed, std::string level0File);
    
    //Destructor
    ~Board();
    
    //BLIND FUNCTIONS
    
    bool blind(); //Sets board to blind
    bool unblind();  //Sets board to NOT blind
    bool getBlind(); //Returns blind value
    bool lastCell(int id); //Checks if any grid tiles have Block id
    void clearRow(int row); //Clears a row

    void explode(); //Deletes columns adjacent to and in including column of the block
    
    int clearRows(); //Returns -1 if it hits the top
    
    //GRID FUNCTIONS
    
    void setCB(std::shared_ptr<Block> b); //Sets current block
    
    void setNB(std::shared_ptr<Block> b); //Sets next block
    
    //GET FUNCTIONS
    
    int getScore(); //Returns score value 
    std::shared_ptr<Level> getlevel(); //Returns level
    std::vector<std::vector<char>> getCharGrid(); //Returns grid as char vector
    std::vector<std::vector<Cell>> getGrid(); //Returns grid
    std::pair<int, int> getPos(); //Returns position
    std::shared_ptr<Block> getNextBlock(); //Returns next Block
    std::shared_ptr<Block> getCurrentBlock(); //Returns current Block
    
    //BLOCK MOVEMENT FUNCTIONS

    void increaseHeavy(int heavy); //Increases heavy value of block a given amount of times
    bool left(); //Tries to move the block left, returns true if successful
    bool right(); //Tries to move the block right, returns true if successful
    bool down(); //Tries to move the block down, returns true if successful
    int drop(); //Drops the current block. Returns -1 if game over, otherwise returns number of rows cleared. Updates score.
    bool clockwise(); //Turns current block clockwise
    bool cclockwise(); //Turns current block counterclockwise

    
    //LEVEL FUNCTIONS
    
    
    bool levelUp(); //Increases level
    bool levelDown(); //Decreases level
    bool random(); //Sets block spawning pattern to random
    bool noRandom(std::string s); //Sets block spawning pattern to follow a file 
    
    //TEST FUNCTIONS
    
    //Print function. For testing purposes only!
    void print();
};

#endif
