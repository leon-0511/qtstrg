#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>

#include "qtstrg.cc"
#include "qtutils.h"


int main(int argc, char* argv[]) {
    // Initialize variable directory with the one provided by config, or default.
    dirinit();
    
    // No arguments? Error & Exit
    if(checkarg(argc, argv) == 1) return 1;
    
    std::string argument = argv[1];
    // --help Argument
    if(argument == "--help") {
        std::cout << helpstr << '\n' << std::endl;
        return 0;
    }

    // --start Argument
    if(argument == "--start") {
        switch(start()) {
            case 0:
                std::cout << "Text file was created successfully! (" << directory << ")" << std::endl;
                return 0;
                break;
            case 1:
                std::cerr << "Error creating file! " << std::endl;
                return 1;
                break;
            case -1:
                std::cerr << "quotes.txt already exists, nothing was changed" << std::endl;
                return 1;
                break;
            default:
                std::cerr << "I don't know how you got here, but there's some error, have a cookie\n";
                return 2;
                break;
        }
    }

    if(argument == "--chdir") {
        if(chdir(argc, argv)) return 0;
        else return 1;
    }
    
   // Add quote to the quotes.txt 
   if(argument == "--add") {
        if(add(argc, argv) == 0) return 0;
        else return 1;
   }

   if(argument == "--clear") {
        if(clear() == 0) return 0;
        else return 1;
   }

    return 0;
}