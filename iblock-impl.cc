module IBlock;

import <vector>;
import Block;

using namespace std;

IBlock::IBlock(int level, bool heavy) : Block{'I', level, heavy} {}

vector<Position> IBlock::getShapeCoordinates() const {
    // I-block rotates between horizontal and vertical
    // Orientation 0 & 2: Horizontal (IIII)
    // Orientation 1 & 3: Vertical

    vector<Position> coords;

    if (this->getOrientation() % 2 == 0) {
        // Horizontal: IIII
        // Reference point is leftmost cell at bottom
        coords.emplace_back(Position {0, 0});
        coords.emplace_back(Position {0, 1});
        coords.emplace_back(Position {0, 2});
        coords.emplace_back(Position {0, 3});
    }

    else {
        // Vertical:
        // I
        // I
        // I
        // I
        coords.emplace_back(Position {0, 0});
        coords.emplace_back(Position {1, 0});
        coords.emplace_back(Position {2, 0});
        coords.emplace_back(Position {3, 0});
    }
    
    return coords;
}
