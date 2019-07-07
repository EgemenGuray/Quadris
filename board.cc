#include "board.h"
#include <vector>
#include "level_0.h"
#include "level_1.h"
#include "level_2.h"
#include "level_3.h"
#include "level_4.h"


//Constructor
Board::Board(std::vector<std::vector<Cell>> input, int score, int level, bool isBlind, int seed, std::string level0file) : grid{input}, score{score}, seed{seed}, x{0}, y{3}, blockId{1}, isBlind{isBlind}, level0File{level0file} {
    x = 0;
    y = 3;
    blockId = 1;
    
    //to make level, need seed and default file for level-0
    if (level == 0) {
        this->level = std::shared_ptr<Level>(new Level_0(level, seed, level0File));
    } else if(level == 1) {
        this->level = std::shared_ptr<Level>(new Level_1(level, seed, level0File));
    } else if (level == 2) {
        this->level = std::shared_ptr<Level>(new Level_2(level, seed, level0File));
    } else if (level == 3) {
        this->level = std::shared_ptr<Level>(new Level_3(level, seed, level0File));
    } else {
        this->level = std::shared_ptr<Level>(new Level_4(level, seed, level0File));
    }
    
    currenBlock = this->level->levelGenerate();
    nextBlock = this->level->levelGenerate();
}

//Destructors
Board::~Board(){
    
}

// BLIND FUNCTIONS

//Sets board to blind
bool Board::blind(){
    if(isBlind) return false;
    isBlind = true;
    return true;
}

//Sets board to NOT blind
bool Board::unblind(){
    if(!isBlind) return false;
    isBlind = false;
    return true;
}

//Returns blind value
bool Board::getBlind(){
    return isBlind;
}

//BLOCK SET FUNCTIONS

//Sets current block
void Board::setCB(std::shared_ptr<Block> b){
    currenBlock = b;
}

//Sets next block
void Board::setNB(std::shared_ptr<Block> b){
    nextBlock = b;
}

//GET FUNCTIONS

//Returns grid as char vector
std::vector<std::vector<char>> Board::getCharGrid(){
    int col = WIDTH;
    int row = HEIGHT;
    std::vector <std::vector<char>> retval;
    for (int i = 0; i < row ; i++){
        std::vector<char> retval_row;
        for (int j = 0; j < col; ++j){
            retval_row.emplace_back(grid.at(i).at(j).type);
        }
        retval.emplace_back(retval_row);
    }
    return retval;
}

//Returns grid
std::vector<std::vector<Cell>> Board::getGrid(){
    return grid;
}

//Returns position
std::pair<int, int> Board::getPos() {
    std::pair<int, int> pos;
    pos.first = x;
    pos.second = y;
    return pos;
}

//Returns next Block
std::shared_ptr<Block> Board::getNextBlock(){
    return nextBlock;
}

//Returns current Block
std::shared_ptr<Block> Board::getCurrentBlock(){
    return currenBlock;
}

//Returns score value
int Board::getScore(){
    return score;
}

//Returns level
std::shared_ptr<Level> Board::getlevel(){
    return level;
}

//GRID CLEAR

//Returns true if a row is full
bool Board::full(int row) {
    for(int i = 0; i < WIDTH; i++) {
        if(grid[row][i].type == ' ') return false;
    }
    return true;
}

//Creates an empty row 
std::vector<Cell> Board::emptyRow() {
    std::vector<Cell> c;
    for(int i = 0; i < WIDTH; i++) c.push_back(Cell{' ', 0, 0});
    return c;
}

//Returns true if no cell carries a given Block id
bool Board::lastCell(int id) {
    for(int i = 0; i < HEIGHT; i++) {
        for(int j = 0; j < WIDTH; j++) {
            if(grid[i][j].blockId == id) return false;
        }
    }
    return true;
}

//Clears a given row, adding to the score
void Board::clearRow(int row) {
    for(int i = 0; i < WIDTH; i++) {
        Cell c = grid[row][i];
        grid[row][i] = Cell{'1', 0, 0};
        if(lastCell(c.blockId)) score += ((c.level + 1) * (c.level + 1));
    }
    grid.erase(grid.begin() + row);
    grid.insert(grid.begin(), emptyRow());
}

//Clears full rows, adding empty rows on top. Returns the number of rows cleared. 
int Board::clearRows() {
    int numClear = 0;
    for(int i = 0; i < HEIGHT; i++) {
        if(full(i)) {
            clearRow(i);
            numClear++;
        }
    }
    return numClear;
}

//Deletes columns adjacent to and in including column of the block
void Board::explode() {
    for(int i = x-1; i <= x + 1; i++){
        for(int j = y-1; j <= y + 1; j++){
            if(0 <= i && i < WIDTH && 0 <= j && j < HEIGHT){
                if(grid[j][i].type != ' ') {
                    Cell c = grid[j][i];
                    grid[j][i] = Cell{' ', 0, 0};
                    if(lastCell(c.blockId)) score += c.level;
                }
            }
        
        }
    }
    
}

