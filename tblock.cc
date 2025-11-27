export module TBlock;

import Position;
import Block;
import <vector>;

using namespace std;

export class TBlock : public Block {

    protected:
        vector<Position> getShapeCoordinates() const override;

    public:
        TBlock(int level, bool heavy = false);
};
