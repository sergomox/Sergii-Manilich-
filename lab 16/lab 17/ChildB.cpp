#include "ChildB.h"
#include <iostream>

ChildB::ChildB(const std::string& name, int pinCount, double supplyVoltage)
    : Microchip(name, pinCount, supplyVoltage) {
    std::cout << "  [ChildB] об'єкт створено" << std::endl;
}

ChildB::~ChildB() {
    std::cout << "  [ChildB] об'єкт знищується" << std::endl;
}
