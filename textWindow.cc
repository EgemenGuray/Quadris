#include "textWindow.h"

// counts the number of digits in integer
int how_many(int x){
    if(x <= 9){
        return 1;
    }else{
        return 1 + how_many(x/10);
    }
}

// draw method gets two Board pointers p1 for player p2 for player, 
// highscore as integer, turn as boolean, and number of eliminated 
// rows as integer Then the method prints the game by extracting the grid, 
// currentBlock, nextBlock, score, and level fields of the both boards and prints 
// them to the command line along with the highscore. According to the turn and eliminated 
// rows method prints useful notifications for the user
void TextWindow::draw(std::shared_ptr<Board> p1, std::shared_ptr<Board> p2, int highScore, bool turn, int eliminatedRows){

    int col = 11;
    int row = 18;

    int diff = 10;

    int lvl_1 = p1->getlevel()->getLevel();
    int lvl_2 = p2->getlevel()->getLevel();

    int score_1 = p1->getScore();
    int score_2 = p2->getScore();

    bool blind_1 = p1->getBlind();
    bool blind_2 = p2->getBlind();

    std::vector<std::vector<char>> pb1 = p1->getCharGrid();
    std::vector<std::vector<char>> pb2 = p2->getCharGrid();


    std::shared_ptr<Block> cur_blck_1 = p1->getCurrentBlock();

    std::shared_ptr<Block> cur_blck_2 = p2->getCurrentBlock();


    //////// IMPRINT BLINDNESS AND CURRENTBLOCK TO PLAYER1S BOARD////////

    std::vector<std::pair<int, int>> cells = cur_blck_1->getCells();
    int x = p1->getPos().first;
    int y = p1->getPos().second;
    int THECELLSSIZE = cells.size();
    for(int i = 0; i < THECELLSSIZE; i++) { //For each cell
        int cellX = x + cells[i].first;
        int cellY = y - cells[i].second;
        pb1.at(cellY).at(cellX) = cur_blck_1->getType();
    }



    if(blind_1){
        for (int i = 0; i < row ; i++){
            for (int j = 0; j < col; ++j){
                if(3<= j && j <= 9 && 3 <= i && i <= 12){
                    pb1.at(i).at(j) = '?';
                }
            }
        }
    }

    //////// IMPRINT BLINDNESS AND CURRENTBLOCK TO PLAYER1S BOARD////////


    //////// IMPRINT BLINDNESS AND CURRENTBLOCK TO PLAYER2S BOARD////////

    cells = cur_blck_2->getCells();
    x = p2->getPos().first;
    y = p2->getPos().second;
    int THECELLSIZE = cells.size();
    for(int i = 0; i < THECELLSIZE; i++) { //For each cell
        int cellX = x + cells[i].first;
        int cellY = y - cells[i].second;
        pb2.at(cellY).at(cellX) = cur_blck_2->getType();
    }
    


    if(blind_2){
        for (int i = 0; i < row ; i++){
            for (int j = 0; j < col; ++j){
                if(3<= j && j <= 9 && 3 <= i && i <= 12){
                    pb2.at(i).at(j) = '?';
                }
            }
        }
    }

    //////// IMPRINT BLINDNESS AND CURRENTBLOCK TO PLAYER2S BOARD////////
    
    //////////// PRINT HIGHSCORE ////////////////////////
    int align_high = (2*col + diff - 13) / 2;
    for(int i = 0; i < align_high ; i++){
        std::cout << " ";
    }
    std::cout << "High Score: ";
    
    std::cout << highScore << std::endl;
    //////////// PRINT HIGHSCORE ////////////////////////
    ///////////// PRINT LEVELLL //////////////////////////
    std::cout << "Level:";
    for(int i = 0; i < 5 - how_many(lvl_1); i++){
        std::cout << " ";
    }
    std::cout << lvl_1;
    for (int i = diff - 3; i >= 0; --i){
        std::cout << " ";
    }
    std::cout << "Level:";
    for(int i = 0; i < 5 - how_many(lvl_2); i++){
        std::cout << " ";
    }
    std::cout << lvl_2 << std::endl;
    ///////////// PRINT LEVELLL //////////////////////////
    
    ///////////// PRINT SCORE //////////////////////////
    std::cout << "Score:";
    for(int i = 0; i < 5 - how_many(score_1); i++){
        std::cout << " ";
    }
    std::cout << score_1;
    for (int i = diff - 3; i >= 0; --i){//
        std::cout << " ";
    }
    std::cout << "Score:";
    for(int i = 0; i < 5 - how_many(score_2); i++){
        std::cout << " ";
    }
    std::cout << score_2 << std::endl;
    ///////////// PRINT SCORE //////////////////////////
    
    //cout << "High Score" << 23 << endl;
    
    
    ///////////// PRINT DASH //////////////////////////
    for (int i = col - 1; i >= 0; --i){
        std::cout << "-";
    }
    for (int i = diff - 3; i >= 0; --i){//
        std::cout << " ";
    }
    for (int i = col - 1; i >= 0; --i){
        std::cout << "-";
    }
    std::cout << std::endl;
    ///////////// PRINT DASH //////////////////////////
    
    ///////////// PRINT BOARDS //////////////////////////
    
    ///////////// PRINT BOARD1 //////////////////////////
    for (int i = 0; i < row ; i++){
        for (int j = 0; j < col; ++j){
            
            std::cout << pb1.at(i).at(j);
            
        }
        ///////////// PRINT BOARD1 //////////////////////////
        
        ///////////// PRINT DIFFERENCE //////////////////////////
        for (int i = diff - 3; i >= 0; --i){//
            std::cout << " ";
        }
        ///////////// PRINT DIFFERENCE //////////////////////////
        
        ///////////// PRINT BOARD2 //////////////////////////
        
        for (int j = 0; j < col; ++j){
            
             std::cout << pb2.at(i).at(j);
            
            
        }
        std::cout << std::endl;
    }
    ///////////// PRINT BOARD2 //////////////////////////
    ///////////// PRINT BOARDS //////////////////////////
    
    ///////////// PRINT DASH //////////////////////////
    for (int i = col - 1; i >= 0; --i){
        std::cout << "-";
    }
    for (int i = diff - 3; i >= 0; --i){//
        std::cout << " ";
    }
    for (int i = col - 1; i >= 0; --i){
        std::cout << "-";
    }
    ///////////// PRINT DASH //////////////////////////
    
    std::cout << std::endl << "Next Block:";
    for (int i = diff - 3; i >= 0; --i){//
        std::cout << " ";
    }
    std::cout << "Next Block:" << std::endl;
    
    for(int y = 3; y > -1; y--) {
        for(int x = 0; x < 4; x++) {
            bool fill = false;
            for(int k = 0; k < 4; k++) {
                if(p1->getNextBlock()->getCells().at(k).first == x && p1->getNextBlock()->getCells().at(k).second == y) fill = true;
            }
            if(fill) {
                std::cout << p1->getNextBlock()->getType();
            } else {
                std::cout << ' ';
            }
        }
        for (int i = diff + 4; i >= 0; --i){//
            std::cout << " ";
        }
        
        for(int x = 0; x < 4; x++) {
            bool fill = false;
            for(int k = 0; k < 4; k++) {
                if(p2->getNextBlock()->getCells().at(k).first == x && p2->getNextBlock()->getCells().at(k).second == y) fill = true;
            }
            if(fill) {
                std::cout << p2->getNextBlock()->getType();
            } else {
                std::cout << ' ';
            }
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
    if(turn){
        if(eliminatedRows == -1){
            std::cout << "Game Ended, player 2 lost" << std::endl;
            std::cout << "Player 1 score: " << p1->getScore() << std::endl;
            std::cout << "Player 2 score: "  << p2->getScore() << std::endl;
            std::cout << "High score: " << highScore << std::endl;
            std::cout << "Do you want to play again?" << std::endl;
            std::cout << "Enter restart to restart" << std::endl;
            std::cout << "N to end" << std::endl;
        }else if(eliminatedRows >= 2){
            std::cout << "Congratulions you have cleared " << eliminatedRows << " rows." << std::endl;
            std::cout << "Type your selection to blind, heavy, or force: " << std::endl;
        }else{
            std::cout << "Player 1, enter command:" << std::endl;
        }

    }else{
        if(eliminatedRows == -1){
            std::cout << "Game Ended, player 1 lost" << std::endl;
            std::cout << "Player 1 score: " << p1->getScore() << std::endl;
            std::cout << "Player 2 score: "  << p2->getScore() << std::endl;
            std::cout << "High score: " << highScore << std::endl;
            std::cout << "Do you want to play again?" << std::endl;
            std::cout << "Enter restart to restart" << std::endl;
            std::cout << "N to end" << std::endl;
        }else if(eliminatedRows >= 2){
            std::cout << "Congratulions you have dropped " << eliminatedRows << " rows." << std::endl;
            std::cout << "Type your selection to blind, heavy, or force: " << std::endl;
        }else{
            std::cout << "Player 2, enter command:" << std::endl;
        }
        
    }
    
}
