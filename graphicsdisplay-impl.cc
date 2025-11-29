module GraphicsDisplay;

import <vector>;
import <sstream>;
import <vector>;
import Position;
import Board;
import Player;
import Observer;
import XWindow;

using namespace std;

GraphicsDisplay:: GraphicsDisplay(Board* b1, Board* b2, Player *p1, Player *p2):
    board1{b1}, board2{b2}, player1{p1}, player2{p2}, hiScore{0},
    cachedScore1{-1}, cachedLevel1{-1}, cachedScore2{-1}, cachedLevel2{-1}, cachedHiScore{-1},
    cachedNextBlock1{' '}, cachedNextBlock2{' '} {
        int windowWidth = 600;
        int windowHeight = 550;
        xw = new Xwindow(windowWidth, windowHeight);

        // Initialize previous board state as not valid
        board1Cache.resize(BOARD_HEIGHT * BOARD_WIDTH, -1);
        board2Cache.resize(BOARD_HEIGHT * BOARD_WIDTH, -1);

        drawBorders();
        
        // initial render of boards and blocks
        notify();
}

void GraphicsDisplay::setHiScore(int score) {
    hiScore = score;
}

// update pointers to boards
void GraphicsDisplay::updateBoards(Board* b1, Board* b2) {
    board1 = b1;
    board2 = b2;
}

GraphicsDisplay::~GraphicsDisplay() {
    delete xw;
}

