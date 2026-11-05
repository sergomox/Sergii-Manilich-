#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <windows.h> // Підключення для налаштування кодування консолі
#include "PowerSource.h"
#include "PowerBank.h"
#include "Generator.h"

int main() {
    // Встановлення UTF-8 (code page 65001) для коректного відображення кирилиці
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    // динамічний масив (вектор) вказівників на базовий клас
    std::vector<PowerSource*> sources;
    std::string choice;

    do {
        std::cout << "\n===== МЕНЮ =====\n"
                     "1 - Додати павербанк\n"
                     "2 - Додати генератор\n"
                     "3 - Вивести всі джерела\n"
                     "4 - Результати обчислень\n"
                     "0 - Вихід\n"
                     "Ваш вибір: ";
        if (!std::getline(std::cin, choice)) break;

        if (choice == "1") {
            PowerSource* p = new PowerBank();
            p->input();                     // віртуальний виклик
            sources.push_back(p);
        } else if (choice == "2") {
            PowerSource* p = new Generator();
            p->input();
            sources.push_back(p);
        } else if (choice == "3") {
            if (sources.empty()) std::cout << "Список порожній.\n";
            for (size_t i = 0; i < sources.size(); ++i) {
                std::cout << "\n--- Джерело №" << i + 1 << " ---\n";
                sources[i]->print();        // віртуальний виклик
            }
        } else if (choice == "4") {
            if (sources.empty()) { std::cout << "Список порожній.\n"; continue; }
            double total = 0, maxPower = 0, maxTime = 0;
            std::string nameP, nameT;
            std::cout << std::fixed << std::setprecision(2);
            for (const PowerSource* s : sources) {
                double e = s->energyWh(), t = s->runtimeHours();
                std::cout << s->getType() << " \"" << s->getName() << "\": E = "
                          << e << " Вт·год, час роботи = " << t << " год\n";
                total += e;
                if (s->getPower() > maxPower) { maxPower = s->getPower(); nameP = s->getName(); }
                if (t > maxTime) { maxTime = t; nameT = s->getName(); }
            }
            std::cout << "\nЗагальний запас енергії: " << total << " Вт·год ("
                      << total / 1000 << " кВт·год)\n"
                      << "Найпотужніше джерело: " << nameP << " (" << maxPower << " Вт)\n"
                      << "Найдовша автономність: " << nameT << " (" << maxTime << " год)\n";
        } else if (choice != "0") {
            std::cout << "Невірний пункт меню!\n";
        }
    } while (choice != "0");

    for (PowerSource* s : sources) delete s;   // віртуальний деструктор
    return 0;
}