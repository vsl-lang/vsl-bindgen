#include "extract.hpp"

/**
 * Writes a **C** struct to a stream
 * @param cursor function node (must be or else bork)
 * @param stream stream to output, does not do margin etc.
 */
SERIALIZE(CStruct) {
    CXType type = clang_getCursorType(cursor);
    stream << "public typealias ";
    stream << Extract::typeName(type) << " = ";
    stream << "Bitfield<" << clang_Type_getSizeOf(type) << ">";
    stream << std::endl;
}
