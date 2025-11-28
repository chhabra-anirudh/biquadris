module Player;

import <iostream>;
import <string>;
import <memory>;
// import SpecialAction;
import Level0;
import Level1;
import Level2;
import Level3;
import Level4;
import <vector>;
import <utility>;

using namespace std;

// BlindAction
void BlindAction::apply(Player* player) {
    player->setBlind(true);
}

string BlindAction::getName() const {
    return "blind";
}

// HeavyAction
void HeavyAction::apply(Player* player) {
    player->incrementHeavyEffect();
}

string HeavyAction::getName() const {
    return "heavy";
}

// ForceAction
ForceAction::ForceAction(char blockType) : blockType{blockType} {}

void ForceAction::apply(Player* player) {
    player->forceBlock(blockType);
}

string ForceAction::getName() const {
    return "force";
}

char ForceAction::getBlockType() const {
    return blockType;
}


Player::Player(int startLevel, const string &scriptFile, int seed)
    : board{make_unique<Board>()}, 
      level{createLevel(startLevel, scriptFile, seed)},
      score{0}, currentLevel{startLevel}, 
      isBlind{false}, heavyEffect{0}, blocksWithoutClear{0}, lastRowsCleared{0},
      sequenceFile{scriptFile}, seed{seed}, isRandom{true} {
    
    // Generate first two blocks
    currentBlock = level->generateBlock();
    nextBlock = level->generateBlock();
    
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
    // Default to level 0 if invalid level number
    return make_unique<Level0>(scriptFile, seed);
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
    if (!currentBlock) {
        return false;
    }
    
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
    if (!currentBlock) {
        return false;
    }
    
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

bool Player::rotate(bool clockwise, int multiplier) {
    bool success = false;
    for (int i = 0; i < multiplier; ++i) {
        if (!currentBlock) {
            return false;
        }
        
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
            return success;
        }
        
        success = true;
        applyHeavyDrop(true); 
    }
    board->notifyObservers();
    return success;
}

void Player::applyHeavyDrop(bool rotateOn) {
    if (!currentBlock) {
        return;
    }
    int totalDrops = 0;
    if (rotateOn) {
        totalDrops = (currentBlock->heavy() ? 1 : 0);
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
            dropOnce();
            return;
        }
    }
}

void Player::drop(int multiplier) {
    for (int i = 0; i < multiplier; ++i) {
        dropOnce();
    }
}

void Player::dropOnce() {
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
        // Clear currentBlock to indicate game over state
        currentBlock.reset();
        board->notifyObservers();
        return;
    }
    // Move currentBlock to allBlocks vector (Player keeps ownership)
    allBlocks.push_back(std::move(currentBlock));
    // Clear any full rows
    int rowsCleared = board->clearFullRows();
    lastRowsCleared = rowsCleared;  // Track for special actions
    if (rowsCleared > 0) {
        // Calculate score for clearing rows
        int rowScore = (currentLevel + rowsCleared) * (currentLevel + rowsCleared);
        score += rowScore;
        blocksWithoutClear = 0;

        // Check for bonus score from fully cleared blocks
        for (const auto& block : allBlocks) {
            if (!block->isFilled() && !block->hasScored()) {
                int blockScore = (block->getLevel() + 1);
                score += blockScore * blockScore;
                block->setScored();
            }
        }

    } else {
        blocksWithoutClear++;
        
        // Level 4: Drop star block every 5 blocks without clearing
        if (currentLevel == 4 && blocksWithoutClear > 0 && blocksWithoutClear % 5 == 0) {
            // Create star block and take ownership
            Block* starRaw = board->createStarBlock();
            unique_ptr<Block> star(starRaw);  // Wrap in unique_ptr
            board->placeBlock(star.get());
            allBlocks.push_back(std::move(star));  // Store in allBlocks
        }
    }
    
    // Clear blind effect after dropping
    isBlind = false;
    
    // Move to next block - use std::move to transfer ownership
    currentBlock = std::move(nextBlock);
    nextBlock = level->generateBlock();
    
    // Handle case where generateBlock returns nullptr (shouldn't happen with fixes, but safety check)
    if (!nextBlock) {
        // Retry generating a block - if still fails, we'll handle it below
        nextBlock = level->generateBlock();
    }
    
    // Position new block
    if (currentBlock) {
        currentBlock->setPosition(Position(14, 0));
    } else {
        // If currentBlock is null (shouldn't happen), try to generate a new one
        currentBlock = level->generateBlock();
        if (currentBlock) {
            currentBlock->setPosition(Position(14, 0));
        }
    }
    
    board->notifyObservers();
}

