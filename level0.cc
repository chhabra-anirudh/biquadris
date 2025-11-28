export module Level0;

import Block;
import Level;

import <memory>;

using namespace std;

export class Level0 : public Level {
    public:
        // Constructor
        Level0(const string& sequence, int seed);
        // Generates the next block strictly from the sequence file 
        unique_ptr<Block> generateBlock() override;
};
