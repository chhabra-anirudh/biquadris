export module Player;

import <memory>;
import <string>;
import <vector>;
import Position;
import Board;
import Level;
import Block;
import Block;
import IBlock;
import TBlock;
import ZBlock;
import OBlock;
import LBlock;
import JBlock;
import SBlock;
import StarBlock;
export class Player;

using namespace std;

// class SpecialAction;
export class SpecialAction {
    public:
        //Pure virtual apply function
        virtual void apply(Player* player) = 0;
        //Pure virtual getname function
        virtual string getName() const = 0;
        // default destructor
        virtual ~SpecialAction() = default;
};

// Blind action
export class BlindAction : public SpecialAction {
    public:
        // Applies the blind effect to the player
        void apply(Player* player) override;
         // Returns the name of the heavy action
        string getName() const override;
};

// Heavy action
export class HeavyAction : public SpecialAction {
    public:
        // Applies the heavy action to the player
        void apply(Player* player) override;
        // Returns the name of the heavy action
        string getName() const override;
};

// Force action
export class ForceAction : public SpecialAction {
        char blockType;
    public:
        // Constructor
        ForceAction(char blockType);
        // Applies the Force effect to the player
        void apply(Player* player) override;
         // Returns the name of the force action
        string getName() const override;
        // Returns the type of block
        char getBlockType() const;
};


export class Player{
        unique_ptr<Board> board;
        unique_ptr<Block> currentBlock;
        unique_ptr<Block> nextBlock;
        unique_ptr<Level> level;
        vector<unique_ptr<Block>> allBlocks;  // All blocks ever created (Player owns them all)
        int score;
        int currentLevel;
        bool isBlind;
        int heavyEffect;
        int blocksWithoutClear;
        int lastRowsCleared;
        string sequenceFile;  // Store sequence file for level changes
        int seed;  // Store seed for level changes
        bool isRandom;  // Store random state for level changes

    public:
        // Constructor
        Player(int startLevel, const string &scriptFile, int seed);
        // Default destructor
        ~Player() = default; 

        // Movement commands
        bool moveLeft(int n = 1);
        bool moveRight(int n = 1);
        bool moveDown(int n = 1);
        bool rotate(bool clockwise, int multiplier = 1);
        void drop(int multiplier = 1);

        //Level management
        void levelUp(int multiplier = 1);
        void levelDown(int multiplier = 1);
        void setLevel(int newLevel);
        void setNoRandom(const string &file);
        void setRandom();

        // Special actions
        void applySpecialAction(SpecialAction* action);
        void setBlind(bool blind);
        void incrementHeavyEffect();
        void forceBlock(char type);

        // Replace current block with specific type (for testing)
        void replaceBlock(char type);

        // Accessors
        Board* getBoard() const;
        Block* getCurrentBlock() const;
        Block* getNextBlock() const;
        int getScore() const;
        int getLevel() const;
        bool blind() const;
        int getHeavyEffect() const;
        int getBlocksWithoutClear() const;
        int getLastRowsCleared() const;
         
        // Score management
        void addScore(int points);
        void setScore(int newScore);
    
        // Game state
        bool isGameOver() const;
        void reset();
    
    private:
        //Generates the next block for the player
        void generateNextBlock();
        //Returns bool whether the current block of the player can move to newPos
        bool canMove(const Position& newPos);
        // Applies the heavy drop for a block
        void applyHeavyDrop(bool rotateOn = false);
        // Drops a single block (internal helper)
        void dropOnce();
        // Creates and returns a Level object corresponding to the given level number
        unique_ptr<Level> createLevel(int levelNum, const string &scriptFile, int seed);
};
