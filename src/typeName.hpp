#ifndef TYPE_NAME_H
#define TYPE_NAME_H

#define PARENT_TYPE_GENERIC(name, func) ( (#name "<") + Extract::typeName(clang_get ## func ## Type(type)) + ">" )

#define VSL_CSTRUCT_PREFIX "CStruct"

#endif
