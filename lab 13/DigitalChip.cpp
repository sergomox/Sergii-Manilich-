#include "DigitalChip.h"
#include "ChipException.h"

#include <sstream>

DigitalChip::DigitalChip() : Microchip(), logicFamily_("CMOS"), clockMHz_(1.0) {}

DigitalChip::DigitalChip(const std::string& name, int pins, double voltage,
                         const std::string& logicFamily, double clockMHz)
    : Microchip(name, pins, voltage) {
    setLogicFamily(logicFamily);
    setClockMHz(clockMHz);
}

DigitalChip::~DigitalChip() {}

void DigitalChip::setLogicFamily(const std::string& family) {
    std::string f = trim(family);
    if (f.empty() || f.find(';') != std::string::npos)
        throw InvalidInputException("некоректне сімейство логіки");
    logicFamily_ = f;
}

void DigitalChip::setClockMHz(double clockMHz) {
    if (!(clockMHz > 0.0 && clockMHz <= 100000.0))
        throw InvalidInputException("тактова частота має бути в межах (0; 100000] МГц");
    clockMHz_ = clockMHz;
}

std::string DigitalChip::getLogicFamily() const { return logicFamily_; }
double DigitalChip::getClockMHz() const { return clockMHz_; }

std::string DigitalChip::typeName() const { return "Цифрова мікросхема"; }
std::string DigitalChip::typeToken() const { return "DIGITAL"; }

void DigitalChip::print(std::ostream& out) const {
    Microchip::print(out);
    out << " | Логіка: " << logicFamily_ << " | Частота: " << clockMHz_ << " МГц";
}

void DigitalChip::readFrom(std::istream& in, std::ostream& out) {
    Microchip::readFrom(in, out);
    setLogicFamily(readLine(in, out, "Сімейство логіки (TTL/CMOS/...): "));
    setClockMHz(toDouble(readLine(in, out, "Тактова частота (МГц): ")));
}

std::string DigitalChip::serialize() const {
    std::ostringstream os;
    os << Microchip::serialize() << ';' << logicFamily_ << ';' << clockMHz_;
    return os.str();
}
