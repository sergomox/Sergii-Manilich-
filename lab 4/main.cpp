#include <iostream>
#include <windows.h> // Для коректного виведення кирилиці у Windows
#include "Microchip.h"

int main() {
    // Встановлення кодування UTF-8 для коректного виведення українських літер
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    MicrochipManager manager;

    std::cout << "\n>>> 1. Додавання початкових елементів (push_back) <<<" << std::endl;
    manager.addChip("NE555", 8, 5.0);
    manager.addChip("ATmega328P", 28, 5.0);
    manager.addChip("STM32F103C8T6", 48, 3.3);
    manager.printAll();

    std::cout << ">>> 2. Тестування валідації значень <<<" << std::endl;
    manager.addChip("BadChip_1", -4, 5.0); // Помилка кількості виводів
    manager.addChip("BadChip_2", 16, -3.3); // Помилка напруги
    manager.addChip("", 14, 5.0);          // Помилка порожньої назви

    std::cout << "\n>>> 3. Вставка елемента за індексом (insert) <<<" << std::endl;
    manager.insertChip(1, "ESP32-WROOM", 38, 3.3);
    manager.printAll();

    std::cout << ">>> 4. Обмін елементів місцями (swap) <<<" << std::endl;
    manager.swapChips(0, 2);
    manager.printAll();

    std::cout << ">>> 5. Вилучення елемента за індексом (erase) <<<" << std::endl;
    manager.removeChip(1);
    manager.printAll();

    std::cout << ">>> 6. Очищення контейнера (clear) <<<" << std::endl;
    manager.clearAll();
    manager.printAll();

    return 0;
}