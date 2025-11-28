export module StarBlock;

import Position;
import Block;
import <vector>;

using namespace std;

export class StarBlock : public Block {

    protected:
         // Returns the coordinates of the starblock shape
        vector<Position> getShapeCoordinates() const override;

    public:
        // Constructor
        StarBlock(int level);
};
