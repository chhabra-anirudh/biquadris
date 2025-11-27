module GraphicsDisplay;

import <vector>;
import <sstream>;
import <vector>;
import Position;
import Board;
import Player;
import Observer;
import XWindow;

GraphicsDisplay:: GraphicsDisplay(Board* b1, Board* b2, Player *p1, Player *p2):
    board1{b1}, board2{b2}, player1{p1}, player2{p2} {
        int windowWidth = 600;
        int windowHeight = 500;
        xw = new Xwindow(windowWidth, windowHeight);

        notify();
}

GraphicsDisplay::~GraphicsDisplay() {
    delete xw;
}

int GraphicsDisplay::getBlockColor(char blockType) const {
    if (blockType == 'I') return Xwindow::Cyan;
    else if (blockType == 'J') return Xwindow::Blue;
    else if (blockType == 'L') return Xwindow::Orange;
    else if (blockType == 'O') return Xwindow::Yellow;
    else if (blockType == 'Z') return Xwindow::Green;
    else if (blockType == 'T') return Xwindow::Red;
    else if (blockType == '*') return Xwindow::Brown;
    else if (blockType == 'S') return Xwindow::White;
}

void GraphicsDisplay::drawCell(int x, int y, int color) {
    xw->fillRectangle(x, y, CELL_SIZE, CELL_SIZE, color);
    xw->fillRectangle(x, y, CELL_SIZE, 1, Xwindow::Black);
    xw->fillRectangle(x, y, 1, CELL_SIZE, Xwindow::Black);
    xw->fillRectangle(x + CELL_SIZE - 1, y, 1, CELL_SIZE, Xwindow::Black);
    xw->fillRectangle(x, y + CELL_SIZE - 1, CELL_SIZE, 1, Xwindow::Black);
}

void GraphicsDisplay::drawBoard(int boardNum) {
    Board* board = (boardNum == 1) ? board1 : board2;
    Player* player = (boardNum == 1) ? player1 : player2;
    
    int offsetX = (boardNum == 1) ? BOARD_OFFSET_X : BOARD2_OFFSET_X;
    int offsetY = BOARD1_OFFSET_Y;

    for (int r = 0; r < BOARD_HEIGHT; ++r) {
        for (int c = 0; c < BOARD_WIDTH; ++c) {
            int x = offsetX + c * CELL_SIZE;
            int y = offsetY + (BOARD_HEIGHT - 1 - r) * CELL_SIZE;
            
            Cell* cell = board->getCell(r, c);
            int color = Xwindow::White;
            
            if (cell && !cell->empty()) {
                Block* block = cell->getBlock();
                if (block) {
                    color = getBlockColor(block->getType());
                }
            }
            
            if (player->blind() && r >= 2 && r <= 11 && c >= 2 && c <= 8) {
                color = Xwindow::Black;
            }
            
            drawCell(x, y, color);
        }
    }
    Block* current = player->getCurrentBlock();
    if (current && !current->placed()) {
        std::vector<Position> positions = current->getCurrentPositions();
        int color = getBlockColor(current->getType());
        
        for (const auto& pos : positions) {
            if (pos.row >= 0 && pos.row < BOARD_HEIGHT) {
                int x = offsetX + pos.col * CELL_SIZE;
                int y = offsetY + (BOARD_HEIGHT - 1 - pos.row) * CELL_SIZE;
                drawCell(x, y, color);
            }
        }
    }
}

void GraphicsDisplay::drawBorders() {
    int x1 = BOARD_OFFSET_X - 2;
    int y1 = BOARD1_OFFSET_Y - 2;
    int w = BOARD_WIDTH * CELL_SIZE + 4;
    int h = BOARD_HEIGHT * CELL_SIZE + 4;
    
    xw->fillRectangle(x1, y1, w, 2, Xwindow::Black);
    xw->fillRectangle(x1, y1, 2, h, Xwindow::Black);
    xw->fillRectangle(x1 + w - 2, y1, 2, h, Xwindow::Black);
    xw->fillRectangle(x1, y1 + h - 2, w, 2, Xwindow::Black);
    
    int x2 = BOARD2_OFFSET_X - 2;
    xw->fillRectangle(x2, y1, w, 2, Xwindow::Black);
    xw->fillRectangle(x2, y1, 2, h, Xwindow::Black);
    xw->fillRectangle(x2 + w - 2, y1, 2, h, Xwindow::Black);
    xw->fillRectangle(x2, y1 + h - 2, w, 2, Xwindow::Black);
}

void GraphicsDisplay::drawInfo() {
    xw->fillRectangle(0, 0, 600, 90, Xwindow::White);
    
    std::ostringstream oss1;
    oss1 << "Player 1";
    xw->drawString(BOARD_OFFSET_X, 20, oss1.str());
    
    oss1.str("");
    oss1 << "Level: " << player1->getLevel();
    xw->drawString(BOARD_OFFSET_X, 40, oss1.str());
    
    oss1.str("");
    oss1 << "Score: " << player1->getScore();
    xw->drawString(BOARD_OFFSET_X, 60, oss1.str());
    
    std::ostringstream oss2;
    oss2 << "Player 2";
    xw->drawString(BOARD2_OFFSET_X, 20, oss2.str());
    
    oss2.str("");
    oss2 << "Level: " << player2->getLevel();
    xw->drawString(BOARD2_OFFSET_X, 40, oss2.str());
    
    oss2.str("");
    oss2 << "Score: " << player2->getScore();
    xw->drawString(BOARD2_OFFSET_X, 60, oss2.str());
    
    xw->drawString(BOARD_OFFSET_X, 420, "Next:");
    xw->drawString(BOARD2_OFFSET_X, 420, "Next:");
    
    drawNextBlock(player1, BOARD_OFFSET_X, 440);
    drawNextBlock(player2, BOARD2_OFFSET_X, 440);
}

void GraphicsDisplay::drawNextBlock(Player* player, int x, int y) {
    Block* next = player->getNextBlock();
    if (!next) return;
    
    Position origPos = next->getPosition();
    next->setPosition(Position(0, 0));
    std::vector<Position> positions = next->getCurrentPositions();
    
    int color = getBlockColor(next->getType());
    
    for (const auto& pos : positions) {
        int px = x + pos.col * CELL_SIZE;
        int py = y + (3 - pos.row) * CELL_SIZE; 
        drawCell(px, py, color);
    }
    
    next->setPosition(origPos);
}

void GraphicsDisplay::notify() {
    xw->fillRectangle(0, 0, 600, 500, Xwindow::White);
    
    drawInfo();
    drawBorders();
    drawBoard(1);
    drawBoard(2);
}
