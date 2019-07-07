#include "graphicsWindow.h"




// constructer
GraphicsWindow::GraphicsWindow(){
    std::vector<std::vector<char>> empty_grid =
{   {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
};
    xw = std::shared_ptr<Xwindow>{new Xwindow};
    p1 = empty_grid;
    p2 = empty_grid;
    
    block1 = '*';

    block2 = '*';

    level1 = -1;

    level2 = -1;

    score1 = -1;

    score2 = -1;

    high_Score = -1;

    nightmode_setting = false;
}

// destructer
GraphicsWindow::~GraphicsWindow(){
    
}

// endGame method gets a boolean to represent turn, and a boolean for nightmode, draws the necessary end game notification
void GraphicsWindow::endGame(bool turn, bool nightmode){
    int text_color;
    if(nightmode_setting){
        text_color = Xwindow::White;
    }else{
        text_color = Xwindow::Black;
    }
    if(!turn){
        xw->drawBigString(177, 20, "You Lost" , text_color);
        xw->drawBigString(112, 45, "Enter restart to restart, N to end" , text_color);
    }else{
        xw->drawBigString(577, 20, "You Lost" , text_color);
        xw->drawBigString(512, 45, "Enter restart to restart, N to end" , text_color);
    }
    


}

// specialActions method gets a boolean to represent turn, a boolean for nightmode, and the 
// number of eliminated rows as an integer draws the necessary special actions notification
void GraphicsWindow::specialActions(bool turn, bool nightmode, int elim_row){
    int text_color;
    if(nightmode_setting){
        text_color = Xwindow::White;
    }else{
        text_color = Xwindow::Black;
    }
    if(turn){
        xw->drawBigString(102, 20, "Congratulions you have cleared " + std::to_string(elim_row) + " rows" , text_color);
        xw->drawBigString(122, 45, "Choose to blind, heavy, or force" , text_color);
    }else{
        xw->drawBigString(502, 20, "Congratulions you have cleared " + std::to_string(elim_row) + " rows" , text_color);
        xw->drawBigString(522, 45, "Choose to blind, heavy, or force" , text_color);
    }


}

// drawNB method draws the nextblock
void GraphicsWindow::drawNB(std::shared_ptr<Block> p1, std::shared_ptr<Block> p2){
    int undraw_color;
    if(nightmode_setting){
        undraw_color = Xwindow::Black;
    }else{
        undraw_color = Xwindow::White;
    }

    char blockType1 = p1->getType();
    char blockType2 = p2->getType();


    int col = 4;
    int row = 4;
    int scale_col = 50/col;
    int scale_row = 50/row;
    int tile_dif = 1;


    if(!(blockType1 == block1)){
        
        // undraw
        xw->fillRectangle(349 + tile_dif, 5, 50 - 3, 50 - 3, undraw_color);
        
        int colour1;
        if (blockType1 == 'I'){ colour1 = Xwindow::Orange; }
        else if (blockType1 == 'J'){ colour1 = Xwindow::Blue; }
        else if (blockType1 == 'L'){ colour1 = Xwindow::Green; }
        else if (blockType1 == 'O'){ colour1 = Xwindow::Red; }
        else if (blockType1 == 'S'){ colour1 = Xwindow::Cyan; }
        else if (blockType1 == 'Z'){ colour1 = Xwindow::Yellow; }
        else if (blockType1 == 'T'){ colour1 = Xwindow::Magenta; }
        else if (blockType1 == '1'){ colour1 = Xwindow::Brown; }
        else { colour1 = undraw_color; }

        int pos_X = 0;
        int pos_Y = 0;
        for(int y = 3; y > -1; y--) {
            for(int x = 0; x < 4; x++) {
                bool fill = false;
                for(int k = 0; k < 4; k++) {
                    if(p1->getCells().at(k).first == x && p1->getCells().at(k).second == y){
                        pos_X = 0 + x;
                        pos_Y = 0 - y;
                        fill = true;
                    }
                }
                if(fill) {
                    xw->fillRectangle(pos_X*scale_col + 349 + tile_dif, pos_Y*scale_row + 30 + tile_dif, scale_col - tile_dif, scale_row - tile_dif, colour1);
                    
                } 
            }
            
        }
        block1 = blockType1;
    }
    

    if(!(blockType2 == block2)){

        // undraw
        xw->fillRectangle(749 + tile_dif, 5, 50 - 3, 50 - 3, undraw_color);

        int colour2;
        if (blockType2 == 'I'){ colour2 = Xwindow::Orange; }
        else if (blockType2 == 'J'){ colour2 = Xwindow::Blue; }
        else if (blockType2 == 'L'){ colour2 = Xwindow::Green; }
        else if (blockType2 == 'O'){ colour2 = Xwindow::Red; }
        else if (blockType2 == 'S'){ colour2 = Xwindow::Cyan; }
        else if (blockType2 == 'Z'){ colour2 = Xwindow::Yellow; }
        else if (blockType2 == 'T'){ colour2 = Xwindow::Magenta; }
        else if (blockType2 == '1'){ colour2 = Xwindow::Brown; }
        else { colour2 = undraw_color; }

        int pos_X = 0;
        int pos_Y = 0;
        for(int y = 3; y > -1; y--) {
            for(int x = 0; x < 4; x++) {
                bool fill = false;
                for(int k = 0; k < 4; k++) {
                    if(p2->getCells().at(k).first == x && p2->getCells().at(k).second == y){
                        pos_X = 0 + x;
                        pos_Y = 0 - y;
                        fill = true;
                    }
                }
                if(fill) {
                    xw->fillRectangle(pos_X*scale_col + 749 + tile_dif, pos_Y*scale_row + 30 + tile_dif, scale_col - tile_dif, scale_row - tile_dif, colour2);
                    
                } 
            }
            
        }
        block2 = blockType2;
    }
    

    
}

// drawText method draws the necessary text in the gameplay
void GraphicsWindow::drawText(int lvl_1, int lvl_2, int score_1, int score_2){
    int text_color;
    int undraw_color;
    if(nightmode_setting){
        text_color = Xwindow::White;
        undraw_color = Xwindow::Black;
    }else{
        text_color = Xwindow::Black;
        undraw_color = Xwindow::White;
    }
    
    if(lvl_1 != level1){
        xw->fillRectangle(7, 5, 100, 25,  undraw_color);
        xw->drawBigString(7, 20, "Level: " + std::to_string(lvl_1), text_color);
        level1 = lvl_1;
    }
    if(lvl_2 != level2){
        xw->fillRectangle(407, 5, 100, 25,  undraw_color);
        xw->drawBigString(407, 20, "Level: " + std::to_string(lvl_2), text_color);
        level2 = lvl_2;
    }
    if(score_1 != score1){
        xw->fillRectangle(7, 27, 100, 20,  undraw_color);
        xw->drawBigString(7, 45, "Score: " + std::to_string(score_1), text_color);
        score1 = score_1;
    }
    if(score_2 != score2){
        xw->fillRectangle(407, 27, 100, 20,  undraw_color);
        xw->drawBigString(407, 45, "Score: " + std::to_string(score_2), text_color);
        score2 = score_2;
    }
    
   
   
    
    
}

// drawHighScore method draws the highscore
void GraphicsWindow::drawHighScore(int highScore){
    int text_color;
    int undraw_color;
    if(nightmode_setting){
        text_color = Xwindow::White;
        undraw_color = Xwindow::Black;
    }else{
        text_color = Xwindow::Black;
        undraw_color = Xwindow::White;
    }
    if(highScore != high_Score){
        xw->fillRectangle(350, 910, 1000, 25,  undraw_color);
        xw->drawBigString(350, 920, "HIGH SCORE: " + std::to_string(highScore), text_color);
        high_Score = highScore;
    }
    
}

// drawTrun method draws red and green rectangles to indicate the whose turn
void GraphicsWindow::drawTurn(bool turn){
    int p1_turn;
    int p2_turn;
    if(turn){
        p1_turn = Xwindow::Green;
        p2_turn = Xwindow::Red;
    }else{
        p2_turn = Xwindow::Green;
        p1_turn = Xwindow::Red;
    }
    xw->fillRectangle(0, 800, 400, 100, p1_turn);
    xw->fillRectangle(400, 800, 400, 100, p2_turn);
    
}

// draw method gets two Board pointers p1 for player p2 for player, integer for highscore, 
// boolean for nightmode, and integer for eliminated rows. Then the method crosschecks fields 
// with given parameters, and to minimize the number of objects drawn by not drawing same values over again
void GraphicsWindow::draw(std::shared_ptr<Board> p1, std::shared_ptr<Board> p2, int highScore, bool turn, bool nightmode){
    std::vector<std::vector<char>> empty_grid_mode =
    {   {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
        {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
        {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
        {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
        {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
        {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
        {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
        {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
        {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
        {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
        {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
        {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
        {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
        {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
        {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
        {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
        {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
        {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
    };
   
    

    if(!nightmode_setting && nightmode){
        xw->fillRectangle(0, 0, 800, 930, Xwindow::Black);
        
        this->p1 = empty_grid_mode;
        
        this->p2 = empty_grid_mode;

        block1 = '*';

        block2 = '*';

        level1 = -1;

        level2 = -1;

        score1 = -1;

        score2 = -1;

        high_Score = -1; 

    }else if(nightmode_setting && !nightmode){
        xw->fillRectangle(0, 0, 800, 930, Xwindow::White); 

        this->p1 = empty_grid_mode;
        
        this->p2 = empty_grid_mode;

        block1 = '*';

        block2 = '*';

        level1 = -1;

        level2 = -1;

        score1 = -1;

        score2 = -1;

        high_Score = -1;
    }

    nightmode_setting = nightmode;
    //int col = 11;
    //int row = 18;
    int lvl_1 = p1->getlevel()->getLevel();
    int lvl_2 = p2->getlevel()->getLevel();
    int score_1 = p1->getScore();
    int score_2 = p2->getScore();
    drawText(lvl_1, lvl_2, score_1, score_2);
    drawNB(p1->getNextBlock(), p2->getNextBlock());
    drawTurn(turn);
    int border_color;
    int undraw_color;
    if(nightmode_setting){
        border_color = Xwindow::White;
        undraw_color = Xwindow::Black;
    }else{
        border_color = Xwindow::Black;
        undraw_color = Xwindow::White;
    }
    xw->fillRectangle(67, 0, 265, 50, undraw_color);
    xw->fillRectangle(467, 0, 265, 50, undraw_color);
    xw->fillRectangle(400, 0, 1, 800, border_color);// middle-vertical
    drawBoard1(p1);
    drawBoard2(p2);
    drawHighScore(highScore);
}

// drawBoard1 method draws the board of the player 1
void GraphicsWindow::drawBoard1(std::shared_ptr<Board> b){

    int undraw_color;
    int blind_color;
    if(nightmode_setting == false){
        undraw_color = Xwindow::White;
        blind_color = Xwindow::Black;
    }else{
        undraw_color = Xwindow::Black;
        blind_color = Xwindow::White;
    }

    std::vector<std::vector<char>> p =  b->getCharGrid();
    bool blind = b->getBlind();
    std::shared_ptr<Block> blck;
    blck = b->getCurrentBlock();

    int col = 11;
    int row = 18;
    int scale_col = 395/col;
    int scale_row = 745/row;
    int tile_dif = 2;
    
    std::vector<std::pair<int, int>> cells = blck->getCells();
    int x = b->getPos().first;
    int y = b->getPos().second;
    int THECELLSIZE1 = cells.size();
    for(int i = 0; i < THECELLSIZE1; i++) { //For each cell
        int cellX = x + cells[i].first;
        int cellY = y - cells[i].second;
        p.at(cellY).at(cellX) = blck->getType();
    }



    if(blind){
        for (int i = 0; i < row ; i++){
            for (int j = 0; j < col; ++j){
                if(3<= j && j <= 9 && 3 <= i && i <= 12){
                    p.at(i).at(j) = '?';
                }
            }
        }
    }



    for (int i = 0; i < row ; i++){
        for (int j = 0; j < col; ++j){
            char blockType = p.at(i).at(j);
            char oldBlockType = p1.at(i).at(j);
            if(oldBlockType != blockType){
                xw->fillRectangle(j*scale_col + tile_dif + 7, i*scale_row + 55 + tile_dif, scale_col - tile_dif, scale_row - tile_dif, undraw_color);
                if(!(blockType == ' ')){
                    int colour;
                    if (blockType == 'I'){ colour = Xwindow::Orange; }
                    else if (blockType == '?'){ colour = blind_color;}
                    else if (blockType == 'J'){ colour = Xwindow::Blue; }
                    else if (blockType == 'L'){ colour = Xwindow::Green; }
                    else if (blockType == 'O'){ colour = Xwindow::Red; }
                    else if (blockType == 'S'){ colour = Xwindow::Cyan; }
                    else if (blockType == 'Z'){ colour = Xwindow::Yellow; }
                    else if (blockType == 'T'){ colour = Xwindow::Magenta; }
                    else if (blockType == '1' || blockType == 'B'){ colour = Xwindow::Brown; }
                    else { colour = undraw_color; }
                    xw->fillRectangle(j*scale_col + tile_dif + 7, i*scale_row + 55 + tile_dif, scale_col - tile_dif, scale_row - tile_dif, colour);
                }
            }
            
        }
    }

    p1 = p;
}
            

// drawBoard2 method draws the board of the player 2
void GraphicsWindow::drawBoard2(std::shared_ptr<Board> b){

    int undraw_color;
    int blind_color;
    if(nightmode_setting == false){
        undraw_color = Xwindow::White;
        blind_color = Xwindow::Black;
    }else{
        undraw_color = Xwindow::Black;
        blind_color = Xwindow::White;
    }
   
    std::vector<std::vector<char>> p =  b->getCharGrid();
    bool blind = b->getBlind();
    std::shared_ptr<Block> blck;
    blck = b->getCurrentBlock();

    int col = 11;
    int row = 18;
    int scale_col = 395/col;
    int scale_row = 745/row;
    int tile_dif = 2;

    
    std::vector<std::pair<int, int>> cells = blck->getCells();
    int x = b->getPos().first;
    int y = b->getPos().second;
    int THECELLSIZE2 = cells.size();
    for(int i = 0; i < THECELLSIZE2;  i++) { //For each cell
        int cellX = x + cells[i].first;
        int cellY = y - cells[i].second;
        p.at(cellY).at(cellX) = blck->getType();
    }
    


    if(blind){
        for (int i = 0; i < row ; i++){
            for (int j = 0; j < col; ++j){
                if(3<= j && j <= 9 && 3 <= i && i <= 12){
                    p.at(i).at(j) = '?';
                }
            }
        }
    }



    for (int i = 0; i < row ; i++){
        for (int j = 0; j < col; ++j){
            char blockType = p.at(i).at(j);
            char oldBlockType = p2.at(i).at(j);
            if(oldBlockType != blockType){
                xw->fillRectangle(j*scale_col + 407 + tile_dif, i*scale_row + 55 + tile_dif, scale_col - tile_dif, scale_row - tile_dif, undraw_color);
                if(!(blockType == ' ')){
                    int colour;
                    if (blockType == 'I'){ colour = Xwindow::Orange; }
                    else if (blockType == '?'){ colour = blind_color;}
                    else if (blockType == 'J'){ colour = Xwindow::Blue; }
                    else if (blockType == 'L'){ colour = Xwindow::Green; }
                    else if (blockType == 'O'){ colour = Xwindow::Red; }
                    else if (blockType == 'S'){ colour = Xwindow::Cyan; }
                    else if (blockType == 'Z'){ colour = Xwindow::Yellow; }
                    else if (blockType == 'T'){ colour = Xwindow::Magenta; }
                    else if (blockType == '1' || blockType == 'B'){ colour = Xwindow::Brown; }
                    else { colour = undraw_color; }
                    xw->fillRectangle(j*scale_col + 407 + tile_dif, i*scale_row + 55 + tile_dif, scale_col - tile_dif, scale_row - tile_dif, colour);
                }
            }
            
        }
    }

    p2 = p;
        
}
