#pragma once
#include "PowerSource.h"

// Дочірній клас "Павербанк"
class PowerBank : public PowerSource {
private:
    double m_capacityMah;    // ємність, мА·год
    double m_cellVoltage;    // номінальна напруга елементів, В
    double m_chargePercent;  // поточний заряд, %

public:
    PowerBank(const std::string& name = "Павербанк", double voltage = 5.0,
              double power = 10.0, double capacityMah = 10000,
              double cellVoltage = 3.7, double chargePercent = 100);
    virtual ~PowerBank();

    bool setCapacity(double mah);
    bool setCellVoltage(double v);
    bool setCharge(double percent);

    double getCapacity() const { return m_capacityMah; }
    double getCharge() const { return m_chargePercent; }

    virtual void input() override;
    virtual void print() const override;
    virtual const char* getType() const override;
    virtual double energyWh() const override;
};