//BLOCK MOVEMENT FUNCTIONS

//Checks if the moving block is colliding the any others in the grid
bool Board::collision() {
    std::vector<std::pair<int, int>>  cells = currenBlock.get()->getCells();
    int theCellsSize = cells.size();
    for(int i = 0; i < theCellsSize; i++) { //For each cell
        int cellX = x + cells[i].first;
        int cellY = y - cells[i].second;
        if(cellX < 0 || cellY < 0 || cellX >= WIDTH || cellY >= HEIGHT) return true; //Out of bounds
        if(grid[cellY][cellX].type != ' ') return true; //Cell filled
    }
    return false;
}

//Tries to move the block left, returns true if successful
bool Board::left() {
    x--;
    if(collision()) { 
        x++;
        return false;
    }
    return true;
}

//Tries to move the block right, returns true if successful
bool Board::right() {
    x++;
    if(collision()) {
        x--;
        return false;
    }
    return true;
}

//Tries to move the block down, returns true if successful
bool Board::down() {
    y++;
    if(collision()) {
        y--;
        return false;
    }
    return true;
}

//Drops the current block. Returns -1 if game over, otherwise returns number of rows cleared. Updates score.
int Board::drop() {
    while(down()) {} //Moves block as far down as possible
    
    if(collision()) return -1; // THE BLOCK HAS NO SPACE
    
    imprint();
    if(currenBlock->getType() == 'B') explode();
    
    if(hitTheTop()) return -1; // THE BLOCK HITS THE TOP THREE ROWS
    
    int cleared = clearRows();
    if(cleared > 0) level->levelDeleteRow();
    
    blockId = (blockId % ID_MAX) + 1;
    
    std::shared_ptr<Block> temp = level->levelGenerate();
    if (temp->getType() == '1') {
        currenBlock = temp;
        x = MIDDLE;
        y = 3;
        drop();
    } else {
        currenBlock = nextBlock;
        nextBlock = temp;
    }   
    x = 0;
    y = 3;
    if(cleared > 0) score += (level->getLevel() + cleared) * (level->getLevel() + cleared);
    
    unblind();
    
    if(collision()) return -1; // THE NEW BLOCK HAS NO SPACE
    
    return cleared;
}

//Turns current block clockwise
bool Board::clockwise() {
    currenBlock.get()->clockwise();
    if(collision()) {
        currenBlock.get()->cclockwise();
        return false;
    }
    return true;
}

//Turns current block counterclockwise
bool Board::cclockwise() {
    currenBlock.get()->cclockwise();
    if(collision()) {
        currenBlock.get()->clockwise();
        return false;
    }
    return true;
}

//Adds the currentblock to the fallen cells in the grid. Used to drop.
void Board::imprint() { //CHANGE WHEN LEVEL UPDATES
    std::vector<std::pair<int, int>> cells = currenBlock->getCells();
    int theCellSize = cells.size();
    for(int i = 0; i < theCellSize; i++) { //For each cell
        int cellX = x + cells[i].first;
        int cellY = y - cells[i].second;
        grid[cellY][cellX].type = currenBlock->getType();
        grid[cellY][cellX].level = level->getLevel();
        grid[cellY][cellX].blockId = blockId;
    }
}

//Increases heavy value of block a given amount of times
void Board::increaseHeavy(int heavy) {
    for(int i = 0; i < heavy; i++) currenBlock->increaseHeavy();
}

//BOARD FUNCTIONS

//Returns true if the block hits illegal rows
bool Board::hitTheTop() {
    for(int y = 0; y < 3; y++) {
        for(int x = 0; x < WIDTH; x++) {
            if(grid[y][x].type != ' ') return true;
        }
    }
    return false;
}



//LEVEL FUNCTIONS

//Increases level
bool Board::levelUp() {
    std::shared_ptr<Level> curr = level->doLevelUp();
    if (curr == NULL) {
        return false;
    }
    level = curr;
    return true;
}

//Decreases level
bool Board::levelDown() {
    std::shared_ptr<Level> curr = level->doLevelDown();
    if (curr == NULL) {
        return false;
    }
    level = curr;
    return true;
}

//Sets block spawning pattern to random
bool Board::random() {
    std::shared_ptr<Level> curr;
    curr = level->levelRandom(); //if random, level remains level, if not, new random level made.
    if (curr == NULL) {
        return false;
    }
    level = curr;
    return true;
}

//Sets block spawning pattern to follow a file 
bool Board::noRandom(std::string blockFileName) {
    std::shared_ptr<Level> curr;
    curr = level->levelNoRandom(blockFileName);//return level.noRandom(s);
    if (curr == NULL) {
        return false;
    }
    level = curr;
    return true;
}

//TEST FUNCTIONS

//Print function. For testing purposes only!
void Board::print() {
    int theGridSize = grid.size();
    for(int i = 0; i < theGridSize; i++) {
        for(int j = 0; j < WIDTH; j++) std::cout<<grid[i][j].type;
        std::cout<<std::endl;
    }
}
