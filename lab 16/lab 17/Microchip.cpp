#include "Microchip.h"
#include <iostream>

Microchip::Microchip(const std::string& name, int pinCount, double supplyVoltage)
    : name(name), pinCount(pinCount), supplyVoltage(supplyVoltage) {
    std::cout << "  [Конструктор] Створено мікросхему " << name << std::endl;
}

Microchip::~Microchip() {
    std::cout << "  [Деструктор] Знищено мікросхему " << name << std::endl;
}

const std::string& Microchip::getName() const { return name; }
int Microchip::getPinCount() const { return pinCount; }
double Microchip::getSupplyVoltage() const { return supplyVoltage; }

void Microchip::print() const {
    std::cout << "  Мікросхема: " << name
              << ", виводів: " << pinCount
              << ", напруга живлення: " << supplyVoltage << " В" << std::endl;
}
