#include "PowerSource.h"
#include <iostream>
#include <iomanip>

PowerSource::PowerSource(const std::string& name, double voltage, double power)
    : m_data{"Невідомо", 5.0, 1.0}
{
    // значення, що не пройшли перевірку, лишаються за замовчуванням
    setName(name);
    setVoltage(voltage);
    setPower(power);
    std::cout << "[Конструктор PowerSource] " << m_data.name << '\n';
}

PowerSource::~PowerSource() {
    std::cout << "[Деструктор PowerSource] " << m_data.name << '\n';
}

bool PowerSource::setName(const std::string& name) {
    if (name.empty()) {
        std::cout << "Помилка: назва не може бути порожньою!\n";
        return false;
    }
    m_data.name = name;
    return true;
}

bool PowerSource::setVoltage(double voltage) {
    if (voltage <= 0 || voltage > 1000) {
        std::cout << "Помилка: напруга має бути в межах (0; 1000] В!\n";
        return false;
    }
    m_data.voltage = voltage;
    return true;
}

bool PowerSource::setPower(double power) {
    if (power <= 0 || power > 100000) {
        std::cout << "Помилка: потужність має бути в межах (0; 100000] Вт!\n";
        return false;
    }
    m_data.power = power;
    return true;
}

std::string PowerSource::readLine(const std::string& prompt) {
    std::string s;
    while (true) {
        std::cout << prompt;
        if (!std::getline(std::cin, s)) return "";   // кінець вводу
        if (!s.empty()) return s;
        std::cout << "Помилка: рядок порожній, повторіть введення.\n";
    }
}

double PowerSource::readDouble(const std::string& prompt, double min, double max) {
    while (true) {
        std::string s = readLine(prompt);
        if (s.empty()) return min;                    // кінець вводу
        try {
            size_t pos = 0;
            double v = std::stod(s, &pos);
            if (pos != s.size()) throw std::invalid_argument("tail");
            if (v < min || v > max) {
                std::cout << "Помилка: значення має бути від " << min
                          << " до " << max << ".\n";
                continue;
            }
            return v;
        } catch (...) {
            std::cout << "Помилка: введіть число!\n";
        }
    }
}

void PowerSource::input() {
    while (!setName(readLine("Назва: "))) {}
    setVoltage(readDouble("Вихідна напруга, В: ", 0.1, 1000));
    setPower(readDouble("Вихідна потужність, Вт: ", 0.1, 100000));
}

void PowerSource::print() const {
    std::cout << std::fixed << std::setprecision(2)
              << "Тип: " << getType() << "\n"
              << "Назва: " << m_data.name << "\n"
              << "Напруга: " << m_data.voltage << " В\n"
              << "Потужність: " << m_data.power << " Вт\n";
}

const char* PowerSource::getType() const { return "Джерело живлення"; }
double PowerSource::energyWh() const { return 0.0; }
double PowerSource::runtimeHours() const {
    return energyWh() / m_data.power;
}
