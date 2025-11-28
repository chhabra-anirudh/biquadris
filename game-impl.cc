module Game;

import <iostream>;
import <cstdlib>;
import TextDisplay;
import CommandInterpreter;
import Player;
//import SpecialAction;


using namespace std;

Game::Game(int startLevel, int seed, const string &scriptfile1, 
    const string &scriptfile2, bool textOnly):
    player1{make_unique<Player>(startLevel, scriptfile1, seed)},
    player2{make_unique<Player>(startLevel, scriptfile2, seed)},
    seed{seed}, hiScore{0}, textOnly{textOnly} {
        
        //set random seed
        srand(seed);

        currentPlayer = player1.get();
        opponent = player2.get();

        //Create  text display
        textDisplay = make_unique<TextDisplay> (
            player1->getBoard(), player2->getBoard(),
            player1.get(), player2.get());

        //Attach text display to boards
        player1->getBoard()->attach(textDisplay.get());
        player2->getBoard()->attach(textDisplay.get());

        //create graphics display if not text-only
        if (!textOnly){
            graphicsDisplay = make_unique<GraphicsDisplay>(
                player1->getBoard(), player2->getBoard(),player1.get(), player2.get());
            player1->getBoard()->attach(graphicsDisplay.get());
            player2->getBoard()->attach(graphicsDisplay.get());
        }

        //Create interpreter

        interpreter = make_unique<CommandInterpreter>();
    }

    void Game::switchPlayer() {
        if (currentPlayer == player1.get()) {
            currentPlayer = player2.get();
            opponent = player1.get();
        } else {
            currentPlayer = player1.get();
            opponent = player2.get();
        }
    }

    void Game::restart() {
        player1->reset();
        player2->reset();
        currentPlayer = player1.get();
        opponent = player2.get();
        
        // Update display board pointers to new boards
        textDisplay->updateBoards(player1->getBoard(), player2->getBoard());
        if (graphicsDisplay) {
            graphicsDisplay->updateBoards(player1->getBoard(), player2->getBoard());
        }
        
        // Reattach displays to new boards
        player1->getBoard()->attach(textDisplay.get());
        player2->getBoard()->attach(textDisplay.get());
        if (graphicsDisplay) {
            player1->getBoard()->attach(graphicsDisplay.get());
            player2->getBoard()->attach(graphicsDisplay.get());
        }
        
        // Notify displays of the reset
        textDisplay->notify();
        if (graphicsDisplay) {
            graphicsDisplay->notify();
        }
    }

void Game::handleSpecialAction() {
    cout << "Special action triggered! Choose action:" << endl;
    cout << "  blind - Cover opponent's board with ?" << endl;
    cout << "  heavy - Opponent's blocks drop 2 rows on movement" << endl;
    cout << "  force <type> - Force opponent's next block (e.g., force Z)" << endl;
    
    string action;
    cin >> action;
    
    if (action == "blind") {
        BlindAction blindAction;
        blindAction.apply(opponent);

    } else if (action == "heavy") {
        HeavyAction heavyAction;
        heavyAction.apply(opponent);

    } else if (action == "force") {
        char blockType;
        cin >> blockType;
        
        // Convert to uppercase
        if (blockType >= 'a' && blockType <= 'z') {
            blockType = blockType - 'a' + 'A';
        }
        
        ForceAction forceAction(blockType);
        forceAction.apply(opponent);

    } else {
        cout << "Invalid action, no effect applied." << endl;
    }
}

int Game::getHiScore() const {
    return hiScore;
}

void Game::updateHiScore() {
    int p1Score = player1->getScore();
    int p2Score = player2->getScore();

    if (p1Score > hiScore) {
        hiScore = p1Score;
    }
    if (p2Score > hiScore) {
        hiScore = p2Score;
    }
}

