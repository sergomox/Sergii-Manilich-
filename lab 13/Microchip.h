#ifndef MICROCHIP_H
#define MICROCHIP_H

#include <iostream>
#include <string>

// Батьківський клас "Мікросхема"
class Microchip {
public:
    // Структура, вкладена в клас: поля мікросхеми
    struct Specs {
        std::string name;      // назва / маркування
        int pinCount;          // кількість виводів
        double supplyVoltage;  // напруга живлення, В
    };

protected:
    Specs specs_;

public:
    Microchip();
    Microchip(const std::string& name, int pinCount, double supplyVoltage);
    Microchip(const Microchip&) = default;
    Microchip& operator=(const Microchip&) = default;
    virtual ~Microchip();

    // Сетери з перевіркою (генерують винятки)
    void setName(const std::string& name);
    void setPinCount(int pinCount);
    void setSupplyVoltage(double voltage);

    const Specs& getSpecs() const;
    std::string getName() const;
    int getPinCount() const;
    double getSupplyVoltage() const;

    // Віртуальні функції
    virtual std::string typeName() const;                        // назва типу для виводу
    virtual std::string typeToken() const;                       // мітка типу у файлі
    virtual void print(std::ostream& out) const;                 // вивід на екран
    virtual void readFrom(std::istream& in, std::ostream& out);  // інтерактивне введення
    virtual std::string serialize() const;                       // рядок для запису у файл

    // Перевантаження операторів
    bool operator==(const Microchip& other) const;
    bool operator!=(const Microchip& other) const;
    bool operator<(const Microchip& other) const;         // порівняння за к-стю виводів
    std::string operator+(const Microchip& other) const;  // конкатенація назв
    friend std::ostream& operator<<(std::ostream& out, const Microchip& chip);

    // Допоміжні функції введення
    static std::string trim(const std::string& s);
    static std::string readLine(std::istream& in, std::ostream& out, const std::string& prompt);
    static int toInt(const std::string& s);
    static double toDouble(const std::string& s);
};

#endif
