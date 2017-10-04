#include "STNodePrintVisitor.h"

namespace mathscript {

    void STNodePrintVisitor::VisitExpr(STExpr& expr)
    {
        for (const auto& item : expr.items_) {
            VisitExprItem(item);
        }
    }

    void STNodePrintVisitor::VisitExprItem(const STExpr::Item& item)
    {
        if (item.type == STExpr::Item::Type::Op) {
            VisitOp(item.op);
        } else if (item.type == STExpr::Item::Type::Term) {
            VisitTerm(*item.term);
        }
    }

    void STNodePrintVisitor::VisitOp(TokenType op)
    {
        switch (op) {
        case TokenType::Plus:     s_ << '+'; break;
        case TokenType::Minus:    s_ << '-'; break;
        case TokenType::Asterisk: s_ << '*'; break;
        case TokenType::Slash:    s_ << '/'; break;
        case TokenType::Caret:    s_ << '^'; break;
        default:
            s_ << "???";
            break;
        }
    }

    void STNodePrintVisitor::VisitTerm(STTerm& term)
    {
        s_ << '(';
        for (const auto& op : term.unary_ops_) {
            VisitOp(op);
        }
        term.operand_->Visit(*this);
        s_ << ')';
    }

    void STNodePrintVisitor::VisitNum(STNum& num)
    {
        s_ << num.dbl_val_;
    }

    void STNodePrintVisitor::VisitFunc(STFunc& func)
    {
        s_ << func.name_ << '(';
        auto b = false;
        for (const auto& param : func.params_) {
            if (b) {
                s_ << ',';
            }
            VisitExpr(*param);
            b = true;
        }
        s_ << ')';
    }

    STNodePrintVisitor::STNodePrintVisitor(std::ostream& s)
        : s_(s)
    {

    }

}
