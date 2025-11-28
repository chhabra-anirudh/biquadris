export module IBlock;

import Position;
import Block;
import <vector>;

using namespace std;

export class IBlock : public Block {

    protected:
        // Returns the coordinates for the I-block shape
        vector<Position> getShapeCoordinates() const override;

    public:
        // Constructor
        IBlock(int level, bool heavy = false);
};
