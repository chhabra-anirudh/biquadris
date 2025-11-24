export module TBlock;

import Block;

using namespace std;

export class TBlock : public Block {

    protected:
        vector<Position> getShapeCoordinates() const override;

    public:
        TBlock(int level, bool heavy = false);
};
