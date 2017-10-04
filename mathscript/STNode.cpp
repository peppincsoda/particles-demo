#include "STNode.h"

namespace mathscript {

    STExpr::~STExpr()
    {
        for (auto& item : items_) {
            if (item.type == Item::Type::Term && item.term != nullptr) {
                delete item.term;
            }
        }
    }

    void STExpr::Visit(STNodeVisitor &visitor)
    {
        visitor.VisitExpr(*this);
    }

    void STExpr::AddTerm(std::unique_ptr<STTerm>&& term)
    {
        Item item;
        item.type = Item::Type::Term;
        item.term = term.release();
        items_.push_back(item);
    }

    void STExpr::AddOp(TokenType op)
    {
        Item item;
        item.type = Item::Type::Op;
        item.op = op;
        items_.push_back(item);
    }

    void STTerm::Visit(STNodeVisitor &visitor)
    {
        visitor.VisitTerm(*this);
    }

    void STNum::Visit(STNodeVisitor &visitor)
    {
        visitor.VisitNum(*this);
    }

    void STFunc::Visit(STNodeVisitor &visitor)
    {
        visitor.VisitFunc(*this);
    }

}
