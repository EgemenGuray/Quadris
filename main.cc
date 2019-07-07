#include <iostream>
#include <string>
#include "controller.h"

int main(int argc, char *argv[]) {
    
    bool onlyText = false; //check if output is text mode only
    bool nospecial = false; //check is special features allowed
    //Relevant for level 0, the blocks generated follow pattern set in these files
    std::string scriptFile1 = "sequence1.txt";
    std::string scriptFile2 = "sequence2.txt";
    //Default values of seed and level for the game
    int seed = 1, level = 0, i = 0;
    std::string argument;
    while (i < argc) {
        argument = argv[i];
        if (argument == "-seed") {
            seed = std::stoi(argv[i+1]);
            i += 2;
        } else if (argument == "-text") {
            onlyText = true;
            ++i;
        } else if (argument == "-nospecial") {
            nospecial = true;
            ++i;
        } else if (argument == "-scriptfile1") {
            scriptFile1 = argv[i+1];
            i += 2;
        } else if (argument == "-scriptfile2") {
            scriptFile2 = argv[i +1];
            i += 2;
        } else if (argument == "-startlevel") {
            level = std::stoi(argv[i+1]);
            i +=2;
        } else {
            ++i;
            continue;
        }
    }
    
    Controller control{onlyText, seed, level, nospecial, scriptFile1, scriptFile2};
    std::string command;
    std::cout<<"Please Enter Command:"<<std::endl;
    while (std::getline(std::cin, command)) {
        //N will end the game
        if (command == "N") { break; }
        try { control.applyCommand(command); }
        catch(std::invalid_argument r) { continue; }
        catch(std::out_of_range a) {std::cout<< "Please enter complete command" << std::endl;}
    }
}
