#include "Microchip.h"
#include <windows.h>

int main() {
    // Встановлюємо вивід консолі у UTF-8 для коректного відображення українських символів
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    // Створення об'єкта класу
    MicrochipManager lab;

    std::cout << "\n1. Ініціалізація валідними тестовими даними:\n";
    lab.setMicrochip(0, "NE555P", 8, 5.0);
    lab.setMicrochip(1, "ATmega328P", 32, 5.0);
    lab.setMicrochip(2, "STM32F103C8T6", 48, 3.3);

    std::cout << "\n2. Демонстрація перевірки валідності некоректних даних:\n";
    lab.setMicrochip(0, "", 8, 5.0);         // Помилка: порожня назва
    lab.setMicrochip(1, "LM358", 0, 12.0);    // Помилка: виводів < 2
    lab.setMicrochip(2, "MAX232", 16, -5.0);  // Помилка: від'ємна напруга
    lab.setMicrochip(5, "Unknown", 8, 5.0);   // Помилка: невірний індекс

    std::cout << "\n3. Виведення таблиці поточного стану масиву:\n";
    lab.printAll();

    std::cout << "\n4. Критеріальний пошук (успішний пошук 5.0V):\n";
    lab.printByVoltage(5.0);

    std::cout << "\n5. Критеріальний пошук (невдалий пошук 12.0V):\n";
    lab.printByVoltage(12.0);

    std::cout << "\n6. Критеріальний пошук (виводи >= 30):\n";
    lab.printByMinPins(30);

    return 0;
}