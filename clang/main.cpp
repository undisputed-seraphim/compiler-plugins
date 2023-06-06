#include <clang/Frontend/CommandLineSourceLoc.h>
#include <clang/Frontend/PrecompiledPreamble.h>
#include <clang/Lex/Preprocessor.h>
#include <clang/Rewrite/Core/Rewriter.h>
#include <clang/Frontend/FrontendPluginRegistry.h>
#include <clang/Tooling/CommonOptionsParser.h>
#include <clang/Tooling/Tooling.h>
#include <memory>


int main(int argc, const char* argv[]) try {
    auto clangptr = std::make_unique<clang::CompilerInstance>();

} catch (const std::exception& e) {
    return -1;
}