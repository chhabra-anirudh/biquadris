export module LBlock;

import Position;
import Block;
import <vector>;

using namespace std;

export class LBlock : public Block {

    protected:
        vector<Position> getShapeCoordinates() const override;

    public:
        LBlock(int level, bool heavy = false);
};
