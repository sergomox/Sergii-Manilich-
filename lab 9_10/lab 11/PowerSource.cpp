#include "PowerSource.h"
#include <iostream>

PowerSource::PowerSource() {
    data.model = "невідомо";
    data.voltage = 0;
    data.power = 0;
    data.price = 0;
    std::cout << "[Конструктор PowerSource за замовчуванням]\n";
}

PowerSource::PowerSource(const std::string& model, double voltage, double power, double price) {
    data.model = model;
    data.voltage = voltage;
    data.power = power;
    data.price = price;
    std::cout << "[Конструктор PowerSource: " << model << "]\n";
}

PowerSource::~PowerSource() {
    std::cout << "[Деструктор PowerSource: " << data.model << "]\n";
}

std::string PowerSource::typeName() const {
    return "Джерело живлення";
}
