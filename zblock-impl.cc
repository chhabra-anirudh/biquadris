module ZBlock;

import <vector>;
import Block;

using namespace std;

ZBlock::ZBlock(int level, bool heavy) : Block{'Z', level, heavy} {}

vector<Position> ZBlock::getShapeCoordinates() const {
    // Z-block:  ZZ     Z
    //            ZZ   ZZ
    //                 Z

    vector<Position> coords;

    if (this->getOrientation() % 2 == 0) {
        coords.emplace_back(Position {0, 1});
        coords.emplace_back(Position {0, 2});
        coords.emplace_back(Position {1, 0});
        coords.emplace_back(Position {1, 1});
    }

    else {
        coords.emplace_back(Position {0, 0});
        coords.emplace_back(Position {1, 0});
        coords.emplace_back(Position {1, 1});
        coords.emplace_back(Position {2, 1});
    }
    
    return coords;
}
