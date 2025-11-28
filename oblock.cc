export module OBlock;

import Position;
import Block;
import <vector>;

using namespace std;

export class OBlock : public Block {

    protected:
        //Returns the coordinates for the O-Block shape
        vector<Position> getShapeCoordinates() const override;

    public:
        // Constructor
        OBlock(int level, bool heavy = false);
};
