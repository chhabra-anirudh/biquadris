export module OBlock;

import Block;

using namespace std;

export class OBlock : public Block {

    protected:
        vector<Position> getShapeCoordinates() const override;

    public:
        OBlock(int level, bool heavy = false);
        void rotateClockwise() override; // O-block doesn't rotate
        void rotateCounterClockwise() override; // O-block doesn't rotate
};
