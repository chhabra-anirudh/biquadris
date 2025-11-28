export module Level2;

import Level;
import Block;

import <memory>;

using namespace std;

export class Level2: public Level {
    public:
        // Constructor
        Level2(const string& sequence, int seed);
        // Generates the next block randomly according to Level 2 probabilities
        unique_ptr<Block> generateBlock() override;
};