void Game::run() {
    cout << "Welcome to Biquadris!" << endl;
    cout << "Player 1 starts." << endl;
    
    // Initial display (hiScore starts at 0)
    textDisplay->setHiScore(0);
    if (graphicsDisplay) {
        graphicsDisplay->setHiScore(0);
    }
    textDisplay->display(cout);
    
    string input;
    while (cin >> input) {
        // Check if this is a single-letter block replacement command
        // Block replacement commands (I, J, L, O, S, Z, T) don't accept multipliers
        bool isBlockReplace = (input.length() == 1 && 
                              string("IJLOSTZ").find(input[0]) != string::npos);
        
        // Parse multiplier if present (manual conversion)
        int multiplier = 1;
        size_t i = 0;
        
        // Only parse multiplier if not a block replacement command
        if (!isBlockReplace) {
            while (i < input.length() && (input[i] >= '0') && (input[i] <= '9')) {
                ++i;
            }
            
            if (i > 0) {
                // Convert to int manually
                multiplier = 0;
                for (size_t j = 0; j < i; ++j) {
                    multiplier = multiplier * 10 + (input[j] - '0');
                }
                
                // Get rest of string
                string temp = "";
                for (size_t j = i; j < input.length(); ++j) {
                    temp += input[j];
                }
                input = temp;
            }
        }
        
        // Special handling for drop command
        // Check if input starts with "dr" or is "drop"
        bool isDrop = false;
        if (input.length() >= 2 && input[0] == 'd' && input[1] == 'r') {
            isDrop = true;
        }
        if (input == "drop") {
            isDrop = true;
        }
        
        if (isDrop) {
            for (int j = 0; j < multiplier; ++j) {
                currentPlayer->drop();
                
                // Check if game over
                if (currentPlayer->isGameOver()) {
                    textDisplay->display(cout);
                    cout << "Game Over!" << endl;
                    
                    if (currentPlayer == player1.get()) {
                        cout << "Player 2 wins!" << endl;
                    } else {
                        cout << "Player 1 wins!" << endl;
                    }
                    
                    updateHiScore();
                    textDisplay->setHiScore(hiScore);
                    if (graphicsDisplay) {
                        graphicsDisplay->setHiScore(hiScore);
                    }
                    textDisplay->display(cout);
                    cout << "Game Over!" << endl;
                    
                    if (currentPlayer == player1.get()) {
                        cout << "Player 2 wins!" << endl;
                    } else {
                        cout << "Player 1 wins!" << endl;
                    }
                    
                    cout << "Hi Score: " << hiScore << endl;
                    return;
                }
                
                // Check if 2+ rows cleared - trigger special action
                if (currentPlayer->getLastRowsCleared() >= 2) {
                    textDisplay->display(cout);
                    handleSpecialAction();
                }
            }
            
            // Switch players after drop
            switchPlayer();
            
        } else {
            // Check if restart command before parsing
            if (input == "restart" || input.find("restart") == 0) {
                restart();
                textDisplay->display(cout);
                continue;
            }
            
            // For block replacement commands, don't add multiplier prefix
            if (isBlockReplace) {
                if (!interpreter->parse(input, currentPlayer, opponent)) {
                    break;  // EOF or quit
                }
            } else {
                // Execute command with multiplier
                // Build full command string manually
                string fullCommand = "";
                
                // Add multiplier digits
                int temp = multiplier;
                if (temp > 0) {
                    string digits = "";
                    while (temp > 0) {
                        digits = char('0' + (temp % 10)) + digits;
                        temp /= 10;
                    }
                    fullCommand = digits;
                }
                fullCommand += input;
                
                if (!interpreter->parse(fullCommand, currentPlayer, opponent)) {
                    break;  // EOF or quit
                }
            }
        }
        
        // Update hi score
        updateHiScore();
        
        // Update displays with new hi score
        textDisplay->setHiScore(hiScore);
        if (graphicsDisplay) {
            graphicsDisplay->setHiScore(hiScore);
        }
        
        // Display current state
        textDisplay->display(cout);
        
        // Show current player
        if (currentPlayer == player1.get()) {
            cout << "Player 1's turn" << endl;
        } else {
            cout << "Player 2's turn" << endl;
        }
    }
    
    cout << "Game ended. Final Hi Score: " << hiScore << endl;
}
