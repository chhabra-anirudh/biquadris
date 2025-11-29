module Level;

import <iostream>;
import <fstream>;
import <string>;

import Block;
import IBlock;
import TBlock;
import ZBlock;
import OBlock;
import LBlock;
import JBlock;
import SBlock;
import StarBlock;


using namespace std;

Level::Level(int levelNum, const string& sequence, int seed)
    : levelNum{levelNum}, sequence{sequence}, seed{seed}, isRandom{true} {
        if (!sequence.empty()) {
            filestream.open(sequence);
            if (!filestream) {
                std::cerr << "Error opening sequence file: " << sequence << std::endl;
            }
        }
    }

Level::~Level() {
    if (filestream.is_open()) {
        filestream.close();
    }
}

unique_ptr<Block> Level::createBlock(char type, bool heavy) {
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

void Level::setRandom(bool random) {
    isRandom = random;
}

void Level::setSequenceFile(const string& file) {
    if (filestream.is_open()) {
        filestream.close();
    }
    filestream.open(file);
    if (!filestream) {
        std::cerr << "Error opening sequence file: " << file << std::endl;
    }
}

int Level::getLevelNum() const {
    return levelNum;
}

bool Level::random() const {
    return isRandom;
}
