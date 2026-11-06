#ifndef MICROCHIP_H
#define MICROCHIP_H

#include <iostream>
#include <string>

// Клас «Мікросхема» (варіант 12)
// Поля: назва/маркування, кількість виводів, напруга живлення
class Microchip {
private:
    std::string name;   // назва / маркування
    int pins;           // кількість виводів
    double voltage;     // напруга живлення, В

public:
    // Конструктори
    Microchip();
    Microchip(const std::string& name, int pins, double voltage);

    // Геттери
    std::string getName() const;
    int getPins() const;
    double getVoltage() const;

    // Сеттери
    void setName(const std::string& newName);
    void setPins(int newPins);
    void setVoltage(double newVoltage);

    // Порівняння елементів (за всіма полями)
    bool operator==(const Microchip& other) const;

    // Виведення у потік
    friend std::ostream& operator<<(std::ostream& os, const Microchip& chip);
};

#endif // MICROCHIP_H
