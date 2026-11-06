#ifndef CYCLELEAK_H
#define CYCLELEAK_H

#include "Microchip.h"
#include <memory>

class StrongB;

// Обидва класи тримають одне одного через shared_ptr -> циклічне посилання
class StrongA : public Microchip {
public:
    std::shared_ptr<StrongB> b_ptr;
    StrongA(const std::string& name, int pinCount, double supplyVoltage);
    ~StrongA() override;
};

class StrongB : public Microchip {
public:
    std::shared_ptr<StrongA> a_ptr;   // shared_ptr замість weak_ptr
    StrongB(const std::string& name, int pinCount, double supplyVoltage);
    ~StrongB() override;
};

#endif
