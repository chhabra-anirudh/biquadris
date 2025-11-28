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
    // Random seed for block generation
    int seed;
    int hiScore;
    // True if running without graphics
    bool textOnly;
    
public:
 // constructor
    Game(int startLevel, int seed, const string& scriptFile1, 
         const string& scriptFile2, bool textOnly);
    // Default destructor
    ~Game() = default;  
    // runs the main game loop, processes input, updates state, and renders output
    void run();
    // switches player
    void switchPlayer();
    // restarts the game
    void restart();
    // handles special actions
    void handleSpecialAction();
    // returns the hi score
    int getHiScore() const;
    //updates the hiscore
    void updateHiScore();
};
