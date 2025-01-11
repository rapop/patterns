#include <iostream>
#include <unordered_map>

// the context contains the mapping
class Context
{
public:
    void set(const std::string& name, double price)
    {
        prices_[name] = price;
    }
    double get(const std::string& name) const 
    {
        return prices_[name];
    }
private:
    mutable std::unordered_map<std::string, double> prices_;
};


// Abstract Expression
struct Expression
{   
    virtual ~Expression() = default;
    virtual double interpret(const Context* context) const = 0;
};

// the terminal expression
class EvaluateExpression : public Expression
{
public:
    EvaluateExpression(const std::string& name)
    : name_(name)
    {}

    double interpret(const Context* context) const override
    {
        return context->get(name_);
    }
private:
    const std::string name_;
};

// non terminal expressions
class AddExpression : public Expression
{
public:
    // takes as arguments other expressions
    AddExpression(const Expression* left_exp, const Expression* right_exp)
    : left_exp_(left_exp),
      right_exp_(right_exp)
    {}

    double interpret(const Context* context) const override
    {
        return left_exp_->interpret(context) + right_exp_->interpret(context);
    }
private:
    const Expression* left_exp_;
    const Expression* right_exp_;
};

class MultiplyExpression : public Expression
{
public:
    // takes as arguments other expressions
    MultiplyExpression(const Expression* left_exp, const Expression* right_exp)
    : left_exp_(left_exp),
      right_exp_(right_exp)
    {}

    double interpret(const Context* context) const override
    {
        return left_exp_->interpret(context) * right_exp_->interpret(context);
    }
private:
    const Expression* left_exp_;
    const Expression* right_exp_;
};

int main()
{   
    // the expression stays the same, but it can be interpreted differently based on the context that is passed.
    EvaluateExpression sauna("sauna");
    EvaluateExpression wood_door("wood_door");
    EvaluateExpression taxe("taxe");
    AddExpression spa(&sauna, &wood_door);
    MultiplyExpression mult(&spa, &taxe);

    // the interpretations are given by the context
    Context context;
    context.set("sauna", 5999.99);
    context.set("wood_door", 41.2);
    context.set("taxe", 1.2);

    std::cout << mult.interpret(&context) << std::endl;

    return 0;
}