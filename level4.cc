export module Level4;

import <memory>;
import Block;
import Level;

using namespace std;

export class Level4: public Level {
    int blocks;
    public:
        Level4(const string &sequence, int seed);
        unique_ptr<Block> generateBlock() override;

        int getBlocksPlaced() const;
        void incrementBlocksPlaced();
        void resetBlocksPlaced();
};