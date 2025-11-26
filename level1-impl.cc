module Level1;

import <cstdlib>;

import Level;
import Block;

using namespace std;

Level1::Level1(const string &sequence, int seed)
    : Level{1, sequence, seed} {}

unique_ptr<Block> Level1::createBlock(char type, bool heavy) {
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

unique_ptr<Block> Level1::generateBlock() {
    char type;
    
    int choice = rand() % 12;

    if (choice == 0) {
        type = 'S';
    } else if (choice == 1) {
        type = 'Z';
    } else {
        const char types[] = {'I', 'J', 'L', 'O', 'T'};
        type = types[rand() % 5];
    }
    return createBlock(type);
}