#ifndef POWERSOURCE_H
#define POWERSOURCE_H

#include <string>

// Структура для збереження спільних даних будь-якого джерела живлення
struct PowerSourceData {
    std::string model;   // модель
    double voltage;      // вихідна напруга, В
    double power;        // максимальна потужність, Вт
    double price;        // ціна, грн
};

// Базовий (батьківський) клас
class PowerSource {
protected:
    PowerSourceData data;

public:
    PowerSource();
    PowerSource(const std::string& model, double voltage, double power, double price);
    virtual ~PowerSource();

    virtual std::string typeName() const;

    // Дружній клас: має доступ до закритих/захищених членів
    friend class PowerHandler;
};

#endif
