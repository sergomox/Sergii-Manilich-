#ifndef MICROCHIP_H
#define MICROCHIP_H

#include <string>

// Клас "Мікросхема" (варіант 12)
class Microchip {
private:
    std::string name;      // Назва/маркування
    int pinCount;          // Кількість виводів
    double supplyVoltage;  // Напруга живлення, В

public:
    Microchip(const std::string& name, int pinCount, double supplyVoltage);
    virtual ~Microchip();

    const std::string& getName() const;
    int getPinCount() const;
    double getSupplyVoltage() const;

    virtual void print() const;
};

#endif
