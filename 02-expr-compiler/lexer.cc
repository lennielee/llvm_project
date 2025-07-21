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
    
    
    while(IsWhiteSpace(*BufPtr)){
        if (*BufPtr == '\n') {
            row++;
            LineHeadPtr = BufPtr+1;
        }
        BufPtr++;
        return;
    }

    
    
    if(BufPtr >= BufEnd){

        tok.tokenType = TokenType::eof;
        return;
    }


    tok.row = row;
    tok.col = BufPtr - LineHeadPtr + 1;

    const char *start = BufPtr;

    if(IsDigit(*BufPtr)){
        
        int len = 0;
        int number = 0;
        while(IsDigit(*BufPtr)){
            number = number * 10 + (*BufPtr++ - '0');
            len++;
        }
        tok.tokenType = TokenType::number;
        tok.value = number;
        tok.content = llvm::StringRef(start, len);
    }else {
        switch(*BufPtr)
        {
            case '+':{
                tok.tokenType = TokenType::plus;
                tok.content = llvm::StringRef(start, 1);
                BufPtr++;
                break;
            }
            case '-': {
                tok.tokenType = TokenType::minus;
                BufPtr++;
                tok.content = llvm::StringRef(start, 1);
                break;
            }
            case '*':{
                tok.tokenType = TokenType::star;
                BufPtr++;
                tok.content = llvm::StringRef(start, 1);
                break;
            }
            case '/':{
                tok.tokenType = TokenType::slash;
                BufPtr++;
                tok.content = llvm::StringRef(start, 1);
                break;
            }
            case ';':{
                tok.tokenType = TokenType::semi;
                BufPtr++;
                tok.content = llvm::StringRef(start, 1);
                break;
            }
            case '(':{
                tok.tokenType = TokenType::l_parent;
                BufPtr++;
                tok.content = llvm::StringRef(start, 1);
                break;
            }
            case ')':{
                tok.tokenType = TokenType::r_parent;
                BufPtr++;
                tok.content = llvm::StringRef(start, 1);
                break;
            } 


            default:{
                tok.tokenType = TokenType::unknown;
                break;
            }
            
        }

    }

}