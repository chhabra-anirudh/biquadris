export module Level;

import <fstream>;
import <memory>;
import <string>;

import Block;

using namespace std;

export class Level {
    protected:
        int levelNum;
        bool isRandom;
        string sequence;
        ifstream filestream;
        int seed;

        unique_ptr<Block> createBlock(char type, bool heavy = false);

    public:
        Level(int levelNum, const string& sequence, int seed);
        virtual ~Level();

        virtual unique_ptr<Block> generateBlock() = 0;

        virtual void setRandom(bool random);
        void setSequenceFile(const string& filename);
        
        int getLevelNum() const;
        bool getIsRandom() const;
};
