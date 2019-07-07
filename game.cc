#include "game.h"



// createCellVec method get 2d char vector number of cols and rows, blockId, and level number returns a 2d cell vector according to the given input
std::vector <std::vector<Cell>> Game::createCellVec(std::vector <std::vector<char>> cv, int col, int row, int blockId, int level){
    std::vector<std::vector<Cell>> retval;
    for (int i = 0; i < row ; i++){
        std::vector<Cell> retval_row;
        for (int j = 0; j < col; ++j){
            Cell c;
            c.type = cv.at(i).at(j);
            c.blockId = blockId;
            c.level = level;
            
            retval_row.emplace_back(c);
            
        }
        retval.emplace_back(retval_row);
    }
    return retval;
}

// constructer
Game::Game(bool onlyText, int level, int seed, std::string file1, std::string file2, bool noSpecial): onlyText{onlyText}, seed{seed}, file1{file1}, file2{file2}, noSpecial{noSpecial} {
    std::vector<std::vector<char>> empty =
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
    
    p1 = std::shared_ptr<Board>{new Board{createCellVec(empty),0,level,false,seed,this->file1}};
    p2 = std::shared_ptr<Board>{new Board{createCellVec(empty),0,level,false,seed,this->file2}};
    
    gameEnded = false;
    active_speical_actions = false;
    nightMode = true;
    player_turn = true;
    highScore = 0; 
    TW = std::shared_ptr<TextWindow>{new TextWindow};
    if(!onlyText){
        GW = std::shared_ptr<GraphicsWindow>{new GraphicsWindow};
        updateGraphics();
    }else{
       GW = nullptr; 
    }
    
    updateText();
}

// destructer
Game::~Game(){}

// changeGraphicsMode changes the mode of the GraphicsWindow according 
// to the given boolean value TRUE = nightmode FALSE = lightmode
void Game::changeGraphicsMode(bool night){
    nightMode = night;
    updateGraphics();
}

// setBoard method sets the boards externally by getting two boards 
void Game::setBoards(std::shared_ptr<Board> p1, std::shared_ptr<Board> p2){
    this->p1 = p1;
    this->p2 = p2;
}

// restart method deletes the boards sets the highscore to 0 and player boolean to “TRUE” and creates new boards
void Game::restart(){
    std::vector<std::vector<char>> empty =
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
    p1 = std::shared_ptr<Board>{new Board{createCellVec(empty),0,0,false,seed,file1}}; // level
    p2 = std::shared_ptr<Board>{new Board{createCellVec(empty),0,0,false,seed,file2}}; // level
    player_turn = true;
    gameEnded = false;
    updateGraphics();
    updateText();
    
}

// updateHighScore method is called after each command to compare player scores with 
// highscore and to update if needed.
void Game::updateHighScore(){
    int p1_score = p1->getScore();
    int p2_score = p2->getScore();
    if(p1_score > highScore){
        highScore = p1_score;
    }
    if(p2_score > highScore){
        highScore = p2_score;
    }
}

// left method calls the left method of the Board depending on the turn, if the block is heavy with weight n 
// calls the down method of the Board for n times then calls updateHighScore, updateText and updateGraphics methods
void Game::left(int n){
    if(!gameEnded && !active_speical_actions){
        bool redraw = false;
        if(player_turn){
            for(int i = 0; i < n; i++){
                if(p1->left()){
                    redraw = true;
                }
            }
            if(redraw){
                for(int i = 0; i < p1->getCurrentBlock()->getHeavy(); i++) p1->down();
            }
        }else{
            for(int i = 0; i < n; i++){
                if(p2->left()){
                    redraw = true;
                }
            }
            if(redraw){
                for(int i = 0; i < p2->getCurrentBlock()->getHeavy(); i++) p2->down();
            }
        }
        
        if(redraw){
            setPlayerTurn();
            updateHighScore();
            updateGraphics();
            updateText();
        }
    }
    
}

// right method calls the right method of the Board depending on the turn, 
// if the block is heavy with weight n calls the down method of the Board
// for n times then calls updateHighScore, updateText and updateGraphics methods
void Game::right(int n){

    if(!gameEnded && !active_speical_actions){
        bool redraw = false;
        if(player_turn){
            for(int i = 0; i < n; i++){
                if(p1->right()){
                    redraw = true;
                }
            }
            if(redraw){
                for(int i = 0; i < p1->getCurrentBlock()->getHeavy(); i++) p1->down();
            }
        }else{
            for(int i = 0; i < n; i++){
                if(p2->right()){
                    redraw = true;
                }
            }
            if(redraw){
                for(int i = 0; i < p2->getCurrentBlock()->getHeavy(); i++) p2->down();
            }
        }
        
        if(redraw){
            setPlayerTurn();
            updateHighScore();
            updateGraphics();
            updateText();
        }
    }
}

