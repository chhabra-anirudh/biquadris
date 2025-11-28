export module GraphicsDisplay;

import <vector>;
import Position;
import Block;
import Board;
import Player;
import Observer;
import XWindow;
//import Cell;

export class GraphicsDisplay: public Observer {
    static const int CELL_SIZE = 20;
    static const int BOARD_WIDTH = 11;
    static const int BOARD_HEIGHT = 15;
    static const int BOARD_OFFSET_X = 50;
    static const int BOARD1_OFFSET_Y = 100;
    static const int BOARD2_OFFSET_X = 350;
    
    Xwindow* xw;
    Board* board1;
    Board* board2;
    Player* player1;
    Player* player2;
    int hiScore;
    
    int getBlockColor(char blockType) const;
    void drawCell(int x, int y, int color);
    void drawBoard(int boardNum);
    void drawBorders();
    void drawInfo();
    void drawNextBlock(Player* player, int x, int y);
    
public:
    GraphicsDisplay(Board* b1, Board* b2, Player* p1, Player* p2);
    ~GraphicsDisplay();
    
    void notify() override;
    void setHiScore(int score);
};
