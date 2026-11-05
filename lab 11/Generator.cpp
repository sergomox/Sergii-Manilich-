#include "Generator.h"
#include <iostream>

Generator::Generator() : PowerSource() {
    gen.fuel = "невідомо";
    gen.consumption = 0;
    gen.tank = 0;
    std::cout << "[Конструктор Generator за замовчуванням]\n";
}

Generator::Generator(const std::string& model, double voltage, double power, double price,
                     const std::string& fuel, double consumption, double tank)
    : PowerSource(model, voltage, power, price) {
    gen.fuel = fuel;
    gen.consumption = consumption;
    gen.tank = tank;
    std::cout << "[Конструктор Generator: " << model << "]\n";
}

Generator::~Generator() {
    std::cout << "[Деструктор Generator: " << data.model << "]\n";
}

std::string Generator::typeName() const {
    return "Генератор (бензиновий/дизельний)";
}
