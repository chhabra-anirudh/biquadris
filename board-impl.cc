module Board;

import <vector>;
import <algorithm>;
import <memory>;
import Position;
//import Cell;
import Block;
import StarBlock;
import Subject;

using namespace std;

Board::Board() {
    cells.resize(HEIGHT);
    for (int r = 0; r < HEIGHT; ++r) {
        cells[r].resize(WIDTH);
        for (int c = 0; c < WIDTH; ++c) {
            cells[r][c] = make_unique<Cell>(r, c);
        }
    }
}

Board::~Board() {}

bool Board::canPlace(Block *block, int row, int col) const {
    // Get the shape of the block at position (0,0)
    Position originalPos = block->getPosition();
    int originalRow = originalPos.row;
    int originalCol = originalPos.col;

    // Calculate offset 
    int offsetRow = row - originalRow;
    int offsetCol = col - originalCol;

    vector<Position> positions = block->getCurrentPositions();

    for (const auto &pos : positions) {
        int newRow = pos.row + offsetRow;
        int newCol = pos.col + offsetCol;

        // Check boundaries
        if (newRow < 0 || newRow >= HEIGHT || 
            newCol < 0 || newCol >= WIDTH) {
            return false;
        }
        
        // Check if cell is already occupied
        if (!cells[newRow][newCol]->empty()) {
            return false;
        }
    }
    
    return true;
}

bool Board::canPlaceAtPositions(const vector<Position> &positions) const {
    for (const auto &pos : positions) {
        // Check boundaries
        if (pos.row < 0 || pos.row >= HEIGHT || 
            pos.col < 0 || pos.col >= WIDTH) {
            return false;
        }
        
        // Check if cell is already occupied
        if (!cells[pos.row][pos.col]->empty()) {
            return false;
        }
    }
    return true;
}

bool Board::placeBlock(Block* block) {
    vector<Position> positions = block->getCurrentPositions();
    
    if (!canPlaceAtPositions(positions)) {
        return false;
    }
    
    // Place block on board
    for (const auto &pos : positions) {
        // Get raw pointer from unique_ptr
        cells[pos.row][pos.col]->occupy(block);
        block->addCell(cells[pos.row][pos.col].get());
    }
    
    block->setPlaced(true);
    placedBlocks.emplace_back(block);
    
    notifyObservers();
    return true;
}

void Board::removeBlock(Block* block) {
    // Clear cells occupied by this block
    for (Cell* cell : block->getCells()) {
        cell->clear();
    }
    
    // Remove from blocks vector
    for (auto it = placedBlocks.begin(); it != placedBlocks.end();) {
        if (*it == block) it = placedBlocks.erase(it);
        else ++it;
    }
    
    notifyObservers();
}

bool Board::isRowFull(int row) const {
    if (row < 0 || row >= HEIGHT) return false;
    
    for (int c = 0; c < WIDTH; ++c) {
        if (cells[row][c]->empty()) {
            return false;
        }
    }
    return true;
}

void Board::clearRow(int row) {
    for (int c = 0; c < WIDTH; ++c) {
        Cell* cell = cells[row][c].get();  // Get raw pointer from unique_ptr
        if (!cell->empty()) {
            Block* block = cell->getBlock();
            if (block) {
                block->removeCell(cell);
                block->decrementCell();
                
                // If block is completely cleared, remove it
                if (!block->isFilled()) {
                    for (auto it = placedBlocks.begin(); it != placedBlocks.end();) {
                        if (*it == block) it = placedBlocks.erase(it);
                        else ++it;
                    }
                }
            }
            cell->clear();
        }
    }
}

void Board::dropRowsAbove(int clearedRow) {
    // Move all rows above down by one
    for (int r = clearedRow; r < HEIGHT - 1; ++r) {
        for (int c = 0; c < WIDTH; ++c) {
            Cell* currentCell = cells[r][c].get();
            Cell* aboveCell = cells[r + 1][c].get();
            
            if (!aboveCell->empty()) {
                Block* block = aboveCell->getBlock();
                currentCell->occupy(block);
                
                // Update block's cell reference
                block->removeCell(aboveCell);
                block->addCell(currentCell);
                
                aboveCell->clear();
            } else {
                currentCell->clear();
            }
        }
    }
    
    // Clear top row
    for (int c = 0; c < WIDTH; ++c) {
        cells[HEIGHT - 1][c]->clear();
    }
}

int Board::clearFullRows() {
    int rowsCleared = 0;
    
    // Check from bottom to top
    for (int r = 0; r < HEIGHT; ++r) {
        if (isRowFull(r)) {
            clearRow(r);
            dropRowsAbove(r);
            ++rowsCleared;
            --r; // Re-check this row since we dropped rows down
        }
    }
    
    if (rowsCleared > 0) {
        notifyObservers();
    }
    
    return rowsCleared;
}

Block* Board::createStarBlock() {
    // Drop a 1x1 block in the center column (column 5)
    StarBlock *star = new StarBlock(4); // Level 4 star block
    
    // Find the lowest empty position in center column
    int targetRow = 0;
    for (int r = 0; r < HEIGHT; ++r) {
        if (cells[r][5]->empty()) {
            targetRow = r;
            break;
        }
    }
    
    star->setPosition(Position {targetRow, 5});
    return star;
}

Cell* Board::getCell(int row, int col) const {
    if (row >= 0 && row < HEIGHT && col >= 0 && col < WIDTH) {
        return cells[row][col].get();  // Return raw pointer from unique_ptr
    }
    return nullptr;
}

int Board::getWidth() const {
    return WIDTH;
}

int Board::getHeight() const {
    return HEIGHT;
}

int Board::getDisplayHeight() const {
    return DISPLAY_HEIGHT;
}
