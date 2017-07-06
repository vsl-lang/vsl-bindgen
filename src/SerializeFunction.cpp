#include "extract.hpp"

/**
 * Writes a C/C++ function to a stream
 * @param cursor function node (must be or else bork)
 * @param stream stream to output, does not do margin etc.
 */
SERIALIZE(Function) {
    Extract& extractor = Extract::getInstance();
    
    // Add inline attribute if clang say to inline
    if (clang_Cursor_isFunctionInlined(cursor)) {
        stream << "@inline" << std::endl;
    }
    
    // This is the name that it was originaly declared. This is generally fully
    // qualified so not sure how to do with C++. Likely we'll need to defer.
    std::string displayName = Extract::unwrap(clang_getCursorSpelling(cursor));
    
    stream << "public ";
    
    if (clang_CXXMethod_isStatic(cursor)) {
        stream << "static ";
    }
    
    stream << "func ";
    stream << extractor.applyCutPrefix(displayName);
    stream << "(";
    
    // Do the args, note: type names are not 100%
    int numArgs = clang_Cursor_getNumArguments(cursor);
    for (int i = 0; i < numArgs; i++) {
        CXCursor arg = clang_Cursor_getArgument(cursor, i);
        
        // The name of the argument, do note that we might want to allow ignoring
        // the params in some cases.
        stream << Extract::unwrap(clang_getCursorSpelling(arg));
        
        // If it doesn't have a type we won't set one but VSL will throw an error
        // there is no situation where this should happen
        CXType argType = clang_getCursorType(arg);
        stream << ": " << Extract::typeName(argType);
        
        // Add the `,` but don't add for last arg
        if (i < numArgs - 1) {
            stream << ", ";
        }
    }
    
    stream << ")";
    
    // Add the return type
    stream << " -> " << Extract::typeName(clang_getResultType(clang_getCursorType(cursor)));
    
    // The mangled/internal name spec.ing the ABI name
    std::string binaryName = extractor.getLanguage() == CXLanguage_C ?
        displayName :
        Extract::unwrap(clang_Cursor_getMangling(cursor));
    
    stream << " external(" << binaryName << ");" << std::endl;
}
