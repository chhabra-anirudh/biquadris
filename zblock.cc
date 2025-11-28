export module ZBlock;

import Position;
import Block;
import <vector>;

using namespace std;

export class ZBlock : public Block {

    protected:
         //Returns the coordinates of Z-block shape
        vector<Position> getShapeCoordinates() const override;

    public:
        //Constructor
        ZBlock(int level, bool heavy = false);
};
