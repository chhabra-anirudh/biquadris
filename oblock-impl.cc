module OBlock;

import <vector>;
import Block;

using namespace std;

OBlock::OBlock(int level, bool heavy) : Block{'O', level, heavy} {}

vector<Position> OBlock::getShapeCoordinates() const {
    // O-block: OO
    //          OO 

    vector<Position> coords;
    coords.emplace_back(Position {0, 0});
    coords.emplace_back(Position {0, 1});
    coords.emplace_back(Position {1, 0});
    coords.emplace_back(Position {1, 1});
    return coords;
}

void OBlock::rotateClockwise() {}
void OBlock::rotateCounterClockwise() {}
