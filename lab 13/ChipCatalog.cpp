#include "ChipCatalog.h"
#include "AnalogChip.h"
#include "ChipException.h"
#include "DigitalChip.h"

#include <algorithm>
#include <fstream>

namespace {
std::vector<std::string> split(const std::string& s, char delim) {
    std::vector<std::string> parts;
    std::string cur;
    for (char c : s) {
        if (c == delim) { parts.push_back(cur); cur.clear(); }
        else cur += c;
    }
    parts.push_back(cur);
    return parts;
}

// Створення об'єкта за рядком файлу
std::unique_ptr<Microchip> parseLine(const std::string& line) {
    std::vector<std::string> f = split(line, ';');
    const std::string& type = f[0];
    try {
        if (type == "GENERIC" && f.size() == 4)
            return std::unique_ptr<Microchip>(new Microchip(
                f[1], Microchip::toInt(f[2]), Microchip::toDouble(f[3])));
        if (type == "DIGITAL" && f.size() == 6)
            return std::unique_ptr<Microchip>(new DigitalChip(
                f[1], Microchip::toInt(f[2]), Microchip::toDouble(f[3]),
                f[4], Microchip::toDouble(f[5])));
        if (type == "ANALOG" && f.size() == 6)
            return std::unique_ptr<Microchip>(new AnalogChip(
                f[1], Microchip::toInt(f[2]), Microchip::toDouble(f[3]),
                f[4], Microchip::toDouble(f[5])));
    } catch (const std::exception& e) {
        throw InvalidInputException(e.what());
    }
    throw InvalidInputException("невідомий тип або неправильна кількість полів");
}
}  // namespace

ChipCatalog::ChipCatalog() {}
ChipCatalog::~ChipCatalog() {}

void ChipCatalog::add(std::unique_ptr<Microchip> chip) {
    if (!chip) throw InvalidInputException("порожній вказівник на мікросхему");
    chips_.push_back(std::move(chip));
}

std::size_t ChipCatalog::size() const { return chips_.size(); }
void ChipCatalog::clear() { chips_.clear(); }

Microchip& ChipCatalog::operator[](std::size_t index) {
    if (index >= chips_.size())
        throw IndexException("елемента з номером " + std::to_string(index + 1) +
                             " немає (у каталозі " + std::to_string(chips_.size()) + ")");
    return *chips_[index];
}

const Microchip& ChipCatalog::operator[](std::size_t index) const {
    if (index >= chips_.size())
        throw IndexException("елемента з номером " + std::to_string(index + 1) +
                             " немає (у каталозі " + std::to_string(chips_.size()) + ")");
    return *chips_[index];
}

void ChipCatalog::printAll(std::ostream& out) const {
    if (chips_.empty()) { out << "Каталог порожній.\n"; return; }
    for (std::size_t i = 0; i < chips_.size(); ++i)
        out << (i + 1) << ". " << *chips_[i] << '\n';  // віртуальний print()
}

void ChipCatalog::sortByPins() {
    std::sort(chips_.begin(), chips_.end(),
              [](const std::unique_ptr<Microchip>& a, const std::unique_ptr<Microchip>& b) {
                  return *a < *b;  // перевантажений operator<
              });
}

void ChipCatalog::saveToFile(const std::string& path) const {
    std::fstream file(path, std::ios::out | std::ios::trunc);
    if (!file.is_open()) throw FileException("не вдалося відкрити \"" + path + "\" для запису");
    for (const auto& c : chips_) file << c->serialize() << '\n';
    file.flush();
    if (!file) throw FileException("помилка під час запису у \"" + path + "\"");
    file.close();
}

void ChipCatalog::loadFromFile(const std::string& path) {
    std::fstream file(path, std::ios::in);
    if (!file.is_open()) throw FileException("не вдалося відкрити \"" + path + "\" для читання");
    std::vector<std::unique_ptr<Microchip>> loaded;
    std::string line;
    int lineNo = 0;
    while (std::getline(file, line)) {
        ++lineNo;
        line = Microchip::trim(line);
        if (line.empty()) continue;
        try {
            loaded.push_back(parseLine(line));
        } catch (const ChipException& e) {
            throw FileException("рядок " + std::to_string(lineNo) + ": " + e.what());
        }
    }
    chips_ = std::move(loaded);  // змінюємо каталог лише якщо весь файл прочитано успішно
}

void ChipCatalog::appendToFile(const std::string& path, const Microchip& chip) {
    std::fstream file(path, std::ios::in | std::ios::out | std::ios::app);
    if (!file.is_open()) throw FileException("не вдалося відкрити \"" + path + "\" для дозапису");
    file << chip.serialize() << '\n';
    file.flush();
    if (!file) throw FileException("помилка під час дозапису у \"" + path + "\"");
}

void ChipCatalog::dumpFile(const std::string& path, std::ostream& out) {
    std::fstream file(path, std::ios::in);
    if (!file.is_open()) throw FileException("не вдалося відкрити \"" + path + "\" для читання");
    std::string line;
    int n = 0;
    while (std::getline(file, line)) { out << ++n << ": " << line << '\n'; }
    if (n == 0) out << "(файл порожній)\n";
}