// associate colour for each block
int GraphicsDisplay::getBlockColor(char blockType) const {
    if (blockType == 'I') return Xwindow::Cyan;
    else if (blockType == 'J') return Xwindow::Blue;
    else if (blockType == 'L') return Xwindow::Orange;
    else if (blockType == 'O') return Xwindow::Yellow;
    else if (blockType == 'Z') return Xwindow::Green;
    else if (blockType == 'T') return Xwindow::Red;
    else if (blockType == '*') return Xwindow::Brown;
    else if (blockType == 'S') return Xwindow::Magenta;
    else return Xwindow::Black; 

void GraphicsDisplay::drawCell(int x, int y, int color) {
    // fill cell with color 
    xw->fillRectangle(x, y, CELL_SIZE, CELL_SIZE, color);
}

void GraphicsDisplay::drawBoard(int boardNum) {
    // select correct board, player and cache
    Board* board = (boardNum == 1) ? board1 : board2;
    Player* player = (boardNum == 1) ? player1 : player2;
    vector<int>& cache = (boardNum == 1) ? board1Cache : board2Cache;
    
    int offsetX = (boardNum == 1) ? BOARD_OFFSET_X : BOARD2_OFFSET_X;
    int offsetY = BOARD1_OFFSET_Y;

    // loop every cell for correct colour
    
    for (int r = 0; r < BOARD_HEIGHT; ++r) {
        for (int c = 0; c < BOARD_WIDTH; ++c) {

            // convert board to pixel coordinates
            int x = offsetX + c * CELL_SIZE;
            int y = offsetY + (BOARD_HEIGHT - 1 - r) * CELL_SIZE;
            
            int color = Xwindow::White; // Default empty
            
            // draw correct blocks
            Cell* cell = board->getCell(r, c);
            if (cell && !cell->empty()) {
                Block* block = cell->getBlock();
                if (block) {
                    color = getBlockColor(block->getType());
                }
            }
            
            // Check blind effect
            if (player->blind() && r >= 2 && r <= 11 && c >= 2 && c <= 8) {
                color = Xwindow::Black;
            }
            
            // check if blind overlays the block colour
            Block* current = player->getCurrentBlock();
            if (current && !current->placed()) {
                vector<Position> positions = current->getCurrentPositions();
                for (const auto& pos : positions) {
                    if (pos.row == r && pos.col == c) {
                        int baseColor = getBlockColor(current->getType());
                         if (player->blind() && r >= 2 && r <= 11 && c >= 2 && c <= 8) {
                            color = Xwindow::Black;
                        } else {
                            color = baseColor;
                        }
                        break; 
                    }
                }
            }

            // check if colour changes and redraw
            int cacheIndex = r * BOARD_WIDTH + c;
            if (cacheIndex >= 0 && cacheIndex < cache.size()) {
                if (cache[cacheIndex] != color) {
                    drawCell(x, y, color);
                    cache[cacheIndex] = color;
                }
            }
        }
    }
}

void GraphicsDisplay::drawBorders() {

    // draw player 1 board
    int x1 = BOARD_OFFSET_X - 2;
    int y1 = BOARD1_OFFSET_Y - 2;
    int w = BOARD_WIDTH * CELL_SIZE + 4;
    int h = BOARD_HEIGHT * CELL_SIZE + 4;
    
    xw->fillRectangle(x1, y1, w, 2, Xwindow::Black);
    xw->fillRectangle(x1, y1, 2, h, Xwindow::Black);
    xw->fillRectangle(x1 + w - 2, y1, 2, h, Xwindow::Black);
    xw->fillRectangle(x1, y1 + h - 2, w, 2, Xwindow::Black);
    
    // draw player 2 board
    int x2 = BOARD2_OFFSET_X - 2;
    xw->fillRectangle(x2, y1, w, 2, Xwindow::Black);
    xw->fillRectangle(x2, y1, 2, h, Xwindow::Black);
    xw->fillRectangle(x2 + w - 2, y1, 2, h, Xwindow::Black);
    xw->fillRectangle(x2, y1 + h - 2, w, 2, Xwindow::Black);
}

void GraphicsDisplay::drawInfo() {
    // update player 1
    if (player1->getScore() != cachedScore1 || player1->getLevel() != cachedLevel1) {
        xw->fillRectangle(BOARD_OFFSET_X, 0, 150, 80, Xwindow::White); // Clear P1 area
        
        std::ostringstream oss1;
        oss1 << "Player 1";
        xw->drawString(BOARD_OFFSET_X, 20, oss1.str());
        
        oss1.str("");
        oss1 << "Level: " << player1->getLevel();
        xw->drawString(BOARD_OFFSET_X, 40, oss1.str());
        
        oss1.str("");
        oss1 << "Score: " << player1->getScore();
        xw->drawString(BOARD_OFFSET_X, 60, oss1.str());
        
        cachedScore1 = player1->getScore();
        cachedLevel1 = player1->getLevel();
    }

    //  update player 2
    if (player2->getScore() != cachedScore2 || player2->getLevel() != cachedLevel2) {
        xw->fillRectangle(BOARD2_OFFSET_X, 0, 150, 80, Xwindow::White); // Clear P2 area

        std::ostringstream oss2;
        oss2 << "Player 2";
        xw->drawString(BOARD2_OFFSET_X, 20, oss2.str());
        
        oss2.str("");
        oss2 << "Level: " << player2->getLevel();
        xw->drawString(BOARD2_OFFSET_X, 40, oss2.str());
        
        oss2.str("");
        oss2 << "Score: " << player2->getScore();
        xw->drawString(BOARD2_OFFSET_X, 60, oss2.str());
        
        cachedScore2 = player2->getScore();
        cachedLevel2 = player2->getLevel();
    }
    
    // update high score
    if (hiScore != cachedHiScore) {
        xw->fillRectangle(250, 0, 100, 30, Xwindow::White); // Clear Hi Score area
        ostringstream ossHi;
        ossHi << "Hi Score: " << hiScore;
        xw->drawString(250, 20, ossHi.str());
        cachedHiScore = hiScore;
    }
    
    // draw next block preview

    Block* next1 = player1->getNextBlock();
    char nextType1 = next1 ? next1->getType() : ' ';
    if (nextType1 != cachedNextBlock1) {
         xw->fillRectangle(BOARD_OFFSET_X, 450, 150, 100, Xwindow::White); // Clear P1 Next area
         xw->drawString(BOARD_OFFSET_X, 475, "Next:");
         drawNextBlock(player1, BOARD_OFFSET_X, 485);
         cachedNextBlock1 = nextType1;
    }

    Block* next2 = player2->getNextBlock();
    char nextType2 = next2 ? next2->getType() : ' ';
    if (nextType2 != cachedNextBlock2) {
         xw->fillRectangle(BOARD2_OFFSET_X, 450, 150, 100, Xwindow::White); // Clear P2 Next area
         xw->drawString(BOARD2_OFFSET_X, 475, "Next:");
         drawNextBlock(player2, BOARD2_OFFSET_X, 485);
         cachedNextBlock2 = nextType2;
    }
}


void GraphicsDisplay::drawNextBlock(Player* player, int x, int y) {
    // preview the next block
    Block* next = player->getNextBlock();
    if (!next) return;
    
    // temporary block positioning at origin
    Position origPos = next->getPosition();
    next->setPosition(Position(0, 0));
    std::vector<Position> positions = next->getCurrentPositions();
    
    int color = getBlockColor(next->getType());
    
    // determine height of block
    int maxRow = 0;
    for (const auto& pos : positions) {
        if (pos.row > maxRow) maxRow = pos.row;
    }
    
    // draw every square in next block
    for (const auto& pos : positions) {
        int px = x + pos.col * CELL_SIZE;
        int py = y + (maxRow - pos.row) * CELL_SIZE;
        drawCell(px, py, color);
    }
    
    next->setPosition(origPos);
}

void GraphicsDisplay::notify() {
    // redraw text and board
    drawInfo();
    drawBoard(1);
    drawBoard(2);
}