// drop method calls the drop method of the Board depending on the turn,
// gets the number of eliminated_rows from the Board, activates special 
// functions or ends the game if needed. Else it calls updateHighScore, 
// updateText  and updateGraphics methods
void Game::drop(int n){
    if(!gameEnded && !active_speical_actions){
        int eliminated_rows = 0;
        if(player_turn){
            if(n == 1){
                // special actions are available
                eliminated_rows = p1->drop();
            }else{
                for(int i = 0; i < n; i++){
                    eliminated_rows = p1->drop();
                    if(eliminated_rows == -1) break; 
                }
                if(eliminated_rows != -1) eliminated_rows = 0;
                // special actions not availbe for multiple drops
            }
            //eliminated_rows = 3; // UNCOMMENT TO TEST speical actions
            //std::cout << eliminated_rows << std::endl;
        }else{
            if(n == 1){
                // special actions are available
                eliminated_rows = p2->drop();
            }else{
                // special actions traded
                for(int i = 0; i < n; i++){
                    eliminated_rows = p2->drop();
                    if(eliminated_rows == -1) break; 
                }
                if(eliminated_rows != -1) eliminated_rows = 0;
                // special actions not availbe for multiple drops
            }
            //eliminated_rows = 3; // UNCOMMENT TO TEST speical actions
            //std::cout << eliminated_rows << std::endl;
        }
        if(noSpecial && eliminated_rows != -1){
            // if no special actions allowed eliminated rows sets to be 0
            eliminated_rows = 0;
        }
        if(eliminated_rows < 2){
            setPlayerTurn();
        }
        updateHighScore();
        updateGraphics(eliminated_rows);
        updateText(eliminated_rows);
        if(eliminated_rows >= 2){
            if(eliminated_rows >= 3){
                if(player_turn){
                    p1->setCB(std::shared_ptr<Block>(new BombBlock));
                    updateGraphics(eliminated_rows);
                    updateText(eliminated_rows);
                }else{
                    p2->setCB(std::shared_ptr<Block>(new BombBlock));
                    updateGraphics(eliminated_rows);
                    updateText(eliminated_rows);
                }
            }
            active_speical_actions = true;
        }else if(eliminated_rows == -1){
             gameEnded = true;
        }
    }
    
}

// testForce method gets a block and changes the player’s current block
void Game::testForce(std::shared_ptr<Block> b){
    active_speical_actions = false;
    bool redraw = false;
    if(player_turn){
        p1->setCB(b);
        redraw = true;
        
    }else{
        p2->setCB(b);
        redraw = true;
    }
    if(redraw){
        setPlayerTurn();
        updateHighScore();
        updateGraphics();
        updateText();
    }


}


// clockwise method calls the clockwise method of the Board depending on the turn, 
// if the block is heavy with weight n calls the down method of the Board for n times then 
// calls updateHighScore, updateText and updateGraphics methods
void Game::clockwise(int n){
    if(!gameEnded && !active_speical_actions){
        bool redraw = false;
        if(player_turn){
            for(int i = 0; i < n; i++){
                if(p1->clockwise()){
                    redraw = true;
                }
            }
            if(redraw){
                for(int i = 0; i < p1->getCurrentBlock()->getHeavy(); i++) p1->down();
            }
        }else{
            for(int i = 0; i < n; i++){
                if(p2->clockwise()){
                    redraw = true;
                }
            }
            if(redraw){
                for(int i = 0; i < p2->getCurrentBlock()->getHeavy(); i++) p2->down();
            }
        }
        
        if(redraw){
            setPlayerTurn();
            updateHighScore();
            updateGraphics();
            updateText();
        }
    }
}

// cclockwise method calls the cclockwise method of the Board depending on the turn, 
// if the block is heavy with weight n calls the down method of the Board for n times then 
// calls updateHighScore, updateText and updateGraphics methods
void Game::cclockwise(int n){
    if(!gameEnded && !active_speical_actions){
        bool redraw = false;
        if(player_turn){
            for(int i = 0; i < n; i++){
                if(p1->cclockwise()){
                    redraw = true;
                }
            }
            if(redraw){
                for(int i = 0; i < p1->getCurrentBlock()->getHeavy(); i++) p1->down();
            }
        }else{
            for(int i = 0; i < n; i++){
                if(p2->cclockwise()){
                    redraw = true;
                }
            }
            if(redraw){
                for(int i = 0; i < p2->getCurrentBlock()->getHeavy(); i++) p2->down();
            }
        }
        
        if(redraw){
            setPlayerTurn();
            updateHighScore();
            updateGraphics();
            updateText();
        }
    }
}


// levelUp method calls the levelUp method of the Board depending on the turn
void Game::levelUp(int n){
    if(!gameEnded && !active_speical_actions){
        bool redraw = false;
        if(player_turn){
            for(int i = 0; i < n; i++){
                if(p1->levelUp()){
                    redraw = true;
                }
            }
        }else{
            for(int i = 0; i < n; i++){
                if(p2->levelUp()){
                    redraw = true;
                }
            }
        }
        
        if(redraw){
            setPlayerTurn();
            updateHighScore();
            updateGraphics();
            updateText();
        }
    }
}

