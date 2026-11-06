#ifndef ANALOGCHIP_H
#define ANALOGCHIP_H

#include "Microchip.h"

// Дочірній клас: аналогова мікросхема
class AnalogChip : public Microchip {
    std::string function_;  // призначення (підсилювач, стабілізатор ...)
    double bandwidthKHz_;   // смуга пропускання, кГц
public:
    AnalogChip();
    AnalogChip(const std::string& name, int pins, double voltage,
               const std::string& function, double bandwidthKHz);
    ~AnalogChip() override;

    void setFunction(const std::string& function);
    void setBandwidthKHz(double bandwidthKHz);
    std::string getFunction() const;
    double getBandwidthKHz() const;

    std::string typeName() const override;
    std::string typeToken() const override;
    void print(std::ostream& out) const override;
    void readFrom(std::istream& in, std::ostream& out) override;
    std::string serialize() const override;
};

#endif
