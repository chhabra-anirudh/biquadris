export module Player;

import Board;
import Level;
import Block;
import <memory>;
import <string>;


using namespace std;

class SpecialAction;

export class Player{
        unique_ptr<Board> board;
        unique_ptr<Block> currentBlock;
        unique_ptr<Block> nextBlock;
        unique_ptr<Level> level;
        int score;
        int currentLevel;
        bool isBlind;
        int heavyEffect;
        int blocksWithoutClear;

    public:
        Player(int startLevel, const string &scriptFile, int seed);
        ~Player() = default; // Smart pointers handle cleanup!

        // Movement commands
        bool moveLeft(int n = 1);
        bool moveRight(int n = 1);
        bool moveDown(int n = 1);
        bool rotate(bool clockwise);
        void drop;

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





