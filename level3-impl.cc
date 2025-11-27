module Level3;

import Block;
import Level;

import <ctsdlib>;
import <iostream>;

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

    if (r < 2) type = 'S';
    else if (r < 4) type = 'Z';
    else if (r == 4) type = 'O';
    else if (r == 5) type = 'I';
    else if (r == 6) type = 'J';
    else if (r == 7) type = 'L';
    else type == 'T';

    return createBlock(type, true);
}
