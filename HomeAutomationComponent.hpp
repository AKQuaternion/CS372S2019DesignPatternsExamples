//
// Created by Chris Hartman on 2019-04-19.
//

#ifndef CS372S2019DESIGNPATTERNSEXAMPLES_HOMEAUTOMATIONCOMPONENT_HPP
#define CS372S2019DESIGNPATTERNSEXAMPLES_HOMEAUTOMATIONCOMPONENT_HPP

#include <iostream>

class HomeAutomationComponent {
   public:
    virtual ~HomeAutomationComponent() = default;
    virtual void on() = 0;
    virtual void off() = 0;

   private:
};

class Fan : public HomeAutomationComponent {
   public:
    void on() override;
    void off() override;
};

class LightObject : public HomeAutomationComponent {
   public:
    void on() override;
    void off() override;

   private:
};

class StereoObject : public HomeAutomationComponent {
   public:
    void on() override;
    void off() override;

   private:
};

#endif  // CS372S2019DESIGNPATTERNSEXAMPLES_HOMEAUTOMATIONCOMPONENT_HPP
