#include "extract.hpp"
#include <iostream>

Extract::Extract() {}

Extract& Extract::getInstance() {
    static Extract extractor;
    return extractor;
}

void Extract::setOut(const std::string& file) {
    out.open(file);
}

/**
 * Unwraps a CXString to an std::string
 * @param  cxstr CXString of str automatically disposed.
 * @return       Ref. to the string so parent can own it
 */
 inline const std::string Extract::unwrap(CXString cxstr) {
     const std::string str = std::string(clang_getCString(cxstr));
     clang_disposeString(cxstr);
     return str;
 }

/**
 * Writes a C/C++ function to a stream
 * @param cursor function node (must be or else bork)
 * @param stream stream to output, does not do margin etc.
 */
SERIALIZE(Extract::stringifyFunction) {
    std::string binaryName = Extract::unwrap(clang_Cursor_getMangling(cursor));
    
    // Add inline attribute if clang say to inline
    if (clang_Cursor_isFunctionInlined(cursor)) {
        stream << "@inline" << std::endl;
    }
    
    stream << "public func name() external(" << binaryName << ");" << std::endl;
}

/**
 * Writes a **C** struct to a stream
 * @param cursor function node (must be or else bork)
 * @param stream stream to output, does not do margin etc.
 */
SERIALIZE(Extract::stringifyCStruct) {
    stream << "typealias " << VSL_CSTRUCT_PREFIX << " = OpaquePointer;" << std::endl;
}

/**
 * The visitor which manages where and what AST nodes should go and where they
 * should go.
 */
CLANG_VISITOR(Extract::visitor) {
    CXCursorKind kind = clang_getCursorKind(cursor);
    CXLanguageKind language = clang_getCursorLanguage(cursor);
    
    bool isC = false;
    
    switch (language) {
        case CXLanguage_C: isC = true; break;
        case CXLanguage_CPlusPlus: isC = false; break;
        default:
            std::cerr << "err(2): bad language." << std::endl;
            exit(1);
    }
    
    // We only care about declarations so don't care about other stuffs
    if (!clang_isDeclaration(kind)) return CXChildVisit_Continue;
    
    // Setup extractor
    Extract& extractor = Extract::getInstance();
    
    // Generator
    switch (kind) {
        case CXCursor_FunctionDecl:
            Extract::stringifyFunction(cursor, extractor.out);
            return CXChildVisit_Continue;
            
        case CXCursor_StructDecl:
            if (isC == true) {
                Extract::stringifyCStruct(cursor, extractor.out);
                return CXChildVisit_Continue;
            }
    }
        
    return CXChildVisit_Recurse;
};
