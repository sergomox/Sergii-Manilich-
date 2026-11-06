#ifndef MICROCHIP_H
#define MICROCHIP_H

#include <iostream>
#include <string>

// Клас "Мікросхема" (варіант 12)
class Microchip {
private:
    std::string name;      // Назва/маркування
    int pinCount;          // Кількість виводів
    double supplyVoltage;  // Напруга живлення, В

public:
    Microchip();
    Microchip(const std::string& name, int pinCount, double supplyVoltage);
    ~Microchip();

    const std::string& getName() const;
    int getPinCount() const;
    double getSupplyVoltage() const;

    // Порівняння мікросхем за кількістю виводів (потрібно для max_value)
    bool operator>(const Microchip& other) const;
    bool operator==(const Microchip& other) const;

    void print() const;
};

// Вивід у потік (потрібно для шаблонів Pair та Repository)
std::ostream& operator<<(std::ostream& os, const Microchip& chip);

#endif
