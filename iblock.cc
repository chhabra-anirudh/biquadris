export module IBlock;

import Block;

using namespace std;

export class IBlock : public Block {

    protected:
        vector<Position> getShapeCoordinates() const override;

    public:
        IBlock(int level, bool heavy = false);
};
