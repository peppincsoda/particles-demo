#include "STSerializer.h"

#include <sstream>

namespace mathscript {

    class STSerializerVisitor : public STNodeVisitor
    {
    public:
        explicit STSerializerVisitor(std::ostream& os)
            : os_(os)
        {

        }

        void VisitExpr(STExpr& expr) override
        {
            for (const auto& item : expr.items_) {
                if (item.type == STExpr::Item::Type::Term) {
                    item.term->Visit(*this);

                } else {
                    os_ << TokenTypeStr(item.op);
                }
            }
        }

        void VisitTerm(STTerm& term) override
        {
            term.operand_->Visit(*this);

            for (const auto& op : term.unary_ops_) {
                os_ << TokenTypeStr(op);
            }
        }

        void VisitNum(STNum& num) override
        {
            os_ << '(' << num.dbl_val_ << ')';
        }

        void VisitFunc(STFunc& func) override
        {
            for (const auto& param : func.params_) {
                param->Visit(*this);
            }

            os_ << func.name_;
        }

    private:
        std::ostream& os_;
    };


    void SerializeST(STNode& node, std::ostream& os)
    {
        STSerializerVisitor visitor(os);
        node.Visit(visitor);
    }

    std::string SerializeST(STNode& node)
    {
        std::ostringstream os;
        SerializeST(node, os);
        return os.str();
    }
}
