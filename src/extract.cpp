#include "extract.hpp"

Extract::Extract() {}

Extract& Extract::getInstance() {
    static Extract extractor;
    return extractor;
}

void Extract::setOut(const std::string file) {
    out.open(file);
}
