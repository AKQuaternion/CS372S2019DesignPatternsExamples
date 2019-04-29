//
// Created by Chris Hartman on 2019-04-19.
//

#include "Door.hpp"
void HouseDoor::open() { std::cout << "Turning knob to open door\n"; }
void HouseDoor::close() { std::cout << "Turning knob to close door\n"; }
void GarageDoor::open() { std::cout << "Pushing button to open door\n"; }
void GarageDoor::close() { std::cout << "Pushing button to close door\n"; }
