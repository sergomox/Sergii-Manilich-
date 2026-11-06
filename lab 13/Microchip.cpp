#include "Microchip.h"
#include "ChipException.h"

#include <cmath>
#include <sstream>

Microchip::Microchip() : specs_{"Невідомо", 1, 5.0} {}

Microchip::Microchip(const std::string& name, int pinCount, double supplyVoltage) {
    setName(name);
    setPinCount(pinCount);
    setSupplyVoltage(supplyVoltage);
}

Microchip::~Microchip() {}

void Microchip::setName(const std::string& name) {
    std::string n = trim(name);
    if (n.empty())
        throw InvalidInputException("назва мікросхеми не може бути порожньою");
    if (n.find(';') != std::string::npos)
        throw InvalidInputException("назва не може містити символ ';'");
    specs_.name = n;
}

void Microchip::setPinCount(int pinCount) {
    if (pinCount < 1 || pinCount > 1000)
        throw InvalidInputException("кількість виводів має бути від 1 до 1000");
    specs_.pinCount = pinCount;
}

void Microchip::setSupplyVoltage(double voltage) {
    if (!(voltage > 0.0 && voltage <= 100.0))
        throw InvalidInputException("напруга живлення має бути в межах (0; 100] В");
    specs_.supplyVoltage = voltage;
}

const Microchip::Specs& Microchip::getSpecs() const { return specs_; }
std::string Microchip::getName() const { return specs_.name; }
int Microchip::getPinCount() const { return specs_.pinCount; }
double Microchip::getSupplyVoltage() const { return specs_.supplyVoltage; }

std::string Microchip::typeName() const { return "Мікросхема"; }
std::string Microchip::typeToken() const { return "GENERIC"; }

void Microchip::print(std::ostream& out) const {
    out << "[" << typeName() << "] Назва: " << specs_.name
        << " | Виводів: " << specs_.pinCount
        << " | Живлення: " << specs_.supplyVoltage << " В";
}

void Microchip::readFrom(std::istream& in, std::ostream& out) {
    setName(readLine(in, out, "Назва/маркування: "));
    setPinCount(toInt(readLine(in, out, "Кількість виводів: ")));
    setSupplyVoltage(toDouble(readLine(in, out, "Напруга живлення (В): ")));
}

std::string Microchip::serialize() const {
    std::ostringstream os;
    os << typeToken() << ';' << specs_.name << ';' << specs_.pinCount << ';' << specs_.supplyVoltage;
    return os.str();
}

bool Microchip::operator==(const Microchip& o) const {
    return specs_.name == o.specs_.name && specs_.pinCount == o.specs_.pinCount &&
           std::fabs(specs_.supplyVoltage - o.specs_.supplyVoltage) < 1e-9;
}

bool Microchip::operator!=(const Microchip& o) const { return !(*this == o); }

bool Microchip::operator<(const Microchip& o) const {
    if (specs_.pinCount != o.specs_.pinCount) return specs_.pinCount < o.specs_.pinCount;
    return specs_.name < o.specs_.name;
}

std::string Microchip::operator+(const Microchip& o) const {
    return specs_.name + " + " + o.specs_.name;
}

std::ostream& operator<<(std::ostream& out, const Microchip& chip) {
    chip.print(out);  // віртуальний виклик
    return out;
}

std::string Microchip::trim(const std::string& s) {
    const char* ws = " \t\r\n";
    std::size_t b = s.find_first_not_of(ws);
    if (b == std::string::npos) return "";
    std::size_t e = s.find_last_not_of(ws);
    return s.substr(b, e - b + 1);
}

std::string Microchip::readLine(std::istream& in, std::ostream& out, const std::string& prompt) {
    out << prompt << std::flush;
    std::string line;
    if (!std::getline(in, line))
        throw InvalidInputException("потік введення закрито");
    return line;
}

int Microchip::toInt(const std::string& s) {
    std::string t = trim(s);
    try {
        std::size_t pos = 0;
        int v = std::stoi(t, &pos);
        if (pos != t.size()) throw InvalidInputException("\"" + t + "\" не є цілим числом");
        return v;
    } catch (const std::invalid_argument&) {
        throw InvalidInputException("\"" + t + "\" не є цілим числом");
    } catch (const std::out_of_range&) {
        throw InvalidInputException("число \"" + t + "\" занадто велике");
    }
}

double Microchip::toDouble(const std::string& s) {
    std::string t = trim(s);
    for (char& c : t) if (c == ',') c = '.';  // дозволяємо кому як роздільник
    try {
        std::size_t pos = 0;
        double v = std::stod(t, &pos);
        if (pos != t.size()) throw InvalidInputException("\"" + t + "\" не є числом");
        return v;
    } catch (const std::invalid_argument&) {
        throw InvalidInputException("\"" + t + "\" не є числом");
    } catch (const std::out_of_range&) {
        throw InvalidInputException("число \"" + t + "\" занадто велике");
    }
}
