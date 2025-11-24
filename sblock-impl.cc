module SBlock;

import <vector>;
import Block;

using namespace std;

SBlock::SBlock(int level, bool heavy) : Block{'S', level, heavy} {}

vector<Position> SBlock::getShapeCoordinates() const {
    // S-block:  SS    S
    //          SS     SS
    //                  S

    vector<Position> coords;

    if (this->getOrientation() % 2 == 0) {
        coords.emplace_back(Position {0, 0});
        coords.emplace_back(Position {0, 1});
        coords.emplace_back(Position {1, 1});
        coords.emplace_back(Position {1, 2});
    }

    else {
        coords.emplace_back(Position {0, 1});
        coords.emplace_back(Position {1, 0});
        coords.emplace_back(Position {1, 1});
        coords.emplace_back(Position {2, 0});
    }
    
    return coords;
}
