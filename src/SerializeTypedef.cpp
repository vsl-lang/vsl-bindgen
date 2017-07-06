#include "extract.hpp"

/**
 * Writes a **C** struct to a stream
 * @param cursor function node (must be or else bork)
 * @param stream stream to output, does not do margin etc.
 */
SERIALIZE(Typedef) {
    Extract& extractor = Extract::getInstance();
    
    stream << "public typealias ";
    stream << extractor.applyCutPrefix(
        Extract::unwrap(clang_getTypeSpelling(clang_getCursorType(cursor)))
    );
    stream << " = ";
    stream << Extract::typeName(clang_getTypedefDeclUnderlyingType(cursor));
    stream << ";" << std::endl;
}
