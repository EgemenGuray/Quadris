#ifndef _GRAPHICSWINDOW_H
#define _GRAPHICSWINDOW_H

#include <vector>
#include "board.h"
#include "window.h"

class GraphicsWindow{

    bool nightmode_setting;
    
    std::shared_ptr<Xwindow> xw;

    std::vector<std::vector<char>> p1;

    std::vector<std::vector<char>> p2;

    char block1;

    char block2;

    int level1;

    int level2;

    int score1;

    int score2;

    int high_Score;

    void drawNB(std::shared_ptr<Block> p1, std::shared_ptr<Block> p2);
    
    void drawText(int lvl_1, int lvl_2, int score_1, int score_2);

    void drawBoard1(std::shared_ptr<Board> b);
    void drawBoard2(std::shared_ptr<Board> b);

    void drawTurn(bool turn);

    void drawHighScore(int highScore);
    

    
public:
    GraphicsWindow();  
    ~GraphicsWindow();
    
    void endGame(bool turn = true, bool nightmode = true);

    void specialActions(bool turn = true, bool nightmode = true, int elim_row = 0);

    void draw(std::shared_ptr<Board> p1, std::shared_ptr<Board> p2, int highScore = 0, bool turn = true, bool nightmode = true);

};



#endif
