#ifndef MICROCHIP_H
#define MICROCHIP_H

#include <iostream>
#include <vector>
#include <string>

// Структура для зберігання даних про мікросхему
struct Microchip_s_t {
    std::string name;    // Назва/маркування (наприклад, "ATmega328P", "NE555")
    int pins;            // Кількість виводів (ніжок)
    double voltage;      // Напруга живлення (у вольтах)
};

// Клас для керування масивом мікросхем
class MicrochipManager {
private:
    std::vector<Microchip_s_t> chips; // Динамічний масив структур

public:
    // Конструктор і деструктор
    MicrochipManager();
    ~MicrochipManager();

    // Метод валідації параметрів
    bool isValid(const std::string& name, int pins, double voltage) const;

    // Методи додавання та вставки
    bool addChip(const std::string& name, int pins, double voltage);
    bool insertChip(size_t index, const std::string& name, int pins, double voltage);

    // Методи вилучення, обміну та очищення
    bool removeChip(size_t index);
    bool swapChips(size_t index1, size_t index2);
    void clearAll();

    // Методи зміни полів з валідацією
    bool updateChip(size_t index, const std::string& name, int pins, double voltage);

    // Метод введення з клавіатури
    void inputFromConsole();

    // Метод виведення списку в консоль
    void printAll() const;

    // Допоміжні методи
    size_t getCount() const;
    bool isEmpty() const;
};

#endif // MICROCHIP_H