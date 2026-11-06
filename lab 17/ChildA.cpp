#include "ChildA.h"
#include <iostream>

ChildA::ChildA(const std::string& name, int pinCount, double supplyVoltage)
    : Microchip(name, pinCount, supplyVoltage) {
    std::cout << "  [ChildA] об'єкт створено" << std::endl;
}

ChildA::~ChildA() {
    std::cout << "  [ChildA] об'єкт знищується" << std::endl;
}
