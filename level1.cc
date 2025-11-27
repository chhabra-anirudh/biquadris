export module Level1;

import Level;
import Block;
import <memory>;

using namespace std;


export class Level1: public Level {
    public:
        Level1(const string& sequence, int seed);
        unique_ptr<Block> generateBlock() override;
};