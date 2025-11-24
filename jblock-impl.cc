module JBlock;

import <vector>;
import Block;

using namespace std;

JBlock::JBlock(int level, bool heavy) : Block{'J', level, heavy} {}

vector<Position> JBlock::getShapeCoordinates() const {
    // J-block: J      JJ     JJJ     J
    //          JJJ    J        J     J
    //                 J             JJ

    vector<Position> coords;

    if (this->getOrientation() == 0) {
        coords.emplace_back(Position {0, 0});
        coords.emplace_back(Position {0, 1});
        coords.emplace_back(Position {0, 2});
        coords.emplace_back(Position {1, 0});
    }

    else if (this->getOrientation() == 1) {
        coords.emplace_back(Position {0, 0});
        coords.emplace_back(Position {1, 0});
        coords.emplace_back(Position {2, 0});
        coords.emplace_back(Position {2, 1});
    }

    else if (this->getOrientation() == 2) {
        coords.emplace_back(Position {0, 2});
        coords.emplace_back(Position {1, 0});
        coords.emplace_back(Position {1, 1});
        coords.emplace_back(Position {1, 2});
    }

    else {
        coords.emplace_back(Position {0, 0});
        coords.emplace_back(Position {0, 1});
        coords.emplace_back(Position {1, 1});
        coords.emplace_back(Position {2, 1});
    }
    
    return coords;
}
