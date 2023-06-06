#include <clang/Lex/Token.h>
#include <clang/Lex/Preprocessor.h>
#include <llvm/

#include "module.hpp"

namespace luaclang {

void ModulePragmaHandler::HandlePragma(clang::Preprocessor& preproc, clang::PragmaIntroducer intro, clang::Token& token) {
    auto loc = token.getLocation();
    auto& sm = preproc.getSourceManager();

    //llvm::outs << "Found lua module pragma at " << loc.printToString(preproc.getSourceManager()) << '\n';

}

}