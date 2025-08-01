#include "printVisitor.h"

PrintVisitor::PrintVisitor(std::shared_ptr<Program> program) {
    VisitProgram(program.get());
}

llvm::Value * PrintVisitor::VisitProgram(Program *p) {
    for (auto &expr : p->exprVec) {
        expr->Accept(this);
        llvm::outs() << "\n";
    }
    return nullptr;
}

llvm::Value * PrintVisitor::VisitVariableDecl(VariableDecl *decl) {
    if (decl->ty == CType::GetIntTy()) {
        llvm::StringRef text(decl->tok.ptr, decl->tok.len);
        llvm::outs() << "int " << text << ";";
    }
    return nullptr;
}

llvm::Value * PrintVisitor::VisitAssignExpr(AssignExpr *expr) {
    expr->left->Accept(this);
    llvm::outs() << " = ";
    expr->right->Accept(this);
    return nullptr;
}

llvm::Value * PrintVisitor::VisitBinaryExpr(BinaryExpr *binaryExpr) {
    binaryExpr->left->Accept(this);

    switch (binaryExpr->op)
    {
    case OpCode::add: {
        llvm::outs() << " + ";
        break;
    }
    case OpCode::sub:{
        llvm::outs() << " - ";
        break;
    }
    case OpCode::mul:{
        llvm::outs() << " * ";
        break;
    }
    case OpCode::div:{
        llvm::outs() << " / ";
        break;
    }           
    default:
        break;
    }

    binaryExpr->right->Accept(this);

    return nullptr;
}

llvm::Value * PrintVisitor::VisitNumberExpr(NumberExpr *expr) {

    llvm::outs() << llvm::StringRef(expr->tok.ptr, expr->tok.len);

    return nullptr;
}

llvm::Value * PrintVisitor::VisitVariableAccessExpr(VariableAccessExpr *expr) {
    llvm::outs() << llvm::StringRef(expr->tok.ptr, expr->tok.len);
    return nullptr;
}