#ifndef DIGITALCHIP_H
#define DIGITALCHIP_H

#include "Microchip.h"

// Дочірній клас: цифрова мікросхема
class DigitalChip : public Microchip {
    std::string logicFamily_;  // сімейство логіки (TTL, CMOS ...)
    double clockMHz_;          // тактова частота, МГц
public:
    DigitalChip();
    DigitalChip(const std::string& name, int pins, double voltage,
                const std::string& logicFamily, double clockMHz);
    ~DigitalChip() override;

    void setLogicFamily(const std::string& family);
    void setClockMHz(double clockMHz);
    std::string getLogicFamily() const;
    double getClockMHz() const;

    std::string typeName() const override;
    std::string typeToken() const override;
    void print(std::ostream& out) const override;
    void readFrom(std::istream& in, std::ostream& out) override;
    std::string serialize() const override;
};

#endif
