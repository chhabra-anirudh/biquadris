module Level2;

import <cstdlib>;

import Level;
import Block;

using namespace std;

Level2::Level2(const string &sequence, int seed):
    Level(2, sequence, seed) {}

unique_ptr<Block> Level2::createBlock(char type, bool heavy) {
    if (type == 'I') return make_unique<IBlock>(levelNum, heavy);
    else if (type == 'J') return make_unique<JBlock>(levelNum, heavy);
    else if (type == 'O') return make_unique<OBlock>(levelNum, heavy);
    else if (type == 'L') return make_unique<LBlock>(levelNum, heavy);
    else if (type == 'S') return make_unique<SBlock>(levelNum, heavy);
    else if (type == 'Z') return make_unique<ZBlock>(levelNum, heavy);
    else if (type == 'T') return make_unique<TBlock>(levelNum, heavy);
    else return nullptr;
}

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


