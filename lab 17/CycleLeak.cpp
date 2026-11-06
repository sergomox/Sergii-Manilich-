#include "CycleLeak.h"
#include <iostream>

StrongA::StrongA(const std::string& name, int pinCount, double supplyVoltage)
    : Microchip(name, pinCount, supplyVoltage) {}
StrongA::~StrongA() { std::cout << "  [StrongA] об'єкт знищується" << std::endl; }

StrongB::StrongB(const std::string& name, int pinCount, double supplyVoltage)
    : Microchip(name, pinCount, supplyVoltage) {}
StrongB::~StrongB() { std::cout << "  [StrongB] об'єкт знищується" << std::endl; }
