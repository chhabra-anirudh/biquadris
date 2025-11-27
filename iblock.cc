export module IBlock;

import Position;
import Block;
import <vector>;

using namespace std;

export class IBlock : public Block {

    protected:
        vector<Position> getShapeCoordinates() const override;

    public:
        IBlock(int level, bool heavy = false);
};
