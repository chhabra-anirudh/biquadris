export module Game;

import Player;
import TextDisplay;
import GraphicsDisplay;
import CommandInterpreter;
import <string>;
import <memory>;

using namespace std;

export class Game {
    unique_ptr<Player> player1;
    unique_ptr<Player> player2;
    Player* currentPlayer;
    Player* opponent;
    unique_ptr<TextDisplay> textDisplay;
    unique_ptr<GraphicsDisplay> graphicsDisplay;
    unique_ptr<CommandInterpreter> interpreter;
    int seed;
    int hiScore;
    bool textOnly;
    
public:
    Game(int startLevel, int seed, const string& scriptFile1, 
         const string& scriptFile2, bool textOnly);
    ~Game() = default;  // Smart pointers handle cleanup
    
    void run();
    void switchPlayer();
    void restart();
    void handleSpecialAction();
    
    int getHiScore() const;
    void updateHiScore();
};
