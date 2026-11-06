#ifndef CHILDB_H
#define CHILDB_H

#include "Microchip.h"
#include <memory>

class ChildA;  // випереджувальне оголошення

// ChildB НЕ володіє ChildA: зворотне посилання через weak_ptr
class ChildB : public Microchip {
public:
    std::weak_ptr<ChildA> a_ptr;

    ChildB(const std::string& name, int pinCount, double supplyVoltage);
    ~ChildB() override;
};

#endif
