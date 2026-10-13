#include "Microchip.h"
#include <iomanip>
#include <cmath>

// Конструктор: безпечна ініціалізація полів значеннями за замовчуванням
MicrochipManager::MicrochipManager() {
    for (auto& item : chips) {
        item.model = "Unknown";
        item.pin_count = 8;
        item.supply_voltage = 5.0;
    }
    std::cout << "[Конструктор] Створено об'єкт MicrochipManager на " << chips.size() << " елементів.\n";
}

// Деструктор
MicrochipManager::~MicrochipManager() {
    std::cout << "[Деструктор] Вивільнення пам'яті об'єкта MicrochipManager.\n";
}

// Метод валідації та запису даних
bool MicrochipManager::setMicrochip(size_t index, const std::string& model, int pinCount, double voltage) {
    // 1. Перевірка діапазону індексу масиву
    if (index >= chips.size()) {
        std::cerr << "[Помилка валідації] Індекс " << index << " виходить за межі масиву (0.." << chips.size() - 1 << ")!\n";
        return false;
    }

    // 2. Перевірка назви/маркування
    if (model.empty()) {
        std::cerr << "[Помилка валідації] Назва мікросхеми не може бути порожньою!\n";
        return false;
    }

    // 3. Перевірка кількості виводів
    if (pinCount < 2) {
        std::cerr << "[Помилка валідації] Кількість виводів (" << pinCount << ") повинна бути >= 2!\n";
        return false;
    }

    // 4. Перевірка напруги живлення 
    if (voltage <= 0.0 || voltage > 48.0) {
        std::cerr << "[Помилка валідації] Напруга живлення (" << voltage << "V) неприпустима (має бути від 0.1V до 48V)!\n";
        return false;
    }

    // Безпечний запис через .at()
    chips.at(index).model = model;
    chips.at(index).pin_count = pinCount;
    chips.at(index).supply_voltage = voltage;

    return true;
}

// Введення даних через консоль із захистом від некоректного вводу
void MicrochipManager::inputData() {
    std::cout << "\n=== Введення параметрів мікросхем ===\n";
    for (size_t i = 0; i < chips.size(); ++i) {
        std::string model;
        int pins;
        double voltage;

        std::cout << "\nМікросхема #" << (i + 1) << ":\n";
        while (true) {
            std::cout << "  Введіть маркування (наприклад, NE555, ATmega328P): ";
            std::cin >> model;
            std::cout << "  Введіть кількість виводів: ";
            std::cin >> pins;
            std::cout << "  Введіть напругу живлення (В): ";
            std::cin >> voltage;

            if (setMicrochip(i, model, pins, voltage)) {
                break;
            }
            std::cout << "  Помилка введення! Повторіть введення для цього елемента.\n";
        }
    }
}

// Виведення повної таблиці мікросхем
void MicrochipManager::printAll() const {
    std::cout << "\n================ Список мікросхем ================\n";
    std::cout << std::left << std::setw(6) << "№"
              << std::setw(20) << "Маркування"
              << std::setw(16) << "К-сть виводів"
              << std::setw(15) << "Напруга (В)" << "\n";
    std::cout << std::string(57, '-') << "\n";

    for (size_t i = 0; i < chips.size(); ++i) {
        std::cout << std::left << std::setw(6) << (i + 1)
                  << std::setw(20) << chips[i].model
                  << std::setw(16) << chips[i].pin_count
                  << std::setw(15) << std::fixed << std::setprecision(2) << chips[i].supply_voltage << "\n";
    }
}

// Виведення за критерієм: точний збіг напруги живлення
void MicrochipManager::printByVoltage(double targetVoltage) const {
    std::cout << "\n[Критерій] Пошук мікросхем із напругою живлення: " << targetVoltage << " В\n";
    bool found = false;

    for (size_t i = 0; i < chips.size(); ++i) {
        // Порівняння дробових чисел з епсилоном
        if (std::fabs(chips.at(i).supply_voltage - targetVoltage) < 0.001) {
            if (!found) {
                std::cout << std::left << std::setw(6) << "№"
                          << std::setw(20) << "Маркування"
                          << std::setw(16) << "К-сть виводів"
                          << std::setw(15) << "Напруга (В)" << "\n";
                std::cout << std::string(57, '-') << "\n";
                found = true;
            }
            std::cout << std::left << std::setw(6) << (i + 1)
                      << std::setw(20) << chips.at(i).model
                      << std::setw(16) << chips.at(i).pin_count
                      << std::setw(15) << std::fixed << std::setprecision(2) << chips.at(i).supply_voltage << "\n";
        }
    }

    if (!found) {
        std::cout << ">> Повідомлення: Мікросхем із напругою " << targetVoltage << " В не знайдено.\n";
    }
}

// Виведення за критерієм: кількість виводів >= заданої
void MicrochipManager::printByMinPins(int minPins) const {
    std::cout << "\n[Критерій] Пошук мікросхем із кількістю виводів >= " << minPins << "\n";
    bool found = false;

    for (size_t i = 0; i < chips.size(); ++i) {
        if (chips.at(i).pin_count >= minPins) {
            if (!found) {
                std::cout << std::left << std::setw(6) << "№"
                          << std::setw(20) << "Маркування"
                          << std::setw(16) << "К-сть виводів"
                          << std::setw(15) << "Напруга (В)" << "\n";
                std::cout << std::string(57, '-') << "\n";
                found = true;
            }
            std::cout << std::left << std::setw(6) << (i + 1)
                      << std::setw(20) << chips.at(i).model
                      << std::setw(16) << chips.at(i).pin_count
                      << std::setw(15) << std::fixed << std::setprecision(2) << chips.at(i).supply_voltage << "\n";
        }
    }

    if (!found) {
        std::cout << ">> Повідомлення: Мікросхем із кількістю виводів >= " << minPins << " не знайдено.\n";
    }
}
