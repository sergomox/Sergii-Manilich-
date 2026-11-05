#include "Generator.h"
#include <iostream>
#include <iomanip>

Generator::Generator(const std::string& name, double voltage, double power,
                     const std::string& fuelType, double tankLiters,
                     double consumptionLph)
    : PowerSource(name, voltage, power),
      m_fuelType("бензин"), m_tankLiters(15.0), m_consumptionLph(1.5)
{
    setFuelType(fuelType);
    setTank(tankLiters);
    setConsumption(consumptionLph);
    std::cout << "[Конструктор Generator]\n";
}

Generator::~Generator() {
    std::cout << "[Деструктор Generator] " << getName() << '\n';
}

bool Generator::setFuelType(const std::string& fuel) {
    if (fuel != "бензин" && fuel != "дизель") {
        std::cout << "Помилка: тип пального - \"бензин\" або \"дизель\"!\n";
        return false;
    }
    m_fuelType = fuel;
    return true;
}

bool Generator::setTank(double liters) {
    if (liters < 1 || liters > 200) {
        std::cout << "Помилка: об'єм бака має бути від 1 до 200 л!\n";
        return false;
    }
    m_tankLiters = liters;
    return true;
}

bool Generator::setConsumption(double lph) {
    if (lph < 0.1 || lph > 20) {
        std::cout << "Помилка: витрата має бути від 0.1 до 20 л/год!\n";
        return false;
    }
    m_consumptionLph = lph;
    return true;
}

void Generator::input() {
    PowerSource::input();
    while (!setFuelType(readLine("Пальне (бензин/дизель): "))) {}
    setTank(readDouble("Об'єм бака, л: ", 1, 200));
    setConsumption(readDouble("Витрата, л/год: ", 0.1, 20));
}

void Generator::print() const {
    PowerSource::print();
    std::cout << std::fixed << std::setprecision(2)
              << "Пальне: " << m_fuelType << "\n"
              << "Бак: " << m_tankLiters << " л\n"
              << "Витрата: " << m_consumptionLph << " л/год\n";
}

const char* Generator::getType() const {
    return "Генератор (бензиновий/дизельний)";
}

double Generator::runtimeHours() const { return m_tankLiters / m_consumptionLph; }

// E (Вт·год) = P(Вт) * час роботи на одному баку
double Generator::energyWh() const { return getPower() * runtimeHours(); }
