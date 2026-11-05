#ifndef POWERHANDLER_H
#define POWERHANDLER_H

#include <vector>
#include "PowerBank.h"
#include "Generator.h"

// Дружній клас: вводить, виводить і обробляє дані
// батьківського та обох дочірніх класів
class PowerHandler {
private:
    std::vector<PowerBank> banks;   // динамічний масив павербанків
    std::vector<Generator> gens;    // динамічний масив генераторів

public:
    PowerHandler();
    ~PowerHandler();

    void inputPowerBank();
    void inputGenerator();
    void inputAll();

    void printPowerBank(const PowerBank& p, int num) const;
    void printGenerator(const Generator& g, int num) const;
    void printAll() const;

    void process() const;   // обчислення результатів
};

#endif
