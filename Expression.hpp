//
// Created by Chris Hartman on 2019-03-27.
//

#ifndef CS372S2019DESIGNPATTERNSEXAMPLES_EXPRESSION_HPP
#define CS372S2019DESIGNPATTERNSEXAMPLES_EXPRESSION_HPP

#include <memory>

class Expression {
public:
   virtual ~Expression() = default;

   virtual int evaluate() = 0;
//   virtual string print()=0;
private:
};


class SumExpression : public Expression {
public:
   SumExpression(std::unique_ptr<Expression> lhs, std::unique_ptr<Expression> rhs);

   virtual int evaluate() override;

private:
   std::unique_ptr<Expression> _lhs;
   std::unique_ptr<Expression> _rhs;
};


class MinusExpression : public Expression {
public:
   MinusExpression(std::unique_ptr<Expression> lhs, std::unique_ptr<Expression> rhs);

   virtual int evaluate() override;

private:
   std::unique_ptr<Expression> _lhs;
   std::unique_ptr<Expression> _rhs;
};


class TimesExpression : public Expression {
public:
   TimesExpression(std::unique_ptr<Expression> lhs, std::unique_ptr<Expression> rhs);

   virtual int evaluate() override;

private:
   std::unique_ptr<Expression> _lhs;
   std::unique_ptr<Expression> _rhs;
};


class DivideExpression : public Expression {
public:
   DivideExpression(std::unique_ptr<Expression> lhs, std::unique_ptr<Expression> rhs);

   virtual int evaluate() override;

private:
   std::unique_ptr<Expression> _lhs;
   std::unique_ptr<Expression> _rhs;
};

class Number : public Expression {
public:
   Number(int value) : _value(value) {}

   virtual int evaluate() override;

private:
   int _value;
};


#endif //CS372S2019DESIGNPATTERNSEXAMPLES_EXPRESSION_HPP
