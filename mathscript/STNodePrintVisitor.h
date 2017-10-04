#ifndef STNODEDEBUG_H
#define STNODEDEBUG_H

#include "STNode.h"

#include <ostream>

namespace mathscript {

    class STNodePrintVisitor : public STNodeVisitor
    {
    public:
        explicit STNodePrintVisitor(std::ostream& s);

        void VisitExpr(STExpr& expr) override;
        void VisitTerm(STTerm& term) override;
        void VisitNum(STNum& num) override;
        void VisitFunc(STFunc& func) override;

        void VisitExprItem(const STExpr::Item& item);
        void VisitOp(TokenType op);

    private:
        std::ostream& s_;
    };

}

#endif // STNODEDEBUG_H
