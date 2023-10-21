#include <clang/Frontend/CommandLineSourceLoc.h>
#include <clang/Frontend/FrontendPluginRegistry.h>
#include <clang/Frontend/PrecompiledPreamble.h>
#include <clang/Frontend/CompilerInstance.h>
#include <clang/Lex/Preprocessor.h>
#include <clang/Rewrite/Core/Rewriter.h>
#include <clang/Tooling/CommonOptionsParser.h>
#include <clang/Tooling/Tooling.h>
#include <memory>

int main(int argc, const char* argv[]) try {
	auto clangptr = std::make_unique<clang::CompilerInstance>();
	clangptr->createDiagnostics();
	std::shared_ptr<clang::TargetOptions> TO(new clang::TargetOptions());

	clangptr->setTarget(clang::TargetInfo::CreateTargetInfo(Clang->getDiagnostics(), TO));
	clangptr->createFileManager();
	clangptr->createSourceManager(clangptr->getFileManager());
	clangptr->createPreprocessor(clang::TU_Complete);
	clangptr->createASTContext();
	clang::ASTContext& Context = clangptr->getASTContext();
	clang::IdentifierTable& Identifiers = clangptr->getPreprocessor().getIdentifierTable();

	// AST building
	clang::TranslationUnitDecl* TopDecl = Context.getTranslationUnitDecl();

	std::vector<clang::QualType> ArgsTy;
	ArgsTy.push_back(Context.DoubleTy);
	clang::QualType FTy = Context.getFunctionType(Context.IntTy, ArrayRef<clang::QualType>(ArgsTy), clang::FunctionProtoType::ExtProtoInfo());
	/* function decl */ {
		clang::FunctionDecl* FD = clang::FunctionDecl::Create(
			Context,
			TopDecl,
			clang::SourceLocation(),
			clang::SourceLocation(),
			clang::DeclarationName(&Identifiers.get("myfunction")),
			FTy,
			NULL,
			clang::SC_None,
			/*inline*/ false);
		std::vector<clang::ParmVarDecl*> NewParamInfo;
		NewParamInfo.push_back(clang::ParmVarDecl::Create(
			Context, FD, clang::SourceLocation(), clang::SourceLocation(), &Identifiers.get("arg1"), Context.DoubleTy, NULL, clang::SC_None, NULL));
		FD->setParams(ArrayRef<clang::ParmVarDecl*>(NewParamInfo));
		TopDecl->addDecl(FD);
	}

	/* function body */ {
		clang::FunctionDecl* FD = clang::FunctionDecl::Create(
			Context,
			TopDecl,
			clang::SourceLocation(),
			clang::SourceLocation(),
			clang::DeclarationName(&Identifiers.get("myfunction")),
			FTy,
			NULL,
			clang::SC_None,
			/*inline*/ false);
		std::vector<clang::ParmVarDecl*> NewParamInfo;
		NewParamInfo.push_back(clang::ParmVarDecl::Create(
			Context, FD, clang::SourceLocation(), clang::SourceLocation(), &Identifiers.get("arg1"), Context.DoubleTy, NULL, clang::SC_None, NULL));
		FD->setParams(ArrayRef<clang::ParmVarDecl*>(NewParamInfo));
		clang::CompoundStmt* CS = new (Context) clang::CompoundStmt(clang::SourceLocation());
		clang::Stmt* S = new (Context) clang::ReturnStmt(
			clang::SourceLocation(), clang::FloatingLiteral::Create(Context, APFloat(12.345), true, Context.DoubleTy, clang::SourceLocation()), NULL);
		CS->setStmts(Context, &S, 1);
		FD->setBody(CS);
		TopDecl->addDecl(FD);
	}

	// Decl printing
	llvm::outs() << "-ast-print: \n";
	Context.getTranslationUnitDecl()->print(llvm::outs());
	llvm::outs() << "\n";

	llvm::outs() << "-ast-dump: \n";
	Context.getTranslationUnitDecl()->dump(llvm::outs());
	llvm::outs() << "\n";

	return 0;
} catch (const std::exception& e) {
	return -1;
}