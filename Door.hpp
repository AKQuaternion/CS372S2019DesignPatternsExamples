//
// Created by Chris Hartman on 2019-04-19.
//

#ifndef CS372S2019DESIGNPATTERNSEXAMPLES_DOOR_HPP
#define CS372S2019DESIGNPATTERNSEXAMPLES_DOOR_HPP

#include <iostream>
#include <memory>
#include "HomeAutomationComponent.hpp"

class Door {
   public:
    virtual void open() = 0;
    virtual void close() = 0;

   private:
};

class HouseDoor : public Door {
   public:
    void open() override;
    void close() override;
};

class GarageDoor : public Door {
   public:
    void open() override;
    void close() override;
};

using DoorPtr = std::shared_ptr<Door>;

class DoorComponent : public HomeAutomationComponent {
   public:
    DoorComponent(std::shared_ptr<Door> door) : _door(door) {}

    void on() { _door->open(); }
    void off() { _door->close(); }

   private:
    DoorPtr _door;
};

#endif  // CS372S2019DESIGNPATTERNSEXAMPLES_DOOR_HPP
