module Player;

import Game;
import <iostream>;
import <string>;
import <memory>;
import SpecialAction;
import Level0;
import Level1;
import Level2;
import level3;
import level4;

using namespace std;

Player::Player(int startlevel, const string &scriptfile, int seed)
    : board{make_unique<Board>()},
    level{createLevel(startLevel, scriptFile, seed)},
    score{0}, currentLevel{startlevel}, 
    isBlind{false}, heavyEffect{0}, blocksWithoutClear{0} {
    
    // Generate first two blocks
    nextBlock = level->generateBlock();
    currentBlock = level->generateBlock();

    // Place current block at starting position
    // Rows 15-17 are reserve rows at top
    // Block starts at row 14 (top visible row), column 0
    if (currentBlock) {
        currentBlock->setPosition(Position(14, 0));
    }
}

unique_ptr<Level> Player::createLevel(int levelNum, const string& scriptFile, int seed) {
    if (levelNum == 0) {
        return make_unique<Level0>(scriptFile, seed);

    } else if (levelNum == 1) {
        return make_unique<Level1>(scriptFile, seed);

    } else if (levelNum == 2) {
        return make_unique<Level2>(scriptFile, seed);

    } else if (levelNum == 3) {
        return make_unique<Level3>(scriptFile, seed);

    } else if (levelNum == 4) {
        return make_unique<Level4>(scriptFile, seed);
        
    }
}

void Player::generateNextBlock() {
    nextBlock = level->generateBlock();
}

bool Player::canMove(const Position &newPos) {
    return board->canPlace(currentBlock.get(), newPos.row, newPos.col);
}

bool Player::moveLeft(int n) {
    if (!currentBlock) {
        return false;
    }
    bool moved = false;
    for (int i = 0; i < n; ++i) {
        Position newPos = currentBlock->getPosition();
        newPos.col -= 1;
        
        if (canMove(newPos)) {
            currentBlock->setPosition(newPos);
            moved = true;
        } else {
            break;
        }
    }
    if (moved) {
        applyHeavyDrop();
        board->notifyObservers();
    }
    
    return moved;
}

bool Player::moveRight(int n) {
    if (!currentBlock) return false;
    
    bool moved = false;
    for (int i = 0; i < n; ++i) {
        Position newPos = currentBlock->getPosition();
        newPos.col += 1;
        
        if (canMove(newPos)) {
            currentBlock->setPosition(newPos);
            moved = true;
        } else {
            break;
        }
    }
    
    if (moved) {
        applyHeavyDrop();
        board->notifyObservers();
    }
    
    return moved;
}

bool Player::moveDown(int n) {
    if (!currentBlock) return false;
    
    bool moved = false;
    for (int i = 0; i < n; ++i) {
        Position newPos = currentBlock->getPosition();
        newPos.row -= 1;
        
        if (canMove(newPos)) {
            currentBlock->setPosition(newPos);
            moved = true;
        } else {
            break;
        }
    }
    
    if (moved) {
        board->notifyObservers();
    }
    
    return moved;
}

bool Player::rotate(bool clockwise) {
    if (!currentBlock) return false;
    
    // Try rotation
    if (clockwise) {
        currentBlock->rotateClockwise();
    } else {
        currentBlock->rotateCounterClockwise();
    }
    
    // Check if rotation is valid
    Position currentPos = currentBlock->getPosition();
    if (!canMove(currentPos)) {
        // Undo rotation
        if (clockwise) {
            currentBlock->rotateCounterClockwise();
        } else {
            currentBlock->rotateClockwise();
        }
        return false;
    }
    
    applyHeavyDrop(true); // changed added a parameter
    board->notifyObservers();
    return true;
}

void Player::applyHeavyDrop(bool rotateOn) {
    if (!currentBlock) {
        return;
    }
    int totalDrops = 0;
    if (rotateOn) {
        totalDrops = (currentBlock->heavy() ? 1 : 0)
    } else {
        totalDrops = (currentBlock->heavy() ? 1 : 0) + heavyEffect;
    }
    
    for (int i = 0; i < totalDrops; ++i) {
        Position newPos = currentBlock->getPosition();
        newPos.row -= 1;
        
        if (canMove(newPos)) {
            currentBlock->setPosition(newPos);
        } else {
            // Can't drop furthur, so drop the block immediately
            drop();
            return;
        }
    }
}

