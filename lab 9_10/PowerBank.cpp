#include "PowerBank.h"
#include <iostream>
#include <iomanip>

PowerBank::PowerBank(const std::string& name, double voltage, double power,
                     double capacityMah, double cellVoltage, double chargePercent)
    : PowerSource(name, voltage, power),   // спочатку будується батьківська частина
      m_capacityMah(10000), m_cellVoltage(3.7), m_chargePercent(100)
{
    setCapacity(capacityMah);
    setCellVoltage(cellVoltage);
    setCharge(chargePercent);
    std::cout << "[Конструктор PowerBank]\n";
}

PowerBank::~PowerBank() {
    std::cout << "[Деструктор PowerBank] " << getName() << '\n';
}

bool PowerBank::setCapacity(double mah) {
    if (mah < 500 || mah > 100000) {
        std::cout << "Помилка: ємність має бути від 500 до 100000 мА·год!\n";
        return false;
    }
    m_capacityMah = mah;
    return true;
}

bool PowerBank::setCellVoltage(double v) {
    if (v < 3.0 || v > 4.5) {
        std::cout << "Помилка: напруга елемента має бути від 3.0 до 4.5 В!\n";
        return false;
    }
    m_cellVoltage = v;
    return true;
}

bool PowerBank::setCharge(double percent) {
    if (percent < 0 || percent > 100) {
        std::cout << "Помилка: заряд має бути від 0 до 100 %!\n";
        return false;
    }
    m_chargePercent = percent;
    return true;
}

void PowerBank::input() {
    PowerSource::input();   // введення спільних полів
    setCapacity(readDouble("Ємність, мА·год: ", 500, 100000));
    setCellVoltage(readDouble("Напруга елементів, В (3.0-4.5): ", 3.0, 4.5));
    setCharge(readDouble("Поточний заряд, %: ", 0, 100));
}

void PowerBank::print() const {
    PowerSource::print();
    std::cout << std::fixed << std::setprecision(2)
              << "Ємність: " << m_capacityMah << " мА·год\n"
              << "Напруга елементів: " << m_cellVoltage << " В\n"
              << "Заряд: " << m_chargePercent << " %\n";
}

const char* PowerBank::getType() const { return "Павербанк"; }

// E (Вт·год) = C(мА·год)/1000 * U(В) * заряд/100
double PowerBank::energyWh() const {
    return m_capacityMah / 1000.0 * m_cellVoltage * m_chargePercent / 100.0;
}
