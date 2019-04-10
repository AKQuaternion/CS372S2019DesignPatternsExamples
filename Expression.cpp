//
// Created by Chris Hartman on 2019-03-27.
//

#include "Expression.hpp"

#include <iostream>
#include <sstream>
#include <string>

BinaryExpression::BinaryExpression(std::unique_ptr<Expression> lhs,
                                   std::unique_ptr<Expression> rhs)
    : _lhs(move(lhs)), _rhs(move(rhs)) {}

int BinaryExpression::evaluate() {
    return operateOn(_lhs->evaluate(), _rhs->evaluate());
}

std::string BinaryExpression::toString() {
    return _lhs->toString() + symbol() + _rhs->toString();
}

int SumExpression::operateOn(int l, int r) {
    return l + r;
}

char SumExpression::symbol() { return '+'; }

int TimesExpression::operateOn(int l, int r) {
    return l * r;
}

char TimesExpression::symbol() { return '*'; }

int MinusExpression::operateOn(int l, int r) {
    return l - r;
}

char MinusExpression::symbol() { return '-'; }

int DivideExpression::operateOn(int l, int r) {
    return l / r;
}

char DivideExpression::symbol() { return '/'; }

int Number::evaluate() {
    return _value;
}

std::string Number::toString() {
    std::ostringstream os;
    os << _value;
    return os.str();
}

void Expression::display() {
    std::cout << toString() << " = " << evaluate() << std::endl;
}
