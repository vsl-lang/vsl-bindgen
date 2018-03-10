#include "extract.hpp"
#include <iostream>

/**
 * The visitor which manages where and what AST nodes should go and where they
 * should go.
 */
CLANG_VISITOR(Extract::visitor) {
    CXCursorKind kind = clang_getCursorKind(cursor);

    // Setup extractor
    Extract& extractor = Extract::getInstance();

    // We only care about declarations so don't care about other stuffs
    if (!clang_isDeclaration(kind)) return CXChildVisit_Continue;

    // Get the main cursor this refers to. This prevents us from looking at a
    // forward declaration and things like that
    CXCursor refCursor = clang_getCursorDefinition(cursor);
    if (!clang_equalCursors(refCursor, cursor)) return CXChildVisit_Continue;

    CXLanguageKind lang = clang_getCursorLanguage(cursor);

    switch (lang) {
        case CXLanguage_C:
        case CXLanguage_CPlusPlus:
            extractor.setLanguage(lang); break;
        default:
            std::cerr << "err(2): bad language (" << lang << ").";
            exit(1);
    }

    // Generator
    switch (kind) {
        case CXCursor_FunctionDecl:
            Extract::stringifyFunction(cursor);
            return CXChildVisit_Continue;

        case CXCursor_TypedefDecl:
            Extract::stringifyTypedef(cursor);
            return CXChildVisit_Continue;

        case CXCursor_StructDecl:
            if (extractor.getLanguage() == CXLanguage_C) {
                Extract::stringifyCStruct(cursor);
                return CXChildVisit_Continue;
            }

        default: break;
    }

    return CXChildVisit_Continue;
};
