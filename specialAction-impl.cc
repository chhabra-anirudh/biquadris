module SpecialAction;

import Player;
import <string>;

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
