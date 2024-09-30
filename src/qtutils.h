#include <string>
#include <iostream>
#include <filesystem>

#if !defined(QTUTILS)
#define QTUTILS

const std::string argumentvec[5] = {"--help", "--start", "--chdir", "--add", "--clear"};
const int argvecsize = sizeof(argumentvec) / sizeof(argumentvec[0]);

std::string helpstr = "Usage: work in progress";
std::string argerrormsg = "ERROR: Missing arguments, use qtstrg --help for usage guidance";

bool exists(std::string filedir) {
    if(std::filesystem::exists(filedir)) {
        return true;
    } else {
        return false;
    }
}

#endif // QTUTILS