#pragma once
#include "PowerSource.h"

// Дочірній клас "Бензиновий/дизельний генератор"
class Generator : public PowerSource {
private:
    std::string m_fuelType;     // "бензин" або "дизель"
    double m_tankLiters;        // об'єм бака, л
    double m_consumptionLph;    // витрата пального при повному навантаженні, л/год

public:
    Generator(const std::string& name = "Генератор", double voltage = 230.0,
              double power = 3000.0, const std::string& fuelType = "бензин",
              double tankLiters = 15.0, double consumptionLph = 1.5);
    virtual ~Generator();

    bool setFuelType(const std::string& fuel);
    bool setTank(double liters);
    bool setConsumption(double lph);

    virtual void input() override;
    virtual void print() const override;
    virtual const char* getType() const override;
    virtual double energyWh() const override;
    virtual double runtimeHours() const override;
};
