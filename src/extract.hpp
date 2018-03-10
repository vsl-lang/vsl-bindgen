#ifndef EXTRACT_H
#define EXTRACT_H

#include <clang-c/Index.h>
#include <clang-c/Documentation.h>

#include <memory>
#include <string>
#include <fstream>
#include <iostream>
#include <set>
#include <algorithm>

#define CLANG_VISITOR(name) CXChildVisitResult name(CXCursor cursor, CXCursor parent, CXClientData client_data)

#define _SERIALIZE_PROTO(type) void type(CXCursor cursor)
#define SERIALIZE_H(type) _SERIALIZE_PROTO(stringify##type)
#define SERIALIZE(type) _SERIALIZE_PROTO(Extract::stringify##type)

class Extract {
private:
    Extract();
    Extract(Extract&&) =delete;
    Extract(const Extract&) = delete;
    Extract& operator =(Extract&&) = delete;
    void operator =(const Extract*) = delete;

    CXLanguageKind language;
    std::string cutPrefix;
public:
    static CLANG_VISITOR(visitor);
    static Extract& getInstance();

    /**
     * Unwraps a CXString to an std::string
     * @param  cxstr CXString of str automatically disposed.
     * @return       Ref. to the string so parent can own it
     */
    static inline std::string unwrap(CXString cxstr) {
        const std::string str = std::string(clang_getCString(cxstr));
        clang_disposeString(cxstr);
        return str;
    }

    /**
     * Returns the canolical VSL type name for a given type. Of course this
     * requires the typename to be defined and converted through whether it be
     * through a struct typedef or such.
     *
     * @param  type CXType representing a type node to convert to VSL string
     * @return      VSL-friendly string that can be directly insert into ast.
     */
    static const std::string typeName(CXType type);

    /**
     * Stringifies a comment to a stream
     * @param comment   root of comment to
     * @param stream    stream to write to
     */
    static void convertComment(const CXComment);

    static SERIALIZE_H(Function);
    static SERIALIZE_H(CStruct);
    static SERIALIZE_H(Typedef);

    std::unique_ptr<std::ostream> out;
    void setOut(const std::string);
    void setOutStdout();
    void setCutPrefix(const std::string&);
    std::string applyCutPrefix(const std::string&);

    void setLanguage(CXLanguageKind lang) {
        if (lang <= this->language) return;

        if (lang == CXLanguage_CPlusPlus) {
            std::cerr << "warn(1): non-C support is experimental." << std::endl;
        }
        this->language = lang;
    }
    bool getLanguage() const { return this->language; }
};

#endif
