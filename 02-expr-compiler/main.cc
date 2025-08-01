#include "lexer.h"
#include "iostream"
#include "llvm/Support/MemoryBuffer.h"
#include "llvm/Support/ErrorOr.h"
#include "parser.h"
#include "printVisitor.h"
#include "codegen.h"

int main(int argc, char** argv ){
    if(argc < 2){
        
        std::cout<<"please input filename!"<<std::endl;
        return 0;
    }

    const char *file_name = argv[1];

    static llvm::ErrorOr<std::unique_ptr<llvm::MemoryBuffer>> buf = llvm::MemoryBuffer::getFile(file_name);
    if (!buf) {
        llvm::errs() << "can't open file!!!\n";
        return -1;
    }

    std::unique_ptr<llvm::MemoryBuffer> memBuf = std::move(*buf);
    Lexer lex(memBuf->getBuffer());
    
    Token tok;
    while (true) {
        lex.NextToken(tok);
        if (tok.tokenType != TokenType::eof)
            tok.Dump();
        else {
            break;
        }
    }

    Lexer lex_1(memBuf->getBuffer());
    Parser parser(lex_1);
    auto program = parser.ParseProgram();
    PrintVisitor printVisitor(program);
    CodeGen codegen(program);

    return 0;
}