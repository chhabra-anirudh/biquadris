module CommandInterpreter;

import <iostream>;
import <fstream>;
import <sstream>;
import <string>;

using namespace std;


CommandInterpreter::CommandInterpreter() {
    CommandInitialise();
}

void CommandInterpreter::CommandInitialise() {
    commandMap["left"] = "left";
    commandMap["right"] = "right";
    commandMap["down"] = "down";
    commandMap["clockwise"] = "clockwise";
    commandMap["counterclockwise"] = "counterclockwise";
    commandMap["drop"] = "drop";
    commandMap["levelup"] = "levelup";
    commandMap["leveldown"] = "leveldown";
    commandMap["norandom"] = "norandom";
    commandMap["random"] = "random";
    commandMap["sequence"] = "sequence";
    commandMap["restart"] = "restart";
    commandMap["i"] = "I";
    commandMap["j"] = "J";
    commandMap["l"] = "L";
    commandMap["o"] = "O";
    commandMap["s"] = "S";
    commandMap["z"] = "Z";
    commandMap["t"] = "T";
    // Also add uppercase versions
    commandMap["I"] = "I";
    commandMap["J"] = "J";
    commandMap["L"] = "L";
    commandMap["O"] = "O";
    commandMap["S"] = "S";
    commandMap["Z"] = "Z";
    commandMap["T"] = "T";
}

std::string CommandInterpreter::matchCommand(const std::string& input) {
    auto it = commandMap.find(input);
    if (it != commandMap.end()) {
        return it->second;
    }

    string match{""};
    int matches = 0;

    for (const auto& pair: commandMap) {
        bool prefix = true;
        if (input.length() > pair.first.length()) {
            prefix = false;
        } else {
            for (size_t i = 0; i < input.length(); i++){
                if (input[i] != pair.first[i]) {
                    prefix = false;
                    break;
                }
            }
        }
        if (prefix) {
            match = pair.second;
            matches++;
        }
    }

    return (matches == 1) ? match : "";
}

bool CommandInterpreter::parse(const string& input, Player* current, Player* opponent) {
    if (input == "") return true;

    int multiplier = 1;
    string cmd = input;

    size_t i = 0;
    if (i < input.size() && input[i] > '0' && input[i] <= '9') {
        i++;
        while (i < input.size() && input[i] >= '0' && input[i] <= '9') {
            i++;
        }
    }

    if (i > 0) {
        multiplier = stoi(input.substr(0, i));
        cmd = input.substr(i);
    }

    string command = matchCommand(cmd);

    if (command == ""){
        cout << "Invalid command " << input << endl;
        return true;
    }

    if (command == "left") current->moveLeft(multiplier);
    else if (command == "right") current->moveRight(multiplier);
    else if (command == "down")  current->moveDown(multiplier);
    else if (command == "clockwise") for (int j = 0; j < multiplier; ++j) current->rotate(true);
    else if (command == "counterclockwise") for (int j = 0; j < multiplier; ++j) current->rotate(false);
    else if (command == "drop")  for (int j = 0; j < multiplier; ++j) current->drop();
    else if (command == "levelup")   for (int j = 0; j < multiplier; ++j) current->levelUp();
    else if (command == "leveldown") for (int j = 0; j < multiplier; ++j) current->levelDown();

    else if (command == "restart") {
        // Restart is handled by Game class in run() method
        // Just return true to continue
    }
    else if (command == "norandom") {
        string filename;
        cin >> filename;
        current->setNoRandom(filename);
    }
    else if (command == "random") current->setRandom();
    else if (command == "sequence") {
        string filename;
        cin >> filename;
        executeSequence(filename, current, opponent);
    }

    else if (command.size() == 1) {
        char blockChar = command[0];
        // Check both uppercase and lowercase
        if (blockChar >= 'a' && blockChar <= 'z') {
            blockChar = blockChar - 'a' + 'A';
        }
        if (string("IJLOSTZ").find(blockChar) != std::string::npos) {
            current->replaceBlock(blockChar);
        }
    }

    return true;
}

void CommandInterpreter::executeSequence(const string& filename, Player* current, Player* opponent){
    ifstream file{filename};
    if (!file) {
        std::cerr << "Could not open sequence file: " << filename << std::endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        if (!parse(line, current, opponent)) {
            break;
        }
    }
}
