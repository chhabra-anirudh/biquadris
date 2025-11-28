export module Board;

import <vector>;
import <memory>;
import Position;
// import Cell;
import Block;
import Subject;

using namespace std;

export class Board : public Subject {
    inline static const int WIDTH = 11; // Columns
    inline static const int HEIGHT = 18; // 15 visible + 3 reserved
    inline static const int DISPLAY_HEIGHT = 15; // 15 visible

    // Using unique_ptr for automatic memory management
    vector<vector<unique_ptr<Cell>>> cells;  // Grid of cells [row][col]
    vector<Block*> placedBlocks;  // Block pointers (non-owning - Player owns blocks)

    public:
        Board(); // constuctor
        ~Board(); // destructor
        Board(const Board &other) = delete;
        Board &operator=(const Board &other) = delete;

        // Block placement and validation
        bool placeBlock(Block *block);
        bool canPlace(Block* block, int row, int col) const;
        bool canPlaceAtPositions(const vector<Position> &positions) const;
        void removeBlock(Block* block);

        // Row operations
        int clearFullRows();
        bool isRowFull(int row) const;
        void clearRow(int row);
        void dropRowsAbove(int clearedRow);

        // Star block (Level 4 feature)
        Block *createStarBlock();

        // Getters
        Cell* getCell(int row, int col) const;
        int getWidth() const;
        int getHeight() const;
        int getDisplayHeight() const;
};
