#ifndef EXTRACT_H
#define EXTRACT_H

#include <clang-c/Index.h>
#include <memory>
#include <string>
#include <fstream>

#define CLANG_VISITOR(name) CXChildVisitResult name(CXCursor cursor, CXCursor parent, CXClientData client_data)
#define SERIALIZE(type) void type(CXCursor cursor, std::ostream& stream)

#define VSL_CSTRUCT_PREFIX "CStruct"

class Extract {
private:
    Extract();
    Extract(Extract const&) = delete;
    void operator =(Extract const*) = delete;
    
public:
    static CLANG_VISITOR(visitor);
    static Extract& getInstance();
    
    static inline const std::string unwrap(CXString cxstr);
    static SERIALIZE(stringifyFunction);
    static SERIALIZE(stringifyCStruct);
    
    std::ofstream out;
    
    void setOut(const std::string&);
};

#endif
