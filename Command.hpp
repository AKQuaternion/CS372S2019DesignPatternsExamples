//
// Created by Chris Hartman on 2019-04-19.
//

#ifndef CS372S2019DESIGNPATTERNSEXAMPLES_COMMAND_HPP
#define CS372S2019DESIGNPATTERNSEXAMPLES_COMMAND_HPP

#include <functional>
#include <iostream>
#include <vector>
#include "Door.hpp"
#include "HomeAutomationComponent.hpp"

class Command {
   public:
    virtual ~Command() = default;
    virtual void execute() = 0;
};

class SayHiCommand : public Command {
   public:
    void execute() override { std::cout << "Hi!\n"; }
};

class OpenDoor : public Command {
   public:
    OpenDoor(DoorPtr door) : _door(door) {}

    void execute() override { _door->open(); }

   private:
    DoorPtr _door;
};

class NullCommand : public Command {
   public:
    void execute() override {}
};

class ExitCommand : public Command {
   public:
    void execute() override { exit(0); }
};

class HACOnCommand : public Command {
   public:
    HACOnCommand(std::shared_ptr<HomeAutomationComponent> hac) : _hac(hac) {}

    void execute() override { _hac->on(); }

   private:
    std::shared_ptr<HomeAutomationComponent> _hac;
};

class LambdaCommand : public Command {
   public:
    LambdaCommand(std::function<void()> f) : _f(f) {}
    void execute() override { _f(); }

   private:
    std::function<void()> _f;
};

class MacroCommand : public Command {
   public:
    MacroCommand(std::vector<std::shared_ptr<Command>> commands)
        : _commands(commands) {}

    void execute() override {
        for (auto s : _commands) s->execute();
    }

   private:
    std::vector<std::shared_ptr<Command>> _commands;
};
#endif  // CS372S2019DESIGNPATTERNSEXAMPLES_COMMAND_HPP
