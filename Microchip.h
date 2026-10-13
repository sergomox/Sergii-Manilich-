#pragma once

#include <iostream>
#include <string>
#include <array>

// Розмір статичного масиву
constexpr size_t CHIPS_COUNT = 3;

// Структура для збереження параметрів мікросхеми (п. 4 вказівок)
struct microchip_s_t {
    std::string model;      // Назва / маркування
    int pin_count;          // Кількість виводів (ніжок)
    double supply_voltage;  // Напруга живлення (В)
};

// Клас для обробки даних (п. 3 вказівок)
class MicrochipManager {
private:
    // Статичний масив структур як поле класу
    std::array<microchip_s_t, CHIPS_COUNT> chips;

public:
    // Конструктор і деструктор
    MicrochipManager();
    ~MicrochipManager();

    // Метод зміни полів із валідацією
    bool setMicrochip(size_t index, const std::string& model, int pinCount, double voltage);

    // Методи введення та виведення
    void inputData();
    void printAll() const;

    // Критеріальне виведення: пошук мікросхем за точною напругою живлення
    void printByVoltage(double targetVoltage) const;

    // Критеріальне виведення: мікросхеми з кількістю виводів не менше заданої
    void printByMinPins(int minPins) const;
};
