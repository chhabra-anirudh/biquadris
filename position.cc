export module Position;

using namespace std;

export struct Position {
    int row;
    int col;
    // Constructor
    Position(int row = 0, int col = 0);
    // Returns true if this position has the same row and column as the other position
    bool operator==(const Position &other) const;
    // Returns true if this position differs in either row or column from the other position
    bool operator!=(const Position &other) const;
};
