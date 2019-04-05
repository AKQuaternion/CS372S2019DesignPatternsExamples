//
// Created by Chris Hartman on 2019-03-27.
//

#include "Expression.hpp"

MinusExpression::MinusExpression(std::unique_ptr<Expression> lhs,
                                 std::unique_ptr<Expression> rhs)
    : _lhs(move(lhs)), _rhs(move(rhs)) {}

int MinusExpression::evaluate() {
    return _lhs->evaluate() - _rhs->evaluate();
}

TimesExpression::TimesExpression(std::unique_ptr<Expression> lhs, std::unique_ptr<Expression> rhs)
    : _lhs(move(lhs)), _rhs(move(rhs)) {}

int TimesExpression::evaluate() {
    return _lhs->evaluate() * _rhs->evaluate();
}

DivideExpression::DivideExpression(std::unique_ptr<Expression> lhs, std::unique_ptr<Expression> rhs)
    : _lhs(move(lhs)), _rhs(move(rhs)) {}

int DivideExpression::evaluate() {
    return _lhs->evaluate() / _rhs->evaluate();
}

int Number::evaluate() {
    return _value;
}

int BinaryExpression::evaluate() {
    return operateOn(_lhs->evaluate(), _rhs->evaluate());
}

BinaryExpression::BinaryExpression(std::unique_ptr<Expression> lhs, std::unique_ptr<Expression> rhs)
    : _lhs(move(lhs)), _rhs(move(rhs)) {
}

int SumExpression::operateOn(int l, int r) {
    return l + r;
}
