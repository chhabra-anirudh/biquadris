export module SBlock;

import Position;
import Block;
import <vector>;

using namespace std;

export class SBlock : public Block {

    protected:
        vector<Position> getShapeCoordinates() const override;

    public:
        SBlock(int level, bool heavy = false);
};
