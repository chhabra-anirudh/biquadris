module Level2;

import <cstdlib>;

import Level;
import Block;

using namespace std;

Level2::Level2(const string &sequence, int seed):
    Level(2, sequence, seed) {}

unique_ptr<Block> Level2::generateBlock() {
    int num = rand() % 7;
    char type;

    if (num == 0) type = 'I';
    else if (num == 1) type = 'J';
    else if (num == 2) type = 'O';
    else if (num == 3) type = 'L';
    else if (num == 4) type = 'S';
    else if (num == 5) type = 'Z';
    else if (num == 6) type = 'T';
    return createBlock(type);
}


