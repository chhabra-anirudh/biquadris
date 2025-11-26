export module Level4;

import <memory>;
import Block;
import Level;

using namespace std;

class Level4: public Level {
    int blocks;
    protected:
        unique_ptr<Block> createBlock(char type, bool heavy = false) override;
    public:
        Level4(const string &sequence, int seed);
        unique_ptr<Block> generateBlock() override;

        int getBlocks() const;
        void addBlocks();
        void resetBlocks();
};