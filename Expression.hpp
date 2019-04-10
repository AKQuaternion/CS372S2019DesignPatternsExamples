//
// Created by Chris Hartman on 2019-03-27.
//

#ifndef CS372S2019DESIGNPATTERNSEXAMPLES_EXPRESSION_HPP
#define CS372S2019DESIGNPATTERNSEXAMPLES_EXPRESSION_HPP

#include <memory>
#include <string>

class Expression {
public:
   virtual ~Expression() = default;

   virtual int evaluate() = 0;
   virtual std::string toString() = 0;

   void display();

  private:
};

class BinaryExpression : public Expression {
   public:
    BinaryExpression(std::unique_ptr<Expression> lhs, std::unique_ptr<Expression> rhs);

    int evaluate() override;
    std::string toString() override;

    virtual int operateOn(int, int) = 0;
    virtual char symbol() = 0;

   private:
    std::unique_ptr<Expression> _lhs;
    std::unique_ptr<Expression> _rhs;
};

class SumExpression : public BinaryExpression {
   public:
    using BinaryExpression::BinaryExpression;

    int operateOn(int, int) override;
    char symbol() override;
};

class MinusExpression : public BinaryExpression {
   public:
    using BinaryExpression::BinaryExpression;

    int operateOn(int, int) override;
    char symbol() override;
};

class TimesExpression : public BinaryExpression {
   public:
    using BinaryExpression::BinaryExpression;

    int operateOn(int, int) override;
    char symbol() override;
};

class DivideExpression : public BinaryExpression {
   public:
    using BinaryExpression::BinaryExpression;

    int operateOn(int, int) override;
    char symbol() override;
};

class Number : public Expression {
public:
    explicit Number(int value) : _value(value) {}

    int evaluate() override;
    std::string toString() override;

   private:
   int _value;
};


#endif //CS372S2019DESIGNPATTERNSEXAMPLES_EXPRESSION_HPP
