module CommandInterpreter;

import <iostream>;

CommandInterpreter::CommandInterpreter() {
    initializeCommands();
}

void CommandInterpreter::initializeCommands() {
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
}

std::string CommandInterpreter::matchCommand(const std::string& input) {
    auto it = commandMap.find(input);
    if (it != commandMap.end()) {
        return it->second;
    }
}