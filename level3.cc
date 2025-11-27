export module Level3;

import Level;
import Block;

import <memory>;

using namespace std;

class Level3: public Level {
    public:
        Level3(const string &sequence, int seed);
        unique_ptr<Block> generateBlock() override;
};