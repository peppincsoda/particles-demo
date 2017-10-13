#ifndef STNODE_H
#define STNODE_H

#include "TokenType.h"

#include <vector>
#include <memory>
#include <string>

namespace mathscript {

    class STExpr;
    class STTerm;
    class STNum;
    class STFunc;

    //! Abstract AST node visitor.
    class STNodeVisitor
    {
    public:
        STNodeVisitor() {}

        virtual ~STNodeVisitor() {}
        virtual void VisitExpr(STExpr& expr) = 0;
        virtual void VisitTerm(STTerm& term) = 0;
        virtual void VisitNum(STNum& num) = 0;
        virtual void VisitFunc(STFunc& func) = 0;

        STNodeVisitor(const STNodeVisitor&) = delete;
        STNodeVisitor& operator=(const STNodeVisitor&) = delete;
    };

    //! AST node base class.
    struct STNode
    {
        STNode() {}

        virtual ~STNode() {}
        virtual void Visit(STNodeVisitor& visitor) = 0;

        STNode(const STNode&) = delete;
        STNode& operator=(const STNode&) = delete;
    };

    //! AST expression node: contains binary operators and subexpressions in RPN.
    struct STExpr : public STNode
    {
        ~STExpr();

        void Visit(STNodeVisitor& visitor) override;

        void AddTerm(std::unique_ptr<STNode>&& term);
        void AddOp(TokenType op);

        struct Item
        {
            enum class Type
            {
                Term,
                Op,
            };

            Type type;
            union
            {
                TokenType op;
                STNode* term;
            };
        };

        std::vector<Item> items_;
    };

    //! AST term node: contains unary operators in reversed order of application and the operand.
    struct STTerm : public STNode
    {
        void Visit(STNodeVisitor& visitor) override;

        std::vector<TokenType> unary_ops_;
        std::unique_ptr<STNode> operand_;
    };

    //! AST constant node
    struct STNum : public STNode
    {
        void Visit(STNodeVisitor& visitor) override;

        double dbl_val_;
    };

    //! AST function node: parameters are stored in reverse order.
    struct STFunc : public STNode
    {
        void Visit(STNodeVisitor& visitor) override;

        std::string name_;
        std::vector<std::unique_ptr<STNode>> params_;
    };

}


#endif // STNODE_H
