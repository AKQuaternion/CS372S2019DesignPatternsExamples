#include <iostream>

using std::cout;
using std::endl;

#include <memory>
using std::make_unique;
using std::move;
using std::unique_ptr;
using std::shared_ptr;
using std::unique_ptr;

#include <vector>

using std::vector;

using std::string;
#include <functional>
using std::function;

#include <numeric>

#include "Expression.hpp"

#include "Command.hpp"
#include "Door.hpp"
#include "HomeAutomationComponent.hpp"

class Item;
class Bag;

class Visitor {
   public:
    virtual void visit(Item *) = 0;
    virtual void visit(Bag *) = 0;

    virtual ~Visitor() = default;

   private:
};

class Inventory {
   public:
    virtual ~Inventory() = default;

    virtual int getWeight() = 0;
    virtual vector<unique_ptr<Inventory>> getChildren() { return {}; }
    virtual void accept(Visitor *) = 0;

   private:
};

class Item : public Inventory {
   public:
    explicit Item(int weight) : _weight(weight) {}
    void accept(Visitor *v) override { v->visit(this); }
    int getWeight() override { return _weight; }
    void setWeight(int w) { _weight = w; }

   private:
    int _weight;
};

class Bag : public Inventory {
   public:
    int getWeight() override {
        return std::accumulate(
            begin(_contents), end(_contents), 0,
            [](auto sum, const auto &item) { return sum + item->getWeight(); });
        //        auto weight = 0;
        //        for (const auto &c : _contents)
        //            weight += c->getWeight();
        //        return weight;
    }

    void accept(Visitor *v) override { v->visit(this); }

    void add(unique_ptr<Inventory> i) { _contents.push_back(move(i)); }

   private:
    vector<unique_ptr<Inventory>> _contents;
};

void demonstrateComposite();

void demonstrateExpression();

class Armor {
   public:
    virtual ~Armor() = default;
    virtual string description() const = 0;
    virtual int getAC() const = 0;
};

class LeatherArmor : public Armor {
   public:
    string description() const override { return "Leather Armor"; }
    int getAC() const override { return 3; }
};

class PlateArmor : public Armor {
   public:
    string description() const override { return "Plate Armor"; }
    int getAC() const override { return 8; }
};

class ArmorDecorator : public Armor {
   public:
    explicit ArmorDecorator(unique_ptr<Armor> wrappee)
        : _wrappee(move(wrappee)) {}

   protected:
    string description() const override { return _wrappee->description(); }
    int getAC() const override { return _wrappee->getAC(); }

   private:
    unique_ptr<Armor> _wrappee;
};

class RustyArmorDecorator : public ArmorDecorator {
    using ArmorDecorator::ArmorDecorator;
    string description() const override {
        return "Rusty " + ArmorDecorator::description();
    }
    int getAC() const override { return ArmorDecorator::getAC() - 2; }
};

void demonstrateDecorator();

void checkPassword(shared_ptr<HomeAutomationComponent> hac) {
    cout << "What's the password? ";
    string password;
    std::cin >> password;
    if (password == "password")
        hac->on();
    else
        cout << "Wrong!\n";
}
int main() {
    //    demonstrateComposite();
    //    demonstrateExpression();
    //    demonstrateDecorator();

    auto f = make_shared<Fan>();
    //    checkPassword(f);
    //
    auto d = make_shared<GarageDoor>();
    //
    //    d->open();
    //    d->close();
    auto dc = make_shared<DoorComponent>(d);

    vector<shared_ptr<Command>> remote(10, make_shared<NullCommand>());
    remote[0] = make_shared<SayHiCommand>();
    remote[1] = make_shared<OpenDoor>(d);
    remote[9] = make_shared<ExitCommand>();
    remote[2] = make_shared<HACOnCommand>(f);
    remote[3] = make_shared<LambdaCommand>([]() { cout << "Monday...\n"; });
    remote[4] = make_shared<MacroCommand>(
        vector<shared_ptr<Command>>{remote[0], remote[1], remote[3]});
    while (1) {
        cout << "Which command? ";
        int commandNumber;
        std::cin >> commandNumber;
        remote[commandNumber]->execute();
    }
    return 0;
}

void describe(const Armor &a) {
    cout << a.description() << " has AC " << a.getAC() << "\n";
}

void demonstrateDecorator() {
    unique_ptr<Armor> p = make_unique<PlateArmor>();
    describe(*p);
    unique_ptr<Armor> l = make_unique<LeatherArmor>();
    describe(*l);
    unique_ptr<Armor> rp = make_unique<RustyArmorDecorator>(move(p));
    describe(*rp);
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
    e.display();
}

class doubleWeightVisitor : public Visitor {
    void visit(Item *i) override { i->setWeight(i->getWeight() * 2); }
    void visit(Bag *b) override {
        for (auto &c : b->getChildren()) c->accept(this);
    }
};