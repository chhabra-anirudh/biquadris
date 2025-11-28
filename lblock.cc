export module LBlock;

import Position;
import Block;
import <vector>;

using namespace std;

export class LBlock : public Block {

    protected:
        // Returns the coordinates for the I-block shape
        vector<Position> getShapeCoordinates() const override;

    public:
        // Constructor
        LBlock(int level, bool heavy = false);
};