// down method calls the down method of the Board depending on the turn, 
// if the block is heavy with weight n calls the down method of the Board for n times again then 
void Game::down(int n){
    if(!gameEnded && !active_speical_actions){
        bool redraw = false;
        if(player_turn){
            for(int i = 0; i < n; i++){
                if(p1->down()){
                    redraw = true;
                }
            }
            if(redraw){
                for(int i = 0; i < p1->getCurrentBlock()->getHeavy(); i++) p1->down();
            }
        }else{
            for(int i = 0; i < n; i++){
                if(p2->down()){
                    redraw = true;
                }
            }
            if(redraw){
                for(int i = 0; i < p2->getCurrentBlock()->getHeavy(); i++) p2->down();
            }
        }
        
        if(redraw){
            setPlayerTurn();
            updateHighScore();
            updateGraphics();
            updateText();
        }
    }
}

// levelDown method calls the levelDown method of the Board depending on the turn
void Game::levelDown(int n){
    if(!gameEnded && !active_speical_actions){
        bool redraw = false;
        if(player_turn){
            for(int i = 0; i < n; i++){
                if(p1->levelDown()){
                    redraw = true;
                }
            }
        }else{
            for(int i = 0; i < n; i++){
                if(p2->levelDown()){
                    redraw = true;
                }
            }
        }
        if(redraw){
            setPlayerTurn();
            updateHighScore();
            updateGraphics();
            updateText();
        }
    }
}


// random method calls the random method of the Board depending on the turn.
void Game::random(){
    bool redraw = false;
    if(player_turn){
        if(p1->random()){
            redraw = true;
        }
    }else{
        if(p2->random()){
            redraw = true;
        }
    }
    if(redraw){
        setPlayerTurn();
        updateHighScore();
        updateGraphics();
        updateText();
    }
}

// noRandom method calls the noRandom method of the Board depending on the
// turn while passing the same parameters
void Game::noRandom(std::string file){
    bool redraw = false;
    if(player_turn){
        if(p1->noRandom(file)){
            redraw = true;
        }
    }else{
        if(p2->noRandom(file)){
            redraw = true;
        }
    }
    if(redraw){
        setPlayerTurn();
        updateHighScore();
        updateGraphics();
        updateText();
    }
}

// force method calls the force method of the Board depending on the 
// turn while passing the same parameters
void Game::force(std::shared_ptr<Block> b){
    if(active_speical_actions){
        bool redraw = false;
        if(player_turn){
            b->setHeavy(p2->getCurrentBlock()->getHeavy());
            p2->setCB(b);
            redraw = true;
            
        }else{
            b->setHeavy(p1->getCurrentBlock()->getHeavy());
            p1->setCB(b);
            redraw = true;
        }
        if(redraw){
            active_speical_actions = false;
            setPlayerTurn();
            updateHighScore();
            updateGraphics();
            updateText();
        }
    }
    active_speical_actions = false;
    
}

// blind method calls the blind method of the Board depending on the turn.
void Game::blind(){
    if(active_speical_actions){
        bool redraw = false;
        if(player_turn){
            if(p2->blind()){
                redraw = true;
            }
        }else{
            if(p1->blind()){
                redraw = true;
            }
        }
        if(redraw){
            active_speical_actions = false;
            setPlayerTurn();
            updateHighScore();
            updateGraphics();
            updateText();
        }
    }
    active_speical_actions = false;
}

// updateGraphics method calls the draw methods of the GraphicsWindow
void Game::updateGraphics(int eliminated_rows){
    if(!onlyText){
        GW->draw(p1, p2, highScore, player_turn, nightMode);

        if(eliminated_rows >= 2 || active_speical_actions){
            GW->specialActions(player_turn, nightMode, eliminated_rows);
            
        }else if (eliminated_rows == -1 || gameEnded){
            GW->endGame(player_turn, nightMode);
        }
    }
}

// updateText method calls the draw methods of the TextWindow 
void Game::updateText(int eliminated_rows){
    TW->draw(p1, p2, highScore, player_turn, eliminated_rows);
}

// heavy method calls the increaseHeavy method of the Board depending on turn
void Game::heavy(int heavy){
    if(active_speical_actions){
        if(player_turn){
            p2->increaseHeavy(heavy);
        }else{
            p1->increaseHeavy(heavy);
        }
    }
    active_speical_actions = false;
    setPlayerTurn();
    updateGraphics();
        
}

// returns high score
int Game::getHighScore(){
    return highScore;
}

// changes the turn of the player
void Game::setPlayerTurn(){
    if(player_turn){
        player_turn = false;
    }else{
        player_turn = true;
    }
}

