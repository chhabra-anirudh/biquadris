export module Level2;

import Level;
import Block;

import <memory>;

using namespace std;

class Level2: public Level {
    protected:
        unique_ptr<Block> createBlock(char type, bool heavy = false) override;

    public:
        Level2(const string& sequence, int seed);
        unique_ptr<Block> generateBlock() override;
};