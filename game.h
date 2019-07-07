#ifndef _GAME_H
#define _GAME_H

#include <vector>
#include "board.h"
#include "textWindow.h"
#include "graphicsWindow.h"


class Game{
    
    std::shared_ptr<Board> p1;
    std::shared_ptr<Board> p2;
    bool player_turn;
    bool gameEnded;
    int highScore;
    std::shared_ptr<TextWindow> TW;
    std::shared_ptr<GraphicsWindow> GW;
    bool onlyText;
    bool nightMode;
    int seed;
    std::string file1;
    std::string file2;
    bool active_speical_actions;
    bool noSpecial;


    std::vector <std::vector<Cell>> createCellVec(std::vector <std::vector<char>> cv, int col = 11, int row = 18, int blockId = 0, int level = 0);
    void setPlayerTurn();
    void updateHighScore();

    //// update observers
    void updateGraphics(int eliminated_rows = 0);
    void updateText(int eliminated_rows = 0);
    //// update observers
    
public:

    Game(bool onlyText, int level, int seed, std::string file1, std::string file2, bool noSpecial);
    ~Game();


    /// Extra fature
    void changeGraphicsMode(bool night);
    
    void restart();
    
    //// Testing functions
    void testForce(std::shared_ptr<Block> b);
    void setBoards(std::shared_ptr<Board> p1, std::shared_ptr<Board> p2);
    //// Testing functions

    //// Block operations
    void left(int n);
    void right(int n);
    void drop(int n);
    void down(int n);
    void clockwise(int n);
    void cclockwise(int n);
    //// Block operations

    //// Game rule operations
    void levelUp(int n);
    void levelDown(int n);
    void random();
    void noRandom(std::string file);
    //// Game rule operations

    /// Speical actions
    void force(std::shared_ptr<Block> b);
    void blind();
    void heavy(int weight);
    /// Speical actions

    /// Visitor calls
    int getHighScore();
    
};



#endif
