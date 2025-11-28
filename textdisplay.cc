export module TextDisplay;

import <iostream>;
import Position;
import Observer;
import Board;
import Player;

using namespace std;

export class TextDisplay: public Observer {
        static const int ROW_COUNT = 18;
        static const int COL_COUNT = 11;

        char grid1[ROW_COUNT][COL_COUNT];
        char grid2[ROW_COUNT][COL_COUNT];

        Board* board1;
        Board* board2;
        Player* player1;
        Player* player2;
        int hiScore;
        // Updates the given text grid using placed blocks and the current active block
        void updateGrid(char grid[ROW_COUNT][COL_COUNT], Board* board1, Player *player);
        // Draws one player's grid, score, and level to the output stream
        void drawGrid(ostream& out, char grid[ROW_COUNT][COL_COUNT], Player *player, int playerNum);
    
    public:
        // Constructor
        TextDisplay(Board *b1, Board *b2, Player *p1, Player *p2);
        // Updates both text grids when the boards change
        void notify() override;
        // Outputs the current text-based game state to the given stream
        void display(ostream &out);
        // Updates the hi-score value displayed in the output
        void setHiScore(int score);
        void updateBoards(Board *b1, Board *b2);

};
