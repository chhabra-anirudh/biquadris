module StarBlock;

import <vector>;
import Block;

using namespace std;

StarBlock::StarBlock(int level) : Block{'*', level, false} {
    this->setCellsFilled(1);
}

vector<Position> StarBlock::getShapeCoordinates() const {
    // Star Block: * (single cell, doesn't rotate)

    vector<Position> coords;
    coords.emplace_back(Position {0, 0});
    return coords;
}
