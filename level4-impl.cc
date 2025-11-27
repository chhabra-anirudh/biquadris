module Level4;

import Block;
import Level;

import <cstdlib>;
import <iostream>;

using namespace std;

Level4::Level4(const string &sequence, int seed):
    Level(4, sequence, seed), blocks{0} {}

unique_ptr<Block> Level4::generateBlock(char type, bool heavy) {
        if (!isRandom) {
        char blockType;
        if (filestream >> blockType) {
            return createBlock(blockType, true);
        } else {
            filestream.close();
            filestream.open(sequence);
            if (filestream >> blockType) {
                return createBlock(blockType, true);
            } else {
                cerr << "Error: Sequence file is empty" << endl;
            }
        }
    }

    int num = rand() % 9;
    char type;

    if (r < 2) type = 'S';
    else if (r < 4) type = 'Z';
    else if (r == 4) type = 'O';
    else if (r == 5) type = 'I';
    else if (r == 6) type = 'J';
    else if (r == 7) type = 'L';
    else type == 'T';

    return createBlock(type, true);
}

int Level4:: getBlocks() const {
    return blocks;
}

void Level4::incrementBlocks() {
    return ++blocks;
}

void Level4::resetBlocks() {
    blocks = 0;
}




