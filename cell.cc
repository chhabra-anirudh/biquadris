export module Cell;

class Block;

using namespace std;

export class Cell {
    int row;
    int col;
    Block* occupiedBy;
    bool isEmpty;

    public:
        Cell(int row = 0, int col = 0);

        // Occupy this cell with a block
        void occupy(Block *block);

        // Clear this cell
        void clear();

        // Get the block occupying this cell
        Block *getBlock() const;
        
        // Getters
        bool empty() const; // Check if cell is empty
        int getRow() const;
        int getCol() const;
};
