#include "Microchip.h"
#include <iomanip>

// Конструктор
MicrochipManager::MicrochipManager() {
    std::cout << "[Система]: Об'єкт менеджера мікросхем створено." << std::endl;
}

// Деструктор
MicrochipManager::~MicrochipManager() {
    chips.clear();
    std::cout << "[Система]: Об'єкт менеджера мікросхем знищено, пам'ять очищено." << std::endl;
}

// Перевірка валідності вхідних даних
bool MicrochipManager::isValid(const std::string& name, int pins, double voltage) const {
    if (name.empty()) {
        std::cerr << "Помилка валідації: Назва мікросхеми не може бути порожньою!" << std::endl;
        return false;
    }
    if (pins <= 0) {
        std::cerr << "Помилка валідації: Кількість виводів повинна бути більшою за 0 (отримано: " << pins << ")!" << std::endl;
        return false;
    }
    if (voltage <= 0.0) {
        std::cerr << "Помилка валідації: Напруга живлення повинна бути додатною (отримано: " << voltage << " В)!" << std::endl;
        return false;
    }
    return true;
}

// Додавання елемента в кінець вектора
bool MicrochipManager::addChip(const std::string& name, int pins, double voltage) {
    if (!isValid(name, pins, voltage)) {
        return false;
    }
    chips.push_back({name, pins, voltage});
    std::cout << "Успішно додано: " << name << std::endl;
    return true;
}

// Вставка елемента за вказаним індексом
bool MicrochipManager::insertChip(size_t index, const std::string& name, int pins, double voltage) {
    if (index > chips.size()) {
        std::cerr << "Помилка: Індекс " << index << " виходить за межі масиву (розмір: " << chips.size() << ")!" << std::endl;
        return false;
    }
    if (!isValid(name, pins, voltage)) {
        return false;
    }
    chips.insert(chips.begin() + index, {name, pins, voltage});
    std::cout << "Успішно вставлено на позицію " << index << ": " << name << std::endl;
    return true;
}

// Вилучення елемента за індексом
bool MicrochipManager::removeChip(size_t index) {
    if (index >= chips.size()) {
        std::cerr << "Помилка: Неможливо видалити, індекс " << index << " поза межами!" << std::endl;
        return false;
    }
    std::string removedName = chips[index].name;
    chips.erase(chips.begin() + index);
    std::cout << "Елемент [" << removedName << "] за індексом " << index << " видалено." << std::endl;
    return true;
}

// Обмін двох елементів місцями
bool MicrochipManager::swapChips(size_t index1, size_t index2) {
    if (index1 >= chips.size() || index2 >= chips.size()) {
        std::cerr << "Помилка обміну: один з індексів виходить за межі!" << std::endl;
        return false;
    }
    std::swap(chips[index1], chips[index2]);
    std::cout << "Елементи з індексами " << index1 << " та " << index2 << " успішно поміняно місцями." << std::endl;
    return true;
}

// Повне очищення списку
void MicrochipManager::clearAll() {
    chips.clear();
    std::cout << "Масив мікросхем повністю очищено." << std::endl;
}

// Оновлення даних наявного запису з валідацією
bool MicrochipManager::updateChip(size_t index, const std::string& name, int pins, double voltage) {
    if (index >= chips.size()) {
        std::cerr << "Помилка оновлення: некоректний індекс " << index << "!" << std::endl;
        return false;
    }
    if (!isValid(name, pins, voltage)) {
        return false;
    }
    chips[index] = {name, pins, voltage};
    std::cout << "Дані за індексом " << index << " успішно оновлено." << std::endl;
    return true;
}

// Введення нового запису з терміналу
void MicrochipManager::inputFromConsole() {
    std::string name;
    int pins;
    double voltage;

    std::cout << "\n--- Додавання нової мікросхеми вручну ---" << std::endl;
    std::cout << "Введіть назву/маркування: ";
    std::cin >> name;
    std::cout << "Введіть кількість виводів: ";
    std::cin >> pins;
    std::cout << "Введіть напругу живлення (В): ";
    std::cin >> voltage;

    addChip(name, pins, voltage);
}

// Виведення вмісту на екран
void MicrochipManager::printAll() const {
    if (chips.empty()) {
        std::cout << "\n[Список мікросхем порожній]" << std::endl;
        return;
    }

    std::cout << "\n================= Список мікросхем =================" << std::endl;
    std::cout << std::left << std::setw(6)  << "№"
              << std::setw(20) << "Маркування"
              << std::setw(15) << "Висновки"
              << std::setw(15) << "Напруга (В)" << std::endl;
    std::cout << "----------------------------------------------------" << std::endl;

    for (size_t i = 0; i < chips.size(); ++i) {
        std::cout << std::left << std::setw(6)  << i
                  << std::setw(20) << chips[i].name
                  << std::setw(15) << chips[i].pins
                  << std::setw(15) << std::fixed << std::setprecision(2) << chips[i].voltage
                  << std::endl;
    }
    std::cout << "====================================================\n" << std::endl;
}

size_t MicrochipManager::getCount() const {
    return chips.size();
}

bool MicrochipManager::isEmpty() const {
    return chips.empty();
}