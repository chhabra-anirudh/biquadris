export module LBlock;

import Block;

using namespace std;

export class LBlock : public Block {

    protected:
        vector<Position> getShapeCoordinates() const override;

    public:
        LBlock(int level, bool heavy = false);
};
