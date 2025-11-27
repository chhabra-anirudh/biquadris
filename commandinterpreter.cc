export module CommandInterpreter;
import <map>;
import <string>;

import Player;

using namespace std;

class CommandInterpreter {
    map<string, string> commandMap;

    void CommandInitialise();
    string matchCommand(const string& input)

    public:
        CommandInterpreter();

        bool parse(const string& input, Player *current, Player* opponent);

        void executeSequence(const string& filename, Player* current, Player* opponent);
};

