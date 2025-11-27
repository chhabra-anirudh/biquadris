export module StarBlock;

import Position;
import Block;
import <vector>;

using namespace std;

export class StarBlock : public Block {

    protected:
        vector<Position> getShapeCoordinates() const override;

    public:
        StarBlock(int level);
};
