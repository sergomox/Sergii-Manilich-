#include "PowerBank.h"
#include <iostream>

PowerBank::PowerBank() : PowerSource() {
    pb.capacityMah = 0;
    pb.usbPorts = 0;
    std::cout << "[Конструктор PowerBank за замовчуванням]\n";
}

PowerBank::PowerBank(const std::string& model, double voltage, double power, double price,
                     double capacityMah, int usbPorts)
    : PowerSource(model, voltage, power, price) {
    pb.capacityMah = capacityMah;
    pb.usbPorts = usbPorts;
    std::cout << "[Конструктор PowerBank: " << model << "]\n";
}

PowerBank::~PowerBank() {
    std::cout << "[Деструктор PowerBank: " << data.model << "]\n";
}

std::string PowerBank::typeName() const {
    return "Павербанк";
}
