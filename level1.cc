export module Level1;

import Level;
import <memory>;

using namespace std;


class Level1: public Level {
    protected:
        unique_ptr<Block> createBlock(char type, bool heavy = false) override;

    public:
        Level1(const string& sequence, int seed);
        unique_ptr<Block> generateBlock() override;
};