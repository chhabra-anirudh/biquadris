export module SpecialAction;

import <string>;

class Player;

using namespace std;

// Interface for special actions
export class SpecialAction {
    public:
        virtual void apply(Player* player) = 0;
        virtual string getName() const = 0;
        virtual ~SpecialAction() = default;
};

// Blind action
class BlindAction : public SpecialAction {
    public:
        void apply(Player* player) override;
        string getName() const override;
};

// Heavy action
class HeavyAction : public SpecialAction {
    public:
        void apply(Player* player) override;
        string getName() const override;
};

// Force action
class ForceAction : public SpecialAction {
        char blockType;
    public:
        ForceAction(char blockType);
        void apply(Player* player) override;
        string getName() const override;
        char getBlockType() const;
};
