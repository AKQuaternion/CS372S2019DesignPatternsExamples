#include <iostream>
using std::cout;
using std::endl;

#include <memory>
using std::unique_ptr;
using std::move;
using std::make_unique;

#include <vector>
using std::vector;

#include <string>
using std::string;

//class Expression {
//public:
//   virtual ~Expression()=default;
//   virtual int evaluate()=0;
//   virtual string print()=0;
//private:
//};
//
//
//class SumExpression : public Expression {
//public:
//   SumExpression(unique_ptr<Expression> lhs, unique_ptr<Expression> rhs)
//      :_lhs(move(lhs)),_rhs(move(rhs))
//   {}
//   virtual int evaluate() override {
//      return _lhs->evaluate()+_rhs->evaluate();
//   }
//private:
//   unique_ptr<Expression> _lhs;
//   unique_ptr<Expression> _rhs;
//};
//
//
//class MinusExpression : public Expression {
//public:
//   MinusExpression(unique_ptr<Expression> lhs, unique_ptr<Expression> rhs)
//         :_lhs(move(lhs)),_rhs(move(rhs))
//   {}
//   virtual int evaluate() override {
//      return _lhs->evaluate()-_rhs->evaluate();
//   }
//private:
//   unique_ptr<Expression> _lhs;
//   unique_ptr<Expression> _rhs;
//};
//
//
//class TimesExpression : public Expression {
//public:
//   TimesExpression(unique_ptr<Expression> lhs, unique_ptr<Expression> rhs)
//         :_lhs(move(lhs)),_rhs(move(rhs))
//   {}
//   virtual int evaluate() override {
//      return _lhs->evaluate()*_rhs->evaluate();
//   }
//private:
//   unique_ptr<Expression> _lhs;
//   unique_ptr<Expression> _rhs;
//};
//
//
//class DivideExpression : public Expression {
//public:
//   DivideExpression(unique_ptr<Expression> lhs, unique_ptr<Expression> rhs)
//         :_lhs(move(lhs)),_rhs(move(rhs))
//   {}
//   virtual int evaluate() override {
//      return _lhs->evaluate()/_rhs->evaluate();
//   }
//private:
//   unique_ptr<Expression> _lhs;
//   unique_ptr<Expression> _rhs;
//};
//
//class Number : public Expression {
//public:
//   Number(int value):_value(value)
//   {}
//   virtual int evaluate() override {
//      return _value;
//   }
//private:
//   int _value;
//};
//
//
//int expressionExample() {
//unique_ptr<Expression> two = make_unique<Number>(2);
//auto three = make_unique<Number>(3);
//auto twoPlusThree = make_unique<SumExpression>(move(two),move(three));
//std::cout << twoPlusThree->evaluate() << std::endl;
//auto five=make_unique<Number>(5);
//TimesExpression e(move(twoPlusThree),move(five));
//std::cout << e.evaluate() << std::endl;
//}

class Inventory {
public:
   virtual ~Inventory() = default;
   virtual int getWeight() = 0;
   virtual vector<unique_ptr<Inventory>> getChildren() {
      return {};
   }
private:
};

class Item : public Inventory {
public:
   Item(int weight):_weight(weight)
   {}

   virtual int getWeight() override {
      return _weight;
   }
private:
   int _weight;
};

class Bag : public Inventory {
public:
   virtual int getWeight() override {
      auto weight=0;
      for(const auto &c:_contents)
         weight += c->getWeight();
      return weight;
   }
   void add(unique_ptr<Inventory> i) {
      _contents.push_back(move(i));
   }
private:
   vector<unique_ptr<Inventory>> _contents;
};

int main() {
   auto sword = make_unique<Item>(5);
   cout << sword->getWeight() << endl;
   auto backpack = make_unique<Bag>();
   backpack->add(move(sword));
   backpack->add(make_unique<Item>(13));
   cout << backpack->getWeight() << endl;
   auto backpack2 = make_unique<Bag>();
   backpack2->add(move(backpack2));
   backpack2->add(make_unique<Item>(12));
   cout << backpack2->getWeight() << endl;

   return 0;
}