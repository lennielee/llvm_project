#include "lexer.h"


bool IsWhiteSpace(char ch) {
    return ch == ' ' || ch == '\r' || ch == '\n';
}

bool IsDigit(char ch) {
    return (ch >= '0' && ch <= '9');
}

Lexer::Lexer(llvm::StringRef sourceCode){
    LineHeadPtr = sourceCode.begin();
    BufPtr = sourceCode.begin();
    BufEnd = sourceCode.end();
    row = 1;

}


void Lexer::NextToken(Token &tok){
    tok.row = row;
    

    while(IsWhiteSpace(*BufPtr)){
        if (*BufPtr == '\n') {
            row++;
            LineHeadPtr = BufPtr+1;
        }
        BufPtr++;
    }

    tok.col = BufPtr - LineHeadPtr + 1;
    
    if(BufPtr >= BufEnd){

        tok.tokenType = TokenType::eof;
        return;
    }
    if(IsDigit(*BufPtr)){

        int number = 0;
        while(IsDigit(*BufPtr)){
            number = number * 10 + (*BufPtr++ - '0');
        }
        tok.tokenType = TokenType::number;
        tok.value = number;
        
    }else {


    }

}