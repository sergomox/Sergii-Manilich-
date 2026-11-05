#ifndef POWERBANK_H
#define POWERBANK_H

#include "PowerSource.h"

// Структура даних, специфічних для павербанка
struct PowerBankData {
    double capacityMah;  // ємність, мА·год
    int usbPorts;        // кількість USB-портів
};

// Дочірній клас 1
class PowerBank : public PowerSource {
private:
    PowerBankData pb;

public:
    PowerBank();
    PowerBank(const std::string& model, double voltage, double power, double price,
              double capacityMah, int usbPorts);
    ~PowerBank() override;

    std::string typeName() const override;

    friend class PowerHandler;
};

#endif
