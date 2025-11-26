module Level0;

import Block;
import Level;

import <iostream>;

using namespace std;

Level0::Level0(const string &sequence, int seed)
    : Level{0, sequence, seed} {}

unique_ptr<Block> Level0::createBlock(char type, bool heavy) {
    if (type == 'I') {
        return make_unique<IBlock>(levelNum, heavy);
    } else if (type == 'J') {
        return make_unique<JBlock>(levelNum, heavy);
    } else if (type == 'L') {
        return make_unique<LBlock>(levelNum, heavy);
    } else if (type == 'O') {
        return make_unique<OBlock>(levelNum, heavy);
    } else if (type == 'S') {
        return make_unique<SBlock>(levelNum, heavy);
    } else if (type == 'Z') {
        return make_unique<ZBlock>(levelNum, heavy);
    } else if (type == 'T') {
        return make_unique<TBlock>(levelNum, heavy);
    } else {
        cerr << "Invalid block type: " << type << endl;
        return nullptr;
    }
}

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
//return make_unique<IBlock>(levelNum);
}
