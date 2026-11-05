#pragma once
#include <string>

// Структура, вкладена в клас: спільні дані будь-якого джерела живлення
struct PowerData {
    std::string name;   // назва моделі
    double voltage;     // вихідна напруга, В
    double power;       // вихідна потужність, Вт
};

// Батьківський (базовий) клас "Джерело живлення"
class PowerSource {
private:
    PowerData m_data;

protected:
    // допоміжні функції введення з перевіркою коректності
    static std::string readLine(const std::string& prompt);
    static double readDouble(const std::string& prompt, double min, double max);

public:
    PowerSource(const std::string& name = "Невідомо",
                double voltage = 5.0, double power = 1.0);
    virtual ~PowerSource();

    // сеттери з перевіркою валідності (повертають false при помилці)
    bool setName(const std::string& name);
    bool setVoltage(double voltage);
    bool setPower(double power);

    // геттери
    const std::string& getName() const { return m_data.name; }
    double getVoltage() const { return m_data.voltage; }
    double getPower() const { return m_data.power; }

    // віртуальні функції
    virtual void input();                    // введення даних
    virtual void print() const;              // виведення даних
    virtual const char* getType() const;     // тип джерела
    virtual double energyWh() const;         // запас енергії, Вт·год
    virtual double runtimeHours() const;     // час автономної роботи, год
};
