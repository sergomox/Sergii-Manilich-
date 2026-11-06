#ifndef MICROCHIP_H
#define MICROCHIP_H

#include <cstddef>
#include <iostream>

// Клас «Мікросхема» (варіант 12).
// Поля: назва/маркування (динамічний рядок), кількість виводів, напруга живлення.
// Клас володіє динамічною пам'яттю -> реалізовано правило п'яти.
class Microchip
{
private:
    char*  name;      // назва/маркування (динамічна пам'ять)
    int    pinCount;  // кількість виводів
    double voltage;   // напруга живлення, В

    static char* duplicate(const char* src); // допоміжна функція: глибока копія рядка

public:
    // Конструктор з параметрами (виділення пам'яті)
    Microchip(const char* name = "", int pinCount = 0, double voltage = 0.0);

    // 1. Деструктор (звільнення пам'яті)
    ~Microchip();

    // 2. Конструктор копіювання (глибоке копіювання)
    Microchip(const Microchip& other);

    // 3. Оператор присвоювання копіюванням
    Microchip& operator=(const Microchip& other);

    // 4. Конструктор переміщення
    Microchip(Microchip&& other) noexcept;

    // 5. Оператор присвоювання переміщенням
    Microchip& operator=(Microchip&& other) noexcept;

    // Допоміжні методи
    void print(const char* label = "") const;
    const char* getName() const { return name; }
    int getPinCount() const { return pinCount; }
    double getVoltage() const { return voltage; }
};

#endif // MICROCHIP_H
