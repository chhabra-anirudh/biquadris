import <iostream>;
import <string>;
import <cstdlib>;
import <ctime>;
import Game;

using namespace std;

void printUsage() {
    cout << "Usage: biquadris [options]\n";
    cout << "Options:\n";
    cout << "  -text              Run in text-only mode (no graphics)\n";
    cout << "  -seed <n>          Set random seed to <n>\n";
    cout << "  -scriptfile1 <f>   Use <f> as level 0 sequence for player 1\n";
    cout << "  -scriptfile2 <f>   Use <f> as level 0 sequence for player 2\n";
    cout << "  -startlevel <n>    Start at level <n> (0-4)\n";
}

int my_Stoi(const string &s) {
    try {
        return stoi(s);
    } catch (...) {
        cerr << "Invalid number: " << s << "\n";
        exit(1);
    }
}

int main(int argc, char* argv[]) {
    bool textOnly = false;
    int seed = static_cast<int>(time(nullptr));
    string scriptFile1 = "biquadris_sequence1.txt";
    string scriptFile2 = "biquadris_sequence2.txt";
    int startLevel = 0;
    
    for (int i = 1; i < argc; ++i) {
        string arg = argv[i];
        
        if (arg == "-text") {
            textOnly = true;

        } else if (arg == "-seed" && i + 1 < argc) {
            seed = my_Stoi(argv[++i]);

        } else if (arg == "-scriptfile1" && i + 1 < argc) {
            scriptFile1 = argv[++i];

        } else if (arg == "-scriptfile2" && i + 1 < argc) {
            scriptFile2 = argv[++i];

        } else if (arg == "-startlevel" && i + 1 < argc) {
            startLevel = my_Stoi(argv[++i]);
            if (startLevel < 0) startLevel = 0;
            if (startLevel > 4) startLevel = 4;

        } else if (arg == "-help" || arg == "--help" || arg == "-h") {
            printUsage();
            return 0;

        } else {
            cerr << "Unknown option: " << arg << "\n";
            printUsage();
            return 1;
        }
    }
    
    try {
        Game game(startLevel, seed, scriptFile1, scriptFile2, textOnly);
        game.run();
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << "\n";
        return 1;
    }
    
    return 0;
}
