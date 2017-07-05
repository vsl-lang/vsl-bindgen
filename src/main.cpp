#include "executor.hpp"
#include "extract.hpp"
#include <iostream>

void printUsage() {
    std::cout << "Usage: vsl-bindgen <source> out.vsl [clang opts...]" << std::endl;
    std::cout << std::endl << "Reccomended usage through `vsl bindgen`" << std::endl;
}

void printErr(const std::string& error) {
    std::cerr << "vsl-bindgen: " << error << std::endl;
}

int main(int argc, char **argv) {
    // Three args, header, then output
    if (argc < 3) {
        printErr("err(0): expected 3 or more arguments");
        printUsage();
        exit(1);
    }
    
    // Header file
    const auto filename = argv[1];
    const auto outfile = argv[2];
    
    const auto clangArgs = argv + 3;
    const auto clangArgc = argc - 3;
    
    Extract& extractor = Extract::getInstance();
    extractor.setOut(std::string(outfile));
    
    Executor executor(filename);
    executor.run(clangArgc, clangArgs, &printErr);
    
    return 0;
}
