// Make config txt to keep directory choice through runs

#include <fstream>
#include <iostream>
#include <string>
#include <filesystem>

#include "qtutils.h"

#if !defined(QTSTRG)
#define QTSTRG

std::string_view linuxdir = "../data/";
std::string_view windir = "C:\\Docs\\Qtstrg\\";
std::string const configdir = "../config/config.cfg";
std::string directory;

bool checkarg(int argc, char* argv[]) {
    // Check number of arguments
    if(argc == 1 || argc > 3) {
        std::cerr << argerrormsg << '\n';
        return 1;
    }
    
    // Check given argument
    for(int i{0}; i < argvecsize - 1; i++) {
        if(argumentvec[i] != argv[1] && i <= argvecsize - 2) {
            continue;
        } else if(argumentvec[i] != argv[1]) {
            //std::cout << i << '\n';
            std::cerr << "Not a valid argument, try qtstrg --help for a list of arguments\n";
            return 1;
        } else {
            break;
        }
    }
    return 0;
}

//Assigns the default directories depending on OS
bool defaultdir() {
    #if defined(_WIN32) || defined(_WIN64)
        directory = windir;
        return 0;
    #elif defined(__linux__)
        directory = linuxdir;
        return 0;
    #else
        std::cerr << "Invalid OS" << std::endl;
        return 1;
    #endif
}

// Initializes directory chosen in config file
bool dirinit() {
    std::ifstream config;
    config.open(configdir);
    if(config) {
        std::getline(config, directory);
        if(directory.empty()) {
            defaultdir(); 
            config.close();
            return 0;
        } else { 
            // std::cout << "Initialized with directory: " << directory << '\n';
            config.close();
            return 0;
        }
    } else {
        std::cerr << "Couldn't open config file\n";
        config.close();
        return 1;
    }
}

// Function that creates the text file (0, correct | 1, Couldn't create file | -1, File already exists)
int start() {
    if(!exists(directory + "quotes.txt")) {
        // Error, file already exists
        return -1;
    }
    // std::cout << startmes << '\n' << std::endl;
    std::ofstream quoteFile;
    quoteFile.open(directory + "quotes.txt");
    if(!quoteFile) {
        // Error creating file
        return 1;
    }
    quoteFile.close();
    // Succesful! Phew
    return 0;
}

bool chdir(int argc, char* argv[]) {
    if(argc < 3) {
            std::cerr << "Incorrect Usage: chdir requires a directory argument (--chdir path/)";
            return 1;
        }
    std::ofstream config;
    config.open(configdir);
    if(config) {
        directory = argv[2]; 
        config << directory << '\n';
        config.close();
        return 0;
    } else {
        std::cerr << "Couldn't open config file";
        return 1;
    }
}

bool clear() {
    if(!exists(directory + "quotes.txt")) {
        std::cerr << "quotes.txt doesn't exist, thus can't be cleared";
        return 1;
    }
    std::cout << "This option will clear your quotes.txt file forever, confirm? (y/n)\n> ";
    char option;
    option = std::cin.get();
    if(option == 'y') {
        std::ofstream(directory + "quotes.txt", std::ios::trunc);
        std::cout << "\nFile cleared succesfully!\n";
        return 0;
    } else {
        return 0;
    }
}

bool add(int argc, char* argv[]) {
    if(!exists(directory + "quotes.txt")) {
        std::cerr << "quotes.txt doesn't exist, thus can't add quotes";
        return 1;
    }
    std::ofstream quoteFile;
    quoteFile.open(directory + "quotes.txt", std::ios::ate | std::ios::app);
    std::string input;
    // Check for commandline input
    if(argc > 2) {
        input = argv[2];
        quoteFile << input << "\n\n";
        quoteFile.close();
        return 0;
    } else {
        std::cout << "qtstrg> ";
        std::cin >> input;
        quoteFile << input << "\n\n";
        quoteFile.close();
        return 0;
    }
}

#endif // QTSTRG