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
        virtual void apply(Player* player) = 0;
        virtual string getName() const = 0;
        virtual ~SpecialAction() = default;
};

// Blind action
export class BlindAction : public SpecialAction {
    public:
        void apply(Player* player) override;
        string getName() const override;
};

// Heavy action
export class HeavyAction : public SpecialAction {
    public:
        void apply(Player* player) override;
        string getName() const override;
};

// Force action
export class ForceAction : public SpecialAction {
        char blockType;
    public:
        ForceAction(char blockType);
        void apply(Player* player) override;
        string getName() const override;
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

    public:
        Player(int startLevel, const string &scriptFile, int seed);
        ~Player() = default; // Smart pointers handle cleanup!

        // Movement commands
        bool moveLeft(int n = 1);
        bool moveRight(int n = 1);
        bool moveDown(int n = 1);
        bool rotate(bool clockwise);
        void drop();

        //Level management
        void levelUp();
        void levelDown();
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
        void generateNextBlock();
        bool canMove(const Position& newPos);
        void applyHeavyDrop(bool rotateOn = false);
        unique_ptr<Level> createLevel(int levelNum, const string &scriptFile, int seed);
};
