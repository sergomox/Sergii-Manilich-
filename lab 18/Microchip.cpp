#include "Microchip.h"

Microchip::Microchip() : name("невідомо"), pinCount(0), supplyVoltage(0.0) {}

Microchip::Microchip(const std::string& name, int pinCount, double supplyVoltage)
    : name(name), pinCount(pinCount), supplyVoltage(supplyVoltage) {}

Microchip::~Microchip() {}

const std::string& Microchip::getName() const { return name; }
int Microchip::getPinCount() const { return pinCount; }
double Microchip::getSupplyVoltage() const { return supplyVoltage; }

bool Microchip::operator>(const Microchip& other) const {
    return pinCount > other.pinCount;
}

bool Microchip::operator==(const Microchip& other) const {
    return name == other.name && pinCount == other.pinCount &&
           supplyVoltage == other.supplyVoltage;
}

void Microchip::print() const {
    std::cout << *this << std::endl;
}

std::ostream& operator<<(std::ostream& os, const Microchip& chip) {
    os << chip.getName() << " [" << chip.getPinCount() << " вив., "
       << chip.getSupplyVoltage() << " В]";
    return os;
}
