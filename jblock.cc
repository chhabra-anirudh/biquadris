export module JBlock;

import Block;

using namespace std;

export class JBlock : public Block {

    protected:
        vector<Position> getShapeCoordinates() const override;

    public:
        JBlock(int level, bool heavy = false);
};
