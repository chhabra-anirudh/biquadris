export module JBlock;

import Position;
import Block;
import <vector>;

using namespace std;

export class JBlock : public Block {

    protected:
        // Returns the coordinates for the I-block shape
        vector<Position> getShapeCoordinates() const override;

    public:
        // Constructor
        JBlock(int level, bool heavy = false);
};
