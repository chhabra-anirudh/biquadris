module Game;

import <iosteam>;
import <cstdlib>;

using namespace std;

Game::Game(int startLevel, int seed, const string &scriptFile1, 
    const string &scriptfile2, bool textOnly):
    player1{make_unique<Player>(startLevel, scriptFile1, seed)},
    player2{make_unique<Player>(startLevel, scriptFile1, seed)},
    seed{seed}, hiscore{0}, textOnly{textOnly} {
        
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
        if (!testOnly){
            graphicsDisplay = make_unique<GraphicsDisplay>(
                player1->getBoard(), player2->getBoard(),player1.get(), player2.get());
            player1->getBoard()->attach(graphicsDisplay.get());
            player2->getBoard()->attch(graphicsDisplay.get());
        }
    }
