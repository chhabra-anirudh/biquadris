export module TBlock;

import Position;
import Block;
import <vector>;

using namespace std;

export class TBlock : public Block {

    protected:
        // Returns the coordinates of T-block shape
        vector<Position> getShapeCoordinates() const override;

    public:
        // Constructor
        TBlock(int level, bool heavy = false);
};
