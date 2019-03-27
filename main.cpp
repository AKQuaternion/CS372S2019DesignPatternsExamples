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

#include "Expression.hpp"

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
   Item(int weight) : _weight(weight) {}

   virtual int getWeight() override {
      return _weight;
   }

private:
   int _weight;
};

class Bag : public Inventory {
public:
   virtual int getWeight() override {
      auto weight = 0;
      for (const auto &c:_contents)
         weight += c->getWeight();
      return weight;
   }

   void add(unique_ptr<Inventory> i) {
      _contents.push_back(move(i));
   }

private:
   vector<unique_ptr<Inventory>> _contents;
};

void demonstrateComposite();

void demonstrateExpression();

int main() {
   demonstrateComposite();
   demonstrateExpression();
   return 0;
}

void demonstrateComposite() {
   auto sword = make_unique<Item>(5);
   cout << sword->getWeight() << endl;
   auto backpack = make_unique<Bag>();
   backpack->add(move(sword));
   backpack->add(make_unique<Item>(13));
   cout << backpack->getWeight() << endl;
   auto backpack2 = make_unique<Bag>();
   backpack2->add(make_unique<Item>(12));
   cout << backpack2->getWeight() << endl;
}

void demonstrateExpression() {
   unique_ptr<Expression> two = make_unique<Number>(2);
   auto three = make_unique<Number>(3);
   auto twoPlusThree = make_unique<SumExpression>(move(two), move(three));
   std::cout << twoPlusThree->evaluate() << std::endl;
   auto five = make_unique<Number>(5);
   TimesExpression e(move(twoPlusThree), move(five));
   std::cout << e.evaluate() << std::endl;
}
