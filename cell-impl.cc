module Cell;

import Block;

using namespace std;

Cell::Cell(int row, int col) : row{row}, col{col}, occupiedBy{nullptr}, isEmpty{true} {}

void Cell::occupy(Block *block) {
    occupiedBy = block;
    isEmpty = false;
}

void Cell::clear() {
    occupiedBy = nullptr;
    isEmpty = true;
}

Block *Cell::getBlock() const {
    return occupiedBy;
}

bool Cell::empty() const {
    return isEmpty;
}

int Cell::getRow() const {
    return row;
}

int Cell::getCol() const {
    return col;
}
