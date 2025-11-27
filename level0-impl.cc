module Level0;

import Block;
import Level;

import <iostream>;
import <fstream>;

using namespace std;

Level0::Level0(const string &sequence, int seed)
    : Level{0, sequence, seed} {}

unique_ptr<Block> Level0::generateBlock() {
    char type;
    if (filestream >> type) {
        return createBlock(type);
    } else {
        filestream.close();
        filestream.open(sequence);

        if (filestream >> type) {
        return createBlock(type);
        }
    }
}
