export module Level0;

import <memory>;

import Block;
import Level;

using namespace std;

class Level0: public Level {
    public:
        Level0(const string& sequence, int seed);
        unique_ptr<Block> generateBlock() override;
}