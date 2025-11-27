module Level1;

import <cstdlib>;

import Level;
import Block;

using namespace std;

Level1::Level1(const string &sequence, int seed)
    : Level{1, sequence, seed} {}

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