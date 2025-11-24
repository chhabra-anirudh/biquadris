module TBlock;

import <vector>;
import Block;

using namespace std;

TBlock::TBlock(int level, bool heavy) : Block{'T', level, heavy} {}

vector<Position> TBlock::getShapeCoordinates() const {
    // T-block: TTT    T     T     T
    //           T    TT    TTT    TT
    //                 T           T

    vector<Position> coords;

    if (this->getOrientation() == 0) {
        coords.emplace_back(Position {0, 1});
        coords.emplace_back(Position {1, 0});
        coords.emplace_back(Position {1, 1});
        coords.emplace_back(Position {1, 2});
    }

    else if (this->getOrientation() == 1) {
        coords.emplace_back(Position {0, 1});
        coords.emplace_back(Position {1, 0});
        coords.emplace_back(Position {1, 1});
        coords.emplace_back(Position {2, 1});
    }

    else if (this->getOrientation() == 2) {
        coords.emplace_back(Position {0, 0});
        coords.emplace_back(Position {0, 1});
        coords.emplace_back(Position {0, 2});
        coords.emplace_back(Position {1, 1});
    }

    else {
        coords.emplace_back(Position {0, 0});
        coords.emplace_back(Position {1, 0});
        coords.emplace_back(Position {1, 1});
        coords.emplace_back(Position {2, 0});
    }
    
    return coords;
}
