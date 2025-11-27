
import <iostream>;
import <string>;
import <cstdlib>;
import <ctime>;
import Game;

void printUsage() {
    std::cout << "Usage: biquadris [options]" << std::endl;
    std::cout << "Options:" << std::endl;
    std::cout << "  -text              Run in text-only mode (no graphics)" << std::endl;
    std::cout << "  -seed <n>          Set random seed to <n>" << std::endl;
    std::cout << "  -scriptfile1 <f>   Use <f> as level 0 sequence for player 1" << std::endl;
    std::cout << "  -scriptfile2 <f>   Use <f> as level 0 sequence for player 2" << std::endl;
    std::cout << "  -startlevel <n>    Start at level <n> (0-4)" << std::endl;
}

int main(int argc, char* argv[]) {
    // Default settings
    bool textOnly = false;
    int seed = time(nullptr);
    std::string scriptFile1 = "biquadris_sequence1.txt";
    std::string scriptFile2 = "biquadris_sequence2.txt";
    int startLevel = 0;
    
    // Parse command-line arguments
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        
        if (arg == "-text") {
            textOnly = true;
        } else if (arg == "-seed" && i + 1 < argc) {
            seed = std::atoi(argv[++i]);
        } else if (arg == "-scriptfile1" && i + 1 < argc) {
            scriptFile1 = argv[++i];
        } else if (arg == "-scriptfile2" && i + 1 < argc) {
            scriptFile2 = argv[++i];
        } else if (arg == "-startlevel" && i + 1 < argc) {
            startLevel = std::atoi(argv[++i]);
            if (startLevel < 0) startLevel = 0;
            if (startLevel > 4) startLevel = 4;
        } else if (arg == "-help" || arg == "--help" || arg == "-h") {
            printUsage();
            return 0;
        } else {
            std::cerr << "Unknown option: " << arg << std::endl;
            printUsage();
            return 1;
        }
    }
    
    try {
        Game game(startLevel, seed, scriptFile1, scriptFile2, textOnly);
        game.run();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}
