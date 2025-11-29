module TextDisplay;

import <vector>;
import <iostream>;
import <iomanip>;
import <string>;
import Board;
import Player;
import Block;


using namespace std;

TextDisplay::TextDisplay(Board *b1, Board *b2, Player *p1, Player *p2)
    : board1{b1}, board2{b2}, player1{p1}, player2{p2}, hiScore{0} {
        
    //Initialize grids with empty spaces
    for (int r = 0; r < ROW_COUNT; r++) {
        for (int c = 0; c < COL_COUNT; c++) {
            grid1[r][c] = ' ';
            grid2[r][c] = ' ';
        }
    }    
}

void TextDisplay::setHiScore(int score) {
    hiScore = score;
}

void TextDisplay::updateBoards(Board *b1, Board *b2) {
    board1 = b1;
    board2 = b2;
}

void TextDisplay::notify() {
    updateGrid(grid1, board1, player1);
    updateGrid(grid2, board2, player2);
}

void TextDisplay::updateGrid(char grid[ROW_COUNT][COL_COUNT], Board* board, Player *player) {
    //clear grid
    for (int r = 0; r < ROW_COUNT; r++) {
        for (int c = 0; c < COL_COUNT; c++) {
            grid[r][c] = ' ';
        }
    }
    
    // Fill in placed blocks
    for (int r = 0; r < ROW_COUNT; r++) {
        for (int c = 0; c < COL_COUNT; c++) {
            Cell *cell = board->getCell(r, c);
            if (cell && !cell->empty()) {
                Block *block = cell->getBlock();
                if (block) {
                    grid[r][c] = block->getType();
                }
            }
        }
    }

    //Overlay current Block (if not placed)
    Block *current = player->getCurrentBlock();
    if (current && !current->placed()) {
        vector<Position> positions = current->getCurrentPositions();
        for (const auto &pos: positions) {
            if (pos.row >= 0 && pos.row < ROW_COUNT &&
                pos.col >= 0 && pos.col < COL_COUNT) {
                    grid[pos.row][pos.col] = current->getType(); 
                }
        }
    }
}

void TextDisplay::drawGrid(ostream& out, char grid[ROW_COUNT][COL_COUNT], Player *player, int playerNum) {
    out << "Level:    " << player->getLevel() << endl;
    out << "Score:    " << player->getScore() << endl;
    out << "-----------" << endl;

    //Display from top to bottom (reverse order, skip reserve rows)
    for (int r = 14; r >= 0; --r) {
        for (int c = 0; c < COL_COUNT; ++c) {
             // Apply blind effect
            if (player->blind() && r >= 2 && r <= 11 && c >= 2 && c <= 8) {
                out << '?';
            } else {
                out << grid[r][c];
            }
        }
        out << endl;
    }

    out << "-----------" << endl;
    out << "Next:" << endl;
    
    // Display next block
    Block* next = player->getNextBlock();
    if (next) {
        //Get shape at position (0,0)
        next->setPosition(Position(0,0));
        vector<Position> nextPositions = next->getCurrentPositions();

        // Find bounding box
        int minRow = 100, maxRow = -1, minCol = 100, maxCol = -1;
        for (const auto& pos : nextPositions) {
            if (pos.row < minRow) minRow = pos.row;
            if (pos.row > maxRow) maxRow = pos.row;
            if (pos.col < minCol) minCol = pos.col;
            if (pos.col > maxCol) maxCol = pos.col;
        }
        
        // Draw next block
        for (int r = maxRow; r >= minRow; --r) {
            for (int c = minCol; c <= maxCol; ++c) {
                bool found = false;
                for (const auto& pos : nextPositions) {
                    if (pos.row == r && pos.col == c) {
                        out << next->getType();
                        found = true;
                        break;
                    }
                }
                if (!found) out << ' ';
            }
            out << endl;
        }
    }
}   

void TextDisplay::display(ostream &out) {
    notify();  // Update grids
    
    // Display both boards side by side
    out << endl;
    
    // Headers
    out << "Level:    " << setw(10) << player1->getLevel() 
        << "          Level:    " << player2->getLevel() << endl;
    out << "Score:    " << setw(10) << player1->getScore() 
        << "          Score:    " << player2->getScore() << endl;
    out << "Hi Score: " << setw(10) << hiScore << endl;
    out << "-----------          -----------" << endl;
    
    // Boards side by side
    for (int r = 14; r >= 0; --r) {
        for (int c = 0; c < COL_COUNT; ++c) {
            if (player1->blind() && r >= 2 && r <= 11 && c >= 2 && c <= 8) {
                out << '?';
            } else {
                out << grid1[r][c];
            }
        }
        out << "          ";
        for (int c = 0; c < COL_COUNT; ++c) {
            if (player2->blind() && r >= 2 && r <= 11 && c >= 2 && c <= 8) {
                out << '?';
            } else {
                out << grid2[r][c];
            }
        }
        out << endl;
    }
    
    out << "-----------          -----------" << endl;
    
    // Next blocks
    out << "Next:                Next:" << endl;
    
    // Get next block shapes
    Block* next1 = player1->getNextBlock();
    Block* next2 = player2->getNextBlock();
    
    if (next1 && next2) {
        Position origPos1 = next1->getPosition();
        Position origPos2 = next2->getPosition();
        
        next1->setPosition(Position(0, 0));
        next2->setPosition(Position(0, 0));
        
        auto pos1 = next1->getCurrentPositions();
        auto pos2 = next2->getCurrentPositions();
        
        // Find max height
        int maxHeight = 0;
        for (const auto& p : pos1) if (p.row > maxHeight) maxHeight = p.row;
        for (const auto& p : pos2) if (p.row > maxHeight) maxHeight = p.row;
        
        for (int r = maxHeight; r >= 0; --r) {
            // Player 1 next block
            for (int c = 0; c < 4; ++c) {
                bool found = false;
                for (const auto& p : pos1) {
                    if (p.row == r && p.col == c) {
                        out << next1->getType();
                        found = true;
                        break;
                    }
                }
                if (!found) out << ' ';
            }
            
            out << "               ";
            
            // Player 2 next block
            for (int c = 0; c < 4; ++c) {
                bool found = false;
                for (const auto& p : pos2) {
                    if (p.row == r && p.col == c) {
                        out << next2->getType();
                        found = true;
                        break;
                    }
                }
                if (!found) out << ' ';
            }
            out << endl;
        }
        
        next1->setPosition(origPos1);
        next2->setPosition(origPos2);
    }
    
    out << endl;
}
