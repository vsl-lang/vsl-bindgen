#include "convertComment.hpp"

void Extract::convertComment(const CXComment comment, std::ostream& stream) {
    switch(clang_Comment_getKind(comment)) {
        case CXComment_FullComment: {
            stream << "/**" << std::endl;
            
            FOR_EACH_CHILD {
                stream << " *";
                RECURSE;
            }
            
            stream << " */" << std::endl;
            break;
        }
        
        case CXComment_ParamCommand: {
            std::string paramName = Extract::unwrap(clang_ParamCommandComment_getParamName(comment));
    
            stream << " @param " << paramName;
            FOR_EACH_CHILD { RECURSE }
            break;
        }
        
        case CXComment_Paragraph: {
            FOR_EACH_CHILD { RECURSE }
            stream << std::endl;
            break;
        }
        
        case CXComment_Text: {
            stream << Extract::unwrap(clang_TextComment_getText(comment));
            break;
        }
        
        case CXComment_BlockCommand: {
            stream << " @" << Extract::unwrap(clang_BlockCommandComment_getCommandName(comment));
            FOR_EACH_CHILD { RECURSE }
            break;
        }
        
        default:
            std::cerr << "warn(4): No support for doc comment #";
            std::cerr << clang_Comment_getKind(comment) << std::endl;
            break;
    }
}
