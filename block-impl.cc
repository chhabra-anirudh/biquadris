module Block;

import <vector>;
import <algorithm>;
import Position;
import Cell;

using namespace std;

Block::Block(char type, int level, bool heavy) 
    : blockType{type}, level{level}, bottomLeft{Position {0, 0}}, orientation{0}, 
    isHeavy{heavy}, isPlaced{false}, cellsFilled{4} {}

Block::~Block(){}

void Block::setPosition(const Position &pos) {
    bottomLeft = pos;
}

Position Block::getPosition() const {
    return bottomLeft;
}

void Block::rotateClockwise() {
    orientation = (orientation + 1) % 4;
}

void Block::rotateCounterClockwise() {
    orientation = (orientation + 3) % 4;
}

char Block::getType() const {
    return blockType;
}

int Block::getLevel() const {
    return level;
}

bool Block::heavy() const {
    return isHeavy;
}

void Block::setHeavy(bool heavy) {
    isHeavy = heavy;
}

bool Block::placed() const {
    return isPlaced;
}

void Block::setPlaced(bool placed) {
    isPlaced = placed;
}

void Block::addCell(Cell *cell) {
    cells.emplace_back(cell);
}

void Block::removeCell(Cell *cell) {
    for (auto it = cells.begin(); it != cells.end();) {
        if (*it == cell) it = cells.erase(it);
        else ++it;
    }
}

const vector<Cell*> &Block::getCells() const {
    return cells;
}

bool Block::isFilled() {
    return cellsFilled > 0;
}

void Block::decrementCell() {
    if (cellsFilled > 0) {
        --cellsFilled;
    }
}

int Block::getOrientation() const {
    return orientation;
}

vector<Position> Block::getCurrentPositions() const {
    vector<Position> shape = getShapeCoordinates();
    vector<Position> absolute;

    for (int i = 0; i < shape.size(); i++) {
        absolute.emplace_back(Position {(bottomLeft.row + shape[i].row), (bottomLeft.col + shape[i].col)});
    }

    return absolute;
}
