export module CommandInterpreter;
import <map>;
import <string>;

import Player;

using namespace std;

export class CommandInterpreter {
    // Maps user command strings to canonical command names
    map<string, string> commandMap;

    // Fills commandMap with all supported commands and block type overrides
    void CommandInitialise();
    // Returns the canonical command if input is an exact or unique prefix match, otherwise an empty string
    string matchCommand(const string& input);

    public:
        //constructor
        CommandInterpreter();
        //Parses a user command and executes it on the players
        bool parse(const string& input, Player *current, Player* opponent);
        // Reads a script file and executes each line as a command via parse()
        void executeSequence(const string& filename, Player* current, Player* opponent);
};
