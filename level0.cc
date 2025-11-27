export module Level0;

import Block;
import Level;

import <memory>;

using namespace std;

export class Level0 : public Level {
    public:
        Level0(const string& sequence, int seed);
        unique_ptr<Block> generateBlock() override;
};