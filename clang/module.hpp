#pragma once

#include <string>
#include <vector>

#include <clang/Lex/Pragma.h>

namespace luaclang {

struct Module {
    std::string name;
    std::string file;
    
    std::string to_code();
};

class ModulePragmaHandler : public clang::PragmaHandler {
public:
    ModulePragmaHandler(Module& m) : clang::PragmaHandler("module"), _module(m) {}

    virtual void HandlePragma(clang::Preprocessor&, clang::PragmaIntroducer, clang::Token&) override;

private:
    Module _module;
};

} // namespace