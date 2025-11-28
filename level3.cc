export module Level3;

import Level;
import Block;

import <memory>;

using namespace std;

export class Level3: public Level {
    public:
        //Constructor
        Level3(const string &sequence, int seed);
        // Generates the next block randomly according to Level 3 probabilities
        unique_ptr<Block> generateBlock() override;
};
