#include "Microchip.h"

Microchip::Microchip() : name(""), pins(0), voltage(0.0) {}

Microchip::Microchip(const std::string& name, int pins, double voltage)
    : name(name), pins(pins), voltage(voltage) {}

std::string Microchip::getName() const { return name; }
int Microchip::getPins() const { return pins; }
double Microchip::getVoltage() const { return voltage; }

void Microchip::setName(const std::string& newName) { name = newName; }
void Microchip::setPins(int newPins) { pins = newPins; }
void Microchip::setVoltage(double newVoltage) { voltage = newVoltage; }

bool Microchip::operator==(const Microchip& other) const {
    return name == other.name && pins == other.pins && voltage == other.voltage;
}

std::ostream& operator<<(std::ostream& os, const Microchip& chip) {
    os << "[" << chip.name << ", " << chip.pins << " виводів, "
       << chip.voltage << " В]";
    return os;
}
