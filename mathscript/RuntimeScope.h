#ifndef RUNTIMESCOPE_H
#define RUNTIMESCOPE_H

#include <stack>
#include <string>
#include <memory>
#include <functional>
#include <unordered_map>

namespace mathscript {

    class RuntimeContext
    {
    public:
        RuntimeContext();
        ~RuntimeContext();

        void Push(double val);
        double Pop();

        int ip() const;
        void set_ip(int ip);

    private:
        std::stack<double> stack_;
        int ip_;
    };

    class FuncInterface
    {
    public:
        virtual ~FuncInterface() {}
        virtual void Call(RuntimeContext& context) = 0;
        virtual int GetNumParams() const = 0;
    };

    //! The runtime scope contains the available functions and their semantics for the program.
    class RuntimeScope
    {
    public:
        //! Construct a scope containing the default functions.
        RuntimeScope();
        //! Construct a scope by explicitly parenting it to another scope.
        explicit RuntimeScope(RuntimeScope* parent);

        RuntimeScope(const RuntimeScope&) = delete;
        RuntimeScope& operator=(const RuntimeScope&) = delete;

        FuncInterface* GetFunc(const std::string& name);

        //! Add a generic function to the scope.
        void SetFunc(const std::string& name, std::unique_ptr<FuncInterface>&& func);
        //! Hide the given name in this scope.
        //! All references to this name in the code will cause a runtime exception to be thrown.
        void SetFunc(const std::string& name, std::nullptr_t);

        //! Shortcuts to define functions using lambdas.
        void SetFunc(const std::string& name, std::function<double ()>&& fn);
        void SetFunc(const std::string& name, std::function<double (double)>&& fn);
        void SetFunc(const std::string& name, std::function<double (double, double)>&& fn);

    private:
        RuntimeScope* parent_;

        std::unordered_map<std::string, std::unique_ptr<FuncInterface>> functions_;
    };

}

#endif // RUNTIMESCOPE_H
