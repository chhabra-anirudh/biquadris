module Level;

import <iostream>;
import <fstream>;
import <string>;

import Block;

Level::Level(int levelNum, string& sequence, int seed)
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

bool Level::getIsRandom() const {
    return isRandom;
}