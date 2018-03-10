#ifndef TYPE_NAME_H
#define TYPE_NAME_H

#include <string>

#define PARENT_TYPE_GENERIC(name, func) ( (#name "<") + Extract::typeName(clang_get ## func ## Type((type))) + ">" )
#define TYPE_STRING(name) (Extract::unwrap(clang_getTypeSpelling((name))))
#define TYPE_SIZE std::to_string(clang_Type_getSizeOf(type) * 8)

#define VSL_CSTRUCT_PREFIX "CStruct"
const std::string CSTRUCT_PREFIX("struct ");

#endif
