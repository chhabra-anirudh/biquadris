export module SBlock;

import Position;
import Block;
import <vector>;

using namespace std;

export class SBlock : public Block {

    protected:
        //Returns the coordintes of S-block shape
        vector<Position> getShapeCoordinates() const override;

    public:
        // Constructor
        SBlock(int level, bool heavy = false);
};
