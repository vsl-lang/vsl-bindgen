#include "extract.hpp"
#include "typeName.hpp"
#include <iostream>

const std::string Extract::typeName(CXType realType) {
    CXType type = clang_getCanonicalType(realType);
    switch (type.kind) {
        case CXType_Void: return "Void";
        case CXType_Bool: return "Bool";
        case CXType_Char_U:
        case CXType_UChar: return "UInt8";
        case CXType_Char_S:
        case CXType_SChar: return "Int8";
        case CXType_UShort: return "UInt16";
        case CXType_Char16:
        case CXType_Short: return "Int16";
        case CXType_UInt: return "UInt32";
        case CXType_Char32:
        case CXType_Int: return "Int";
        case CXType_ULong: return "UInt64";
        case CXType_Long: return "Int64";
        case CXType_ULongLong:
        case CXType_UInt128: return "UInt128";
        case CXType_LongLong:
        case CXType_Int128: return "Int128";
        
        case CXType_Float: return "Float";
        case CXType_Double: return "Double";
        case CXType_LongDouble: return "LongDouble";
        
        case CXType_Pointer: return PARENT_TYPE_GENERIC(Pointer, Pointee);
        
        case CXType_ConstantArray:
        case CXType_VariableArray:
        case CXType_IncompleteArray: return PARENT_TYPE_GENERIC(CArray, ArrayElement);
        
        case CXType_Record:
            return VSL_CSTRUCT_PREFIX + TYPE_STRING(type).erase(0, CSTRUCT_PREFIX.length());
        
        case CXType_NullPtr: return "Pointer.null";
        
        default:
            std::cerr << "warn(0): unknown type " << type.kind << std::endl;
            return "Object";
    }
}
