#ifndef CONVERT_COMMENT_H
#define CONVERT_COMMENT_H

#include "extract.hpp"
#define FOR_EACH_CHILD                                                         \
    unsigned children = clang_Comment_getNumChildren(comment);                 \
    for (unsigned i = 0; i < children; i++)
#define RECURSE                                                                \
    Extract::convertComment(clang_Comment_getChild(comment, i));

void convertComment(const CXComment);

#endif
