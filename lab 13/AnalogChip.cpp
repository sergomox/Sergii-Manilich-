#include "AnalogChip.h"
#include "ChipException.h"

#include <sstream>

AnalogChip::AnalogChip() : Microchip(), function_("підсилювач"), bandwidthKHz_(1.0) {}

AnalogChip::AnalogChip(const std::string& name, int pins, double voltage,
                       const std::string& function, double bandwidthKHz)
    : Microchip(name, pins, voltage) {
    setFunction(function);
    setBandwidthKHz(bandwidthKHz);
}

AnalogChip::~AnalogChip() {}

void AnalogChip::setFunction(const std::string& function) {
    std::string f = trim(function);
    if (f.empty() || f.find(';') != std::string::npos)
        throw InvalidInputException("некоректне призначення мікросхеми");
    function_ = f;
}

void AnalogChip::setBandwidthKHz(double bandwidthKHz) {
    if (!(bandwidthKHz > 0.0 && bandwidthKHz <= 1e7))
        throw InvalidInputException("смуга пропускання має бути в межах (0; 10000000] кГц");
    bandwidthKHz_ = bandwidthKHz;
}

std::string AnalogChip::getFunction() const { return function_; }
double AnalogChip::getBandwidthKHz() const { return bandwidthKHz_; }

std::string AnalogChip::typeName() const { return "Аналогова мікросхема"; }
std::string AnalogChip::typeToken() const { return "ANALOG"; }

void AnalogChip::print(std::ostream& out) const {
    Microchip::print(out);
    out << " | Призначення: " << function_ << " | Смуга: " << bandwidthKHz_ << " кГц";
}

void AnalogChip::readFrom(std::istream& in, std::ostream& out) {
    Microchip::readFrom(in, out);
    setFunction(readLine(in, out, "Призначення (підсилювач/стабілізатор/...): "));
    setBandwidthKHz(toDouble(readLine(in, out, "Смуга пропускання (кГц): ")));
}

std::string AnalogChip::serialize() const {
    std::ostringstream os;
    os << Microchip::serialize() << ';' << function_ << ';' << bandwidthKHz_;
    return os.str();
}
