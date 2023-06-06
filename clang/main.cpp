#include <clang/Lex/Preprocessor.h>
#include <clang/Rewrite/Core/Rewriter.h>
#include <clang/Frontend/FrontendPluginRegistry.h>

class ASTConsumer : public clang::ASTConsumer {
public:
    ASTConsumer(clang::CompilerInstance& ci, clang::Rewriter& rw, )
};

class LuaClang : public clang::PluginASTAction {
public:
    std::unique_ptr<clang::ASTConsumer> CreateASTConsumer(clang::CompilerInstance& ci, llvm::StringRef filename) override {
        _rewriter.setSourceMgr(ci.getSourceManager(), ci.getLangOpts());
        _filename = filename.str();
        return std::make_unique<ASTConsumer>(ci, _rewriter, );
    }

    bool ParseArgs(const clang::CompilerInstance&, const std::vector<std::string>&) override {
        return true;
    }

    clang::PluginASTAction::ActionType getActionType() override {
        return clang::PluginASTAction::ReplaceAction;
    }

    void EndSourceFileAction() override {

    }

private:
    clang::Rewriter _rewriter;
    std::string _filename;
};

static clang::FrontendPluginRegistry::Add<LuaClang> X("luaclang", "Plugin for automating the creation of lua modules");