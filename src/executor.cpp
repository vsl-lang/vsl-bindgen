#include "executor.hpp"

#include <iostream>
Executor::Executor(const char *infile): infile(infile) {
}

void Executor::run(int argc, char** argv, void (*printErr)(const std::string& error)) {
    // A shared 'context' between 'translation units'
    CXIndex index = clang_createIndex(1, 1);
    
    // The translation of our file.
    CXTranslationUnit tu = clang_parseTranslationUnit(
        index, this->infile,
        argv, argc,
        nullptr, 0,
        CXTranslationUnit_None
    );
    
    if (tu == NULL) {
        printErr("err(1): could not create main translation unit.");
        exit(1);
    }
    
    // Cursor is what directly references an item whether it be a declaration or
    // a statement, in this case represent translation unit
    CXCursor cursor = clang_getTranslationUnitCursor(tu);
    
    clang_visitChildren(cursor, Extract::visitor, nullptr);
    
    clang_disposeTranslationUnit(tu);
    clang_disposeIndex(index);
}
