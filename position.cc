export module Position;

using namespace std;

export struct Position {
    int row;
    int col;

    Position(int row = 0, int col = 0);

    bool operator==(const Position &other) const;
    bool operator!=(const Position &other) const;
};
