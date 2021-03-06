#include "extract.hpp"


Extract::Extract() {}

Extract& Extract::getInstance() {
    static Extract extractor;
    return extractor;
}

void Extract::setOut(const std::string file) {
    out.reset(new std::ofstream(file));
}

void Extract::setOutStdout() {
    out.reset(new std::ostream(std::cout.rdbuf()));
}

void Extract::setCutPrefix(const std::string& prefix) {
    this->cutPrefix = prefix;
}

std::string Extract::applyCutPrefix(const std::string& source) {
    if (source.find(this->cutPrefix) != 0) return source;
    else return source.substr(this->cutPrefix.length());
}
