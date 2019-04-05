//
// Created by Chris Hartman on 2019-03-27.
//

#include "Expression.hpp"

int BinaryExpression::evaluate() {
    return operateOn(_lhs->evaluate(), _rhs->evaluate());
}

BinaryExpression::BinaryExpression(std::unique_ptr<Expression> lhs, std::unique_ptr<Expression> rhs)
    : _lhs(move(lhs)), _rhs(move(rhs)) {
}

int SumExpression::operateOn(int l, int r) {
    return l + r;
}

int TimesExpression::operateOn(int l, int r) {
    return l * r;
}

int MinusExpression::operateOn(int l, int r) {
    return l - r;
}

int DivideExpression::operateOn(int l, int r) {
    return l / r;
}

int Number::evaluate() {
    return _value;
}
