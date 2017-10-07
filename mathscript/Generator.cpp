#include "Generator.h"

#include <cassert>

namespace mathscript {

    class STCodeGenVisitor : public STNodeVisitor
    {
    public:
        STCodeGenVisitor(Program& program)
            : program_(program)
        {

        }

        void VisitExpr(STExpr& expr) override
        {
            for (const auto& item : expr.items_) {
                if (item.type == STExpr::Item::Type::Term) {
                    item.term->Visit(*this);

                } else {
                    switch (item.op) {
                    case TokenType::Plus:
                        program_.EmitCallFunc("__add__");
                        break;
                    case TokenType::Minus:
                        program_.EmitCallFunc("__sub__");
                        break;
                    case TokenType::Asterisk:
                        program_.EmitCallFunc("__mul__");
                        break;
                    case TokenType::Slash:
                        program_.EmitCallFunc("__div__");
                        break;
                    case TokenType::Caret:
                        program_.EmitCallFunc("__pow__");
                        break;
                    default:
                        assert(0);
                    }
                }
            }
        }

        void VisitTerm(STTerm& term) override
        {
            term.operand_->Visit(*this);

            for (const auto& op : term.unary_ops_) {
                switch (op) {
                case TokenType::Plus:
                    program_.EmitCallFunc("__pos__");
                    break;
                case TokenType::Minus:
                    program_.EmitCallFunc("__neg__");
                    break;
                default:
                    assert(0);
                }
            }
        }

        void VisitNum(STNum& num) override
        {
            program_.EmitPushConst(num.dbl_val_);
        }

        void VisitFunc(STFunc& func) override
        {
            for (const auto& param : func.params_) {
                param->Visit(*this);
            }

            program_.EmitCallFunc(func.name_);
        }

    private:
        Program& program_;
    };


    void GenerateCode(STNode& node, Program& program)
    {
        STCodeGenVisitor visitor(program);
        node.Visit(visitor);
    }

}
