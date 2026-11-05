#ifndef GENERATOR_H
#define GENERATOR_H

#include "PowerSource.h"

// Структура даних, специфічних для генератора
struct GeneratorData {
    std::string fuel;    // тип пального: бензин / дизель
    double consumption;  // витрата пального, л/год
    double tank;         // об'єм баку, л
};

// Дочірній клас 2
class Generator : public PowerSource {
private:
    GeneratorData gen;

public:
    Generator();
    Generator(const std::string& model, double voltage, double power, double price,
              const std::string& fuel, double consumption, double tank);
    ~Generator() override;

    std::string typeName() const override;

    friend class PowerHandler;
};

#endif
