export module Level2;

import Level;
import Block;

import <memory>;

using namespace std;

class Level2: public Level {
    public:
        Level2(const string& sequence, int seed);
        unique_ptr<Block> generateBlock() override;
};