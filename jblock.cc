export module JBlock;

import Position;
import Block;
import <vector>;

using namespace std;

export class JBlock : public Block {

    protected:
        vector<Position> getShapeCoordinates() const override;

    public:
        JBlock(int level, bool heavy = false);
};
