#include "extract.hpp"
#include "typeName.hpp"
#include <iostream>

const std::string Extract::typeName(CXType realType) {
    CXType type = clang_getCanonicalType(realType);
    switch (type.kind) {
        case CXType_Void: return "Void";
        case CXType_Bool: return "Bool";
        case CXType_Char16: return "UInt16";
        case CXType_Char32: return "UInt32";
        case CXType_UInt128: return "UInt128";
        case CXType_Int128: return "Int128";

        case CXType_UInt:
        case CXType_ULong:
        case CXType_UChar:
        case CXType_UShort:
        case CXType_Char_U:
        case CXType_ULongLong: return "UInt" + TYPE_SIZE;

        case CXType_Int:
        case CXType_Long:
        case CXType_Short:
        case CXType_SChar:
        case CXType_Char_S:
        case CXType_LongLong: return "Int" + TYPE_SIZE;

        case CXType_Float: return "Float";
        case CXType_Double: return "Double";
        case CXType_LongDouble: return "LongDouble";

        case CXType_Pointer: return PARENT_TYPE_GENERIC(Pointer, Pointee);

        case CXType_ConstantArray:
        case CXType_VariableArray:
        case CXType_IncompleteArray: return PARENT_TYPE_GENERIC(CArray, ArrayElement);

        case CXType_Record: {
            std::string typeName = TYPE_STRING(type);

            // Try to remove `struct`
            if (typeName.find(CSTRUCT_PREFIX) == 0)
                return typeName.replace(0, CSTRUCT_PREFIX.length(), VSL_CSTRUCT_PREFIX);
            else
                return typeName;
        }

        case CXType_NullPtr: return "Pointer.null";

        default:
            std::cerr << "warn(0): unknown type " << type.kind << std::endl;
            return "Object";
    }
}
