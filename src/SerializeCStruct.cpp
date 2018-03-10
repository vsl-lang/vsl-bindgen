#include "extract.hpp"

/**
 * Writes a **C** struct to a stream
 * @param cursor function node (must be or else bork)
 * @param stream stream to output, does not do margin etc.
 */
SERIALIZE(CStruct) {
    CXType type = clang_getCursorType(cursor);
    Extract& extractor = Extract::getInstance();
    std::ostream* stream = extractor.out.get();

    *stream << "@mock(pointer8) public class ";
    *stream << extractor.applyCutPrefix(Extract::typeName(type));
    *stream << " {}" << std::endl;
}
