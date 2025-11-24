export module ZBlock;

import Block;

using namespace std;

export class ZBlock : public Block {

    protected:
        vector<Position> getShapeCoordinates() const override;

    public:
        ZBlock(int level, bool heavy = false);
};
