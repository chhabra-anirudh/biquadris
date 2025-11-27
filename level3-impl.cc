module Level3;

import Block;
import Level;

import <cstdlib>;
import <iostream>;
import <string>;

using namespace std;

Level3::Level3(const string &sequence, int seed):
    Level(3, sequence, seed) {}

unique_ptr<Block> Level3::generateBlock() {
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

    int rnum = rand() % 9;
    char type;

    if (rnum < 2) type = 'S';
    else if (rnum < 4) type = 'Z';
    else if (rnum == 4) type = 'O';
    else if (rnum == 5) type = 'I';
    else if (rnum == 6) type = 'J';
    else if (rnum == 7) type = 'L';
    else type == 'T';

    return createBlock(type, true);
}
