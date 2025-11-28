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
        // Creates and returns a specific Block subclass based on the given type

    public:
        //Constructor
        Level(int levelNum, const string& sequence, int seed);
        //Destuctor
        virtual ~Level();
        // Makes the class abstract
        virtual unique_ptr<Block> generateBlock() = 0;
        //Enables or disables random block generation
        virtual void setRandom(bool random);
        // Sets and opens a new sequence file for scripted block generation
        void setSequenceFile(const string& filename);
         // Returns the current level number
        int getLevelNum() const;
        // Returns whether the level is using random block generation
        bool random() const;
};
