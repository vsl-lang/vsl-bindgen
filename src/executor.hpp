#ifndef EXECUTOR_H
#define EXECUTOR_H

#include <clang-c/Index.h>
#include <string>
#include "extract.hpp"

class Executor {
private:
    const char *infile;
    
public:
    Executor(const char *infile);
    void run(void (*printErr)(const std::string& error));
};

#endif
