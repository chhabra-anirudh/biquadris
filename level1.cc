export module Level1;

import Level;
import Block;
import <memory>;

using namespace std;


export class Level1: public Level {
    public:
        // Constructor 
        Level1(const string& sequence, int seed);
        // Generates the next block randomly accoding to level 1 probablities 
        unique_ptr<Block> generateBlock() override;
};
