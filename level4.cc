export module Level4;

import <memory>;
import Block;
import Level;

using namespace std;

export class Level4: public Level {
    int blocks;
    public:
        // Constructor
        Level4(const string &sequence, int seed);
        // Generates the next block randomly according to Level 4 probabilities
        unique_ptr<Block> generateBlock() override;
        // Returns the number of blocks placed so far in Level 4
        int getBlocksPlaced() const;
        // Increments the counter tracking how many blocks have been placed in Level 4
        void incrementBlocksPlaced();
         // Resets the Level 4 block placement counter back to zero
        void resetBlocksPlaced();
};
