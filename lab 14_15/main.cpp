#include <iostream>
#include <limits>
#include <stdexcept>
#include <string>

#ifdef _WIN32
#include <windows.h>
#endif

#include "DoublyLinkedList.h"
#include "Microchip.h"

// Зчитування цілого числа з перевіркою
int read_int(const std::string& prompt) {
    int value;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Помилка: введіть ціле число." << std::endl;
    }
}

// Зчитування дійсного числа з перевіркою
double read_double(const std::string& prompt) {
    double value;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Помилка: введіть число." << std::endl;
    }
}

// Зчитування рядка
std::string read_line(const std::string& prompt) {
    std::string value;
    std::cout << prompt;
    std::getline(std::cin, value);
    return value;
}

// Введення даних мікросхеми
Microchip read_chip() {
    std::string name = read_line("Назва/маркування: ");
    int pins = read_int("Кількість виводів: ");
    double voltage = read_double("Напруга живлення (В): ");
    return Microchip(name, pins, voltage);
}

void print_menu() {
    std::cout << "\n===== Двозв'язний список «Мікросхема» =====\n"
              << "1. Додати на початок\n"
              << "2. Додати в кінець\n"
              << "3. Додати після вказаного елемента\n"
              << "4. Видалити з початку\n"
              << "5. Видалити з кінця\n"
              << "6. Видалити за значенням (маркуванням)\n"
              << "7. Прямий вивід списку\n"
              << "8. Зворотний вивід списку\n"
              << "9. Перевірити, чи список порожній\n"
              << "0. Вихід\n";
}

int main() {
#ifdef _WIN32
    // Українські символи в консолі Windows
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif

    DoublyLinkedList list;
    int choice = -1;

    while (choice != 0) {
        print_menu();
        choice = read_int("Ваш вибір: ");

        try {
            switch (choice) {
                case 1:
                    list.push_front(read_chip());
                    break;
                case 2:
                    list.push_back(read_chip());
                    break;
                case 3: {
                    std::string after = read_line("Маркування елемента, після якого додати: ");
                    if (list.is_empty()) {
                        std::cout << "Список порожній, додавати після елемента неможливо." << std::endl;
                        break;
                    }
                    Microchip chip = read_chip();
                    if (!list.insert_after(after, chip)) {
                        std::cout << "Елемент \"" << after << "\" не знайдено." << std::endl;
                    }
                    break;
                }
                case 4: {
                    Microchip removed = list.pop_front();
                    std::cout << "Видалено з початку: " << removed << std::endl;
                    break;
                }
                case 5: {
                    Microchip removed = list.pop_back();
                    std::cout << "Видалено з кінця: " << removed << std::endl;
                    break;
                }
                case 6: {
                    std::string name = read_line("Маркування елемента для видалення: ");
                    if (list.remove_by_value(name)) {
                        std::cout << "Елемент \"" << name << "\" видалено." << std::endl;
                    } else {
                        std::cout << "Елемент \"" << name << "\" не знайдено." << std::endl;
                    }
                    break;
                }
                case 7:
                    list.display_forward();
                    break;
                case 8:
                    list.display_backward();
                    break;
                case 9:
                    std::cout << (list.is_empty() ? "Список порожній." : "Список не порожній.") << std::endl;
                    break;
                case 0:
                    std::cout << "Завершення роботи." << std::endl;
                    break;
                default:
                    std::cout << "Невірний пункт меню." << std::endl;
            }
        } catch (const std::out_of_range& e) {
            std::cout << "Помилка: " << e.what() << std::endl;
        }
    }

    return 0;
}
