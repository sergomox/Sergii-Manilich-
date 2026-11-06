#ifndef CHIPCATALOG_H
#define CHIPCATALOG_H

#include "Microchip.h"

#include <cstddef>
#include <memory>
#include <string>
#include <vector>

// Каталог мікросхем: динамічний масив (вектор) об'єктів
class ChipCatalog {
    std::vector<std::unique_ptr<Microchip>> chips_;
public:
    ChipCatalog();
    ~ChipCatalog();

    void add(std::unique_ptr<Microchip> chip);
    std::size_t size() const;
    void clear();

    // Доступ за індексом (з винятком IndexException)
    Microchip& operator[](std::size_t index);
    const Microchip& operator[](std::size_t index) const;

    void printAll(std::ostream& out) const;
    void sortByPins();

    // Двонаправлений файловий ввід/вивід (std::fstream)
    void saveToFile(const std::string& path) const;
    void loadFromFile(const std::string& path);
    static void appendToFile(const std::string& path, const Microchip& chip);
    static void dumpFile(const std::string& path, std::ostream& out);
};

#endif
