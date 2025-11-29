export module GraphicsDisplay;

import <vector>;
import <memory>;
import Position;
import Block;
import Board;
import Player;
import Observer;
import XWindow;

using namespace std;

export class GraphicsDisplay: public Observer {
    static const int CELL_SIZE = 20;
    static const int BOARD_WIDTH = 11;
    static const int BOARD_HEIGHT = 15;
    static const int BOARD_OFFSET_X = 50;
    static const int BOARD1_OFFSET_Y = 100;
    static const int BOARD2_OFFSET_X = 350;
    
    std::unique_ptr<Xwindow> xw;
    Board* board1;
    Board* board2;
    Player* player1;
    Player* player2;
    int hiScore;
    
    // Returns the display color for a given block type
    int getBlockColor(char blockType) const;
    // Draws a single colored cell in the window
    void drawCell(int x, int y, int color);
    // Draws the full board for the given board num
    void drawBoard(int boardNum);
     // Draws the borders around both boards
    void drawBorders();
    // Draws player info, scores, and hi-score text
    void drawInfo();
    // Draws the next block preview for a player
    void drawNextBlock(Player* player, int x, int y);
    
public:
    // Constructor
    GraphicsDisplay(Board* b1, Board* b2, Player* p1, Player* p2);
    // Destructor
    ~GraphicsDisplay();
    // Redraws the entire graphical display when a board update occurs
    void notify() override;
    // Updates the hi-score value show in the display
    void setHiScore(int score);
    // Updates the boards
    void updateBoards(Board* b1, Board* b2);
};
