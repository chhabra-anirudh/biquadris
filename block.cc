export module Block;

import <vector>;
import Position;

// class Cell;
export class Block;

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

export class Block {
    char blockType; // 'I', 'J', 'L', 'O', 'S', 'Z', 'T', '*'
    int level; // Level at which block was generated
    vector<Cell*> cells; // Cells occupied by this block (non-owning - Board owns them)
    Position bottomLeft; // Bottom-left corner of bounding box
    int orientation; // 0, 1, 2, 3 for rotation states
    bool isHeavy; 
    bool isPlaced; 
    int cellsFilled; // Number of cells still part of this block
    bool scored; 

    protected:
        // Subclasses (Blocks) define their shape using this pure virtual function
        virtual vector<Position> getShapeCoordinates() const = 0;

    public:
        Block(char type, int level, bool heavy = false);
        virtual ~Block();

        // Movement and rotation
        void setPosition(const Position &pos);
        Position getPosition() const;

        void rotateClockwise();
        void rotateCounterClockwise();

        // Get current cell positions relative to board
        vector<Position> getCurrentPositions() const;

        // Block state
        char getType() const;
        int getLevel() const;
        bool heavy() const;
        void setHeavy(bool heavy);
        bool placed() const;
        void setPlaced(bool placed);
        void setCellsFilled(int num);

        // Cell management
        void addCell(Cell *cell);
        void removeCell(Cell *cell);
        const vector<Cell*> &getCells() const;

        // Check if block is fully cleared
        bool isFilled();
        void decrementCell();

        int getOrientation() const;

        bool hasScored() const;
        void setScored(bool scored = true);
};
