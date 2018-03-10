#include "extract.hpp"

/**
 * Writes a **C** struct to a stream
 * @param cursor function node (must be or else bork)
 * @param stream stream to output, does not do margin etc.
 */
SERIALIZE(Typedef) {
    Extract& extractor = Extract::getInstance();
    std::ostream* stream = extractor.out.get();
    std::string targetId = Extract::unwrap(clang_getTypeSpelling(clang_getCursorType(cursor)));
    std::string sourceId = Extract::typeName(clang_getTypedefDeclUnderlyingType(cursor));

    // If we have like `typedef T = T` we don't want that. This is caused in
    // things like `typedef struct {} T;`
    if (targetId == sourceId) return;

    *stream << "public typealias ";
    *stream << extractor.applyCutPrefix(targetId);
    *stream << " = ";
    *stream << sourceId;
    *stream << ";" << std::endl;
}