void Player::drop() {
    if (!currentBlock) {
        return;
    }
    // Drop block as far as possible
    while (true) {
        Position newPos = currentBlock->getPosition();
        newPos.row -= 1;
        
        if (canMove(newPos)) {
            currentBlock->setPosition(newPos);
        } else {
            break;
        }
    }
    
    // Place block on board
    bool placed = board->placeBlock(currentBlock.get());
    
    if (!placed) {
        // Game over - block couldn't be placed
        return;
    }
    
    // Clear any full rows
    int rowsCleared = board->clearFullRows();
    
    if (rowsCleared > 0) {
        // Calculate score for clearing rows
        int rowScore = (currentLevel + rowsCleared) * (currentLevel + rowsCleared);
        score += rowScore;
        blocksWithoutClear = 0;
    } else {
        blocksWithoutClear++;
        
        // Level 4: Drop star block every 5 blocks without clearing
        if (currentLevel == 4 && blocksWithoutClear > 0 && blocksWithoutClear % 5 == 0) {
            board->dropStarBlock();
        }
    }
    
    // Check if block is fully cleared - add bonus score
    if (!currentBlock->isFilled()) {
        int blockScore = (currentBlock->getLevel() + 1) * (currentBlock->getLevel() + 1);
        score += blockScore;
    }
    
    // Clear blind effect after dropping
    isBlind = false;
    
    // Move to next block - use std::move to transfer ownership
    currentBlock = std::move(nextBlock);
    nextBlock = level->generateBlock();
    
    // Position new block
    if (currentBlock) {
        currentBlock->setPosition(Position(14, 0));
    }
    
    board->notifyObservers();
}

void Player::levelUp() {
    if (currentLevel < 4) {
        setLevel(currentLevel + 1);
    }
}

void Player::levelDown() {
    if (currentLevel > 0) {
        setLevel(currentLevel - 1);
    }
}

void Player::setLevel(int newLevel) {
    if (newLevel < 0 || newLevel > 4) {
        return;
    }
    
    currentLevel = newLevel;
    
    // Get sequence file from old level
    string seqFile = "";
    int seed = 0;
    
    level = createLevel(newLevel, seqFile, seed);
}

void Player::setNoRandom(const string& file) {
    level->setRandom(false);
    level->setSequenceFile(file);
}

void Player::setRandom() {
    level->setRandom(true);
}

void Player::applySpecialAction(SpecialAction* action) {
    action->apply(this);
}

void Player::setBlind(bool blind) {
    isBlind = blind;
}

void Player::incrementHeavyEffect() {
    heavyEffect += 2;
}

void Player::forceBlock(char type) {
    // Replace next block with specified type
    bool heavy = (currentLevel >= 3);

    if ('I' == type) {
        nextBlock = make_unique<IBlock>(currentLevel, heavy);
        return;

    } else if ('J' == type) {
        nextBlock = make_unique<JBlock>(currentLevel, heavy);
        return;

    } else if ('L' == type) {
        nextBlock = make_unique<LBlock>(currentLevel, heavy);
        return;

    } else if ('O' == type) {
        nextBlock = make_unique<OBlock>(currentLevel, heavy);
        return;

    } else if ('S' == type) {
        nextBlock = make_unique<SBlock>(currentLevel, heavy);
        return;

    } else if ('Z' == type) {
        nextBlock = make_unique<ZBlock>(currentLevel, heavy);
        return;

    } else if ('T' == type) {
        nextBlock = make_unique<TBlock>(currentLevel, heavy);
        return;
    }
}

void Player::replaceBlock(char type) {
    if (currentBlock && !currentBlock->placed()) {
        Position pos = currentBlock->getPosition();
        
        bool heavy = currentLevel >= 3;
        
        if ('I' == type) {
            nextBlock = make_unique<IBlock>(currentLevel, heavy);
            return;

        } else if ('J' == type) {
            nextBlock = make_unique<JBlock>(currentLevel, heavy);
            return;

        } else if ('L' == type) {
            nextBlock = make_unique<LBlock>(currentLevel, heavy);
            return;

        } else if ('O' == type) {
            nextBlock = make_unique<OBlock>(currentLevel, heavy);
            return;

        } else if ('S' == type) {
            nextBlock = make_unique<SBlock>(currentLevel, heavy);
            return;

        } else if ('Z' == type) {
            nextBlock = make_unique<ZBlock>(currentLevel, heavy);
            return;

        } else if ('T' == type) {
            nextBlock = make_unique<TBlock>(currentLevel, heavy);
            return;
        }
        
        if (currentBlock) {
            currentBlock->setPosition(pos);
        }
    }
    
    board->notifyObservers();
}

Board* Player::getBoard() const { return board.get(); }
Block* Player::getCurrentBlock() const { return currentBlock.get(); }
Block* Player::getNextBlock() const { return nextBlock.get(); }
int Player::getScore() const { return score; }
int Player::getLevel() const { return currentLevel; }
bool Player::blind() const { return isBlind; }
int Player::getHeavyEffect() const { return heavyEffect; }
int Player::getBlocksWithoutClear() const { return blocksWithoutClear; }

void Player::addScore(int points) {
    score += points;
}

void Player::setScore(int newScore) {
    score = newScore;
}

bool Player::isGameOver() const {
    // Game over if current block can't fit at starting position
    if (!currentBlock) return false;
    return (!board->canPlace(currentBlock.get(), 14, 0));
}

void Player::reset() {
    // Clear board - create new one
    board = std::make_unique<Board>();
    
    // Clear all blocks (automatically deletes them)
    allBlocks.clear();
    
    // Generate new blocks
    nextBlock = level->generateBlock();
    currentBlock = level->generateBlock();
    if (currentBlock) {
        currentBlock->setPosition(Position(14, 0));
    }
    
    // Reset state
    score = 0;
    isBlind = false;
    heavyEffect = 0;
    blocksWithoutClear = 0;
}
