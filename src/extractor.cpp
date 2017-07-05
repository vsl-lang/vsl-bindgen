#include "extract.hpp"
#include <iostream>

/**
 * The visitor which manages where and what AST nodes should go and where they
 * should go.
 */
CLANG_VISITOR(Extract::visitor) {
    CXCursorKind kind = clang_getCursorKind(cursor);
    CXLanguageKind language = clang_getCursorLanguage(cursor);
    
    // Setup extractor
    Extract& extractor = Extract::getInstance();
    
    switch (language) {
        case CXLanguage_C: extractor.isC = true; break;
        case CXLanguage_CPlusPlus: extractor.isC = false; break;
        case CXLanguage_Invalid: return CXChildVisit_Continue;
        default:
            std::cerr << "err(2): bad language (" << language << ")." << std::endl;
            exit(1);
    }
    
    // We only care about declarations so don't care about other stuffs
    if (!clang_isDeclaration(kind)) return CXChildVisit_Continue;
    
    // Get the main cursor this refers to. This prevents us from looking at a
    // forward declaration and things like that
    CXCursor refCursor = clang_getCursorDefinition(cursor);
    if (!clang_equalCursors(refCursor, cursor)) return CXChildVisit_Continue;
    
    // Generator
    switch (kind) {
        case CXCursor_FunctionDecl:
            Extract::stringifyFunction(cursor, extractor.out);
            return CXChildVisit_Continue;
        
        case CXCursor_TypedefDecl:
            Extract::stringifyTypedef(cursor, extractor.out);
            return CXChildVisit_Continue;
        
        case CXCursor_StructDecl:
            if (extractor.isC) {
                Extract::stringifyCStruct(cursor, extractor.out);
                return CXChildVisit_Continue;
            }
            
        default: break;
    }
        
    return CXChildVisit_Continue;
};
