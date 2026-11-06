#ifndef CHILDA_H
#define CHILDA_H

#include "Microchip.h"
#include "ChildB.h"
#include <memory>

// ChildA володіє ChildB через shared_ptr
class ChildA : public Microchip {
public:
    std::shared_ptr<ChildB> b_ptr;

    ChildA(const std::string& name, int pinCount, double supplyVoltage);
    ~ChildA() override;
};

#endif
