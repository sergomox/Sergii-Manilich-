#include "Microchip.h"
#include <cstring>
#include <utility>

char* Microchip::duplicate(const char* src)
{
    if (src == nullptr)
        src = "";
    char* copy = new char[std::strlen(src) + 1];
    std::strcpy(copy, src);
    return copy;
}

// Конструктор з параметрами
Microchip::Microchip(const char* name, int pinCount, double voltage)
    : name(duplicate(name)), pinCount(pinCount), voltage(voltage)
{
    std::cout << "[Конструктор з параметрами] створено \"" << this->name
              << "\", адреса рядка: " << static_cast<const void*>(this->name) << std::endl;
}

// Деструктор
Microchip::~Microchip()
{
    if (name != nullptr)
    {
        std::cout << "[Деструктор] видалення \"" << name
                  << "\", адреса рядка: " << static_cast<const void*>(name) << std::endl;
        delete[] name;
    }
    else
    {
        std::cout << "[Деструктор] об'єкт порожній (moved-from), видаляти нічого" << std::endl;
    }
}

// Конструктор копіювання (глибоке копіювання)
Microchip::Microchip(const Microchip& other)
    : name(duplicate(other.name)), pinCount(other.pinCount), voltage(other.voltage)
{
    std::cout << "[Конструктор копіювання] скопійовано \"" << name
              << "\", нова адреса рядка: " << static_cast<const void*>(name) << std::endl;
}

// Оператор присвоювання копіюванням
Microchip& Microchip::operator=(const Microchip& other)
{
    if (this != &other)
    {
        delete[] name;                 // видаляємо старе
        name = duplicate(other.name);  // створюємо нове (глибока копія)
        pinCount = other.pinCount;
        voltage = other.voltage;
    }
    std::cout << "[Оператор присвоювання копіюванням] \"" << name << "\"" << std::endl;
    return *this;
}

// Конструктор переміщення
Microchip::Microchip(Microchip&& other) noexcept
    : name(other.name), pinCount(other.pinCount), voltage(other.voltage)
{
    other.name = nullptr;   // "забираємо" ресурс
    other.pinCount = 0;
    other.voltage = 0.0;
    std::cout << "[Конструктор переміщення] ресурс передано, адреса рядка: "
              << static_cast<const void*>(name) << std::endl;
}

// Оператор присвоювання переміщенням
Microchip& Microchip::operator=(Microchip&& other) noexcept
{
    if (this != &other)
    {
        delete[] name;          // видаляємо свій ресурс
        name = other.name;      // забираємо чужий
        pinCount = other.pinCount;
        voltage = other.voltage;
        other.name = nullptr;   // обнуляємо джерело
        other.pinCount = 0;
        other.voltage = 0.0;
    }
    std::cout << "[Оператор присвоювання переміщенням] ресурс передано, адреса рядка: "
              << static_cast<const void*>(name) << std::endl;
    return *this;
}

void Microchip::print(const char* label) const
{
    std::cout << label << "Мікросхема: назва = "
              << (name != nullptr ? name : "<порожньо>")
              << ", виводів = " << pinCount
              << ", напруга живлення = " << voltage << " В" << std::endl;
}
