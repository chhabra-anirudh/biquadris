export module StarBlock;

import Block;

using namespace std;

export class StarBlock : public Block {

    protected:
        vector<Position> getShapeCoordinates() const override;

    public:
        StarBlock(int level);
        void rotateClockwise() override; // Star block doesn't rotate
        void rotateCounterClockwise() override; // Star block doesn't rotate
};