int Player::getLastRowsCleared() const {
    return lastRowsCleared;
}

void Player::levelUp(int multiplier) {
    for (int i = 0; i < multiplier && currentLevel < 4; ++i) {
        setLevel(currentLevel + 1);
    }
}

void Player::levelDown(int multiplier) {
    for (int i = 0; i < multiplier && currentLevel > 0; ++i) {
        setLevel(currentLevel - 1);
    }
}

void Player::setLevel(int newLevel) {
    if (newLevel < 0 || newLevel > 4) {
        return;
    }
    
    // Preserve random state from old level before destroying it
    if (level) {
        isRandom = level->random();
    }
    
    currentLevel = newLevel;
    
    // Use stored sequence file and seed when creating new level
    level = createLevel(newLevel, sequenceFile, seed);
    
    // Restore random state
    if (level) {
        level->setRandom(isRandom);
        if (!isRandom && !sequenceFile.empty()) {
            level->setSequenceFile(sequenceFile);
        }
    }
}

void Player::setNoRandom(const string& file) {
    level->setRandom(false);
    level->setSequenceFile(file);
    isRandom = false;
    sequenceFile = file;  // Update stored sequence file
}

void Player::setRandom() {
    level->setRandom(true);
    isRandom = true;
}

void Player::applySpecialAction(SpecialAction* action) {
    action->apply(this);
}

void Player::setBlind(bool blind) {
    isBlind = blind;
    if (board) {
        board->notifyObservers();
    }
}

void Player::incrementHeavyEffect() {
    heavyEffect += 2;
}

void Player::forceBlock(char type) {
    // Replace current block with specified type (not next block)
    if (currentBlock && !currentBlock->placed()) {
        // Save the current position of the undropped block
        Position currentPos = currentBlock->getPosition();
        
    bool heavy = (currentLevel >= 3);

    if ('I' == type) {
            currentBlock = make_unique<IBlock>(currentLevel, heavy);
    } else if ('J' == type) {
            currentBlock = make_unique<JBlock>(currentLevel, heavy);
    } else if ('L' == type) {
            currentBlock = make_unique<LBlock>(currentLevel, heavy);
    } else if ('O' == type) {
            currentBlock = make_unique<OBlock>(currentLevel, heavy);
    } else if ('S' == type) {
            currentBlock = make_unique<SBlock>(currentLevel, heavy);
        } else if ('Z' == type) {
            currentBlock = make_unique<ZBlock>(currentLevel, heavy);
        } else if ('T' == type) {
            currentBlock = make_unique<TBlock>(currentLevel, heavy);
        } else {
            // Invalid block type, don't replace
        return;
        }
        
        // Place the new block at the same position as the old block
        if (currentBlock) {
            currentBlock->setPosition(currentPos);
            currentBlock->setPlaced(false);  // Ensure it's not marked as placed
        }
        
        board->notifyObservers();
    }
}

void Player::replaceBlock(char type) {
    if (currentBlock && !currentBlock->placed()) {
        // Save the current position of the undropped block
        Position currentPos = currentBlock->getPosition();
        
        bool heavy = currentLevel >= 3;
        
        // Create new block of specified type
        if ('I' == type) {
            currentBlock = make_unique<IBlock>(currentLevel, heavy);
        } else if ('J' == type) {
            currentBlock = make_unique<JBlock>(currentLevel, heavy);
        } else if ('L' == type) {
            currentBlock = make_unique<LBlock>(currentLevel, heavy);
        } else if ('O' == type) {
            currentBlock = make_unique<OBlock>(currentLevel, heavy);
        } else if ('S' == type) {
            currentBlock = make_unique<SBlock>(currentLevel, heavy);
        } else if ('Z' == type) {
            currentBlock = make_unique<ZBlock>(currentLevel, heavy);
        } else if ('T' == type) {
            currentBlock = make_unique<TBlock>(currentLevel, heavy);
        } else {
            // Invalid block type, don't replace
            return;
        }
        
        // Place the new block at the same position as the old block
        if (currentBlock) {
            currentBlock->setPosition(currentPos);
            currentBlock->setPlaced(false);  // Ensure it's not marked as placed
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
    if (!currentBlock) {
        return false;
    }
    return (!board->canPlace(currentBlock.get(), 14, 0));
}

void Player::reset() {
    // Clear board - create new one
    board = make_unique<Board>();
    
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
    lastRowsCleared = 0;
}
