#include "executor.hpp"
#include "extract.hpp"
#include <iostream>
#include <string>
#include <cstdint>
#include <map>

#define OPT_READ_HEAD  0x1F
#define OPT_READ_TAIL  0x1E
#define OPT_CUT_PREFIX 0x4F

typedef uint32_t opt_length_t;

void printUsage() {
    std::cout << "Usage: vsl-bindgen <source> out.vsl [clang opts...]" << std::endl;
    std::cout << "bindgen opts through stdin." << std::endl;
    std::cout << "opt format: 0x1F ui32 (opt id) ui32 (payload length) payload> 0x1E" << std::endl;
    std::cout << std::endl << "Reccomended usage through `vsl bindgen`" << std::endl;
}

void printErr(const std::string& error) {
    std::cerr << "vsl-bindgen: " << error << std::endl;
}

std::map<unsigned, std::string> options;

void getOpts() {
    while (std::cin.get() == OPT_READ_HEAD) {
        opt_length_t optId;
        opt_length_t valLen;
        
        std::cin.read((char*) &optId, sizeof(opt_length_t));
        std::cin.read((char*) &valLen, sizeof(opt_length_t));
        
        char *value = new char[valLen];
        std::cin.read(value, valLen);
        
        options[optId] = std::string(value);
        
        char c = std::cin.get();
        if (c != OPT_READ_TAIL) {
            printErr("err(3): malformed bindgen opt format (internal).");
            exit(1);
        }
    }
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
    
    // Set prefixes
    getOpts();
    
    Extract& extractor = Extract::getInstance();
    extractor.setOut(std::string(outfile));
    
    // Handle prefix cutting
    auto it = options.find(OPT_CUT_PREFIX);
    if (it != options.end()) extractor.setCutPrefix(it->second);
    
    Executor executor(filename);
    executor.run(clangArgc, clangArgs, &printErr);
    
    return 0;
}
