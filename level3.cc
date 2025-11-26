export module Level3;

import Level;
import Block;

import <memory>;

using namespace std;

class Level3: public Level {
    protected:
        unique_ptr<Block> createBlock(char type, bool heavy = false) override;
        
    public:
        Level3(const string &sequence, int seed);
        unique_ptr<Block> generateBlock() override;
};