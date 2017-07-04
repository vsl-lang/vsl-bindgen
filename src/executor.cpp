#include "executor.hpp"

Executor::Executor(const char *infile): infile(infile) {
}

void Executor::run(void (*printErr)(const std::string& error)) {
    // A shared 'context' between 'translation units'
    CXIndex index = clang_createIndex(1, 1);
    
    const char *args[] = { "-cc1" };
    
    // The translation of our file.
    CXTranslationUnit tu = clang_parseTranslationUnit(
        index, this->infile,
        args, 1,
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
