export module TextDisplay;

import Observer;
import <iostream>;
import Board;
import Player;

using namespace std;

export class TextDisplay: public Observer {
        static const int ROW_COUNT = 18;
        static const int COL_COUNT = 11;

        char grid1[ROW_COUNT][COL_COUNT];
        char grid2[ROW_COUNT][COL_COUNT];

        board* board1;
        Board* board2;
        Player* player1;
        Player* player2;

        void updateGrid(char grid[ROW_COUNT][COL_COUNT], board* board1, Player *player);
        void drawGrid(ostream& out, char grid[ROW_COUNT][COL_COUNT], Player *player, int playerNum);
    
    public:
        TextDisplay(Board *b1, Board *b2, Player *p1, Player *p2);

        void notify() override;
        void displat(ostream &out);

}
