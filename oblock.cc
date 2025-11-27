export module OBlock;

import Position;
import Block;
import <vector>;

using namespace std;

export class OBlock : public Block {

    protected:
        vector<Position> getShapeCoordinates() const override;

    public:
        OBlock(int level, bool heavy = false);
};
