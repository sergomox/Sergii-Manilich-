#include "AnalogChip.h"
#include "ChipCatalog.h"
#include "ChipException.h"
#include "DigitalChip.h"
#include "Microchip.h"

#include <iostream>
#include <memory>
#include <string>

#ifdef _WIN32
#include <windows.h>
#endif

static const std::string FILE_NAME = "chips.txt";

static void showMenu() {
    std::cout << "\n===== Каталог мікросхем =====\n"
              << "1. Додати мікросхему (загальну)\n"
              << "2. Додати цифрову мікросхему\n"
              << "3. Додати аналогову мікросхему\n"
              << "4. Показати всі (віртуальний вивід)\n"
              << "5. Зберегти каталог у файл\n"
              << "6. Завантажити каталог з файлу\n"
              << "7. Дописати останню мікросхему у файл\n"
              << "8. Показати вміст файлу\n"
              << "9. Порівняти дві мікросхеми (==, <)\n"
              << "10. Конкатенація назв двох мікросхем (+)\n"
              << "11. Сортувати за кількістю виводів\n"
              << "0. Вихід\n";
}

static std::size_t readIndex(const std::string& prompt) {
    int n = Microchip::toInt(Microchip::readLine(std::cin, std::cout, prompt));
    if (n < 1) throw IndexException("номер має бути додатним");
    return static_cast<std::size_t>(n - 1);
}

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);  // український текст у консолі Windows
    SetConsoleCP(CP_UTF8);
#endif
    ChipCatalog catalog;

    while (true) {
        showMenu();
        try {
            std::string choice = Microchip::readLine(std::cin, std::cout, "Ваш вибір: ");
            int cmd = Microchip::toInt(choice);

            if (cmd == 0) break;
            switch (cmd) {
            case 1: case 2: case 3: {
                std::unique_ptr<Microchip> chip;
                if (cmd == 1) chip.reset(new Microchip());
                else if (cmd == 2) chip.reset(new DigitalChip());
                else chip.reset(new AnalogChip());
                chip->readFrom(std::cin, std::cout);  // віртуальний виклик
                catalog.add(std::move(chip));
                std::cout << "Мікросхему додано.\n";
                break;
            }
            case 4:
                catalog.printAll(std::cout);
                break;
            case 5:
                catalog.saveToFile(FILE_NAME);
                std::cout << "Збережено у файл " << FILE_NAME << " (" << catalog.size() << " зап.).\n";
                break;
            case 6:
                catalog.loadFromFile(FILE_NAME);
                std::cout << "Завантажено " << catalog.size() << " зап. з файлу " << FILE_NAME << ".\n";
                break;
            case 7: {
                if (catalog.size() == 0) throw IndexException("каталог порожній");
                ChipCatalog::appendToFile(FILE_NAME, catalog[catalog.size() - 1]);
                std::cout << "Останню мікросхему дописано у файл.\n";
                break;
            }
            case 8:
                ChipCatalog::dumpFile(FILE_NAME, std::cout);
                break;
            case 9: {
                std::size_t a = readIndex("Номер першої мікросхеми: ");
                std::size_t b = readIndex("Номер другої мікросхеми: ");
                const Microchip& x = catalog[a];
                const Microchip& y = catalog[b];
                std::cout << "Однакові (==): " << (x == y ? "так" : "ні") << '\n';
                std::cout << "Перша має менше виводів (<): " << (x < y ? "так" : "ні") << '\n';
                break;
            }
            case 10: {
                std::size_t a = readIndex("Номер першої мікросхеми: ");
                std::size_t b = readIndex("Номер другої мікросхеми: ");
                std::cout << "Результат: " << (catalog[a] + catalog[b]) << '\n';
                break;
            }
            case 11:
                catalog.sortByPins();
                std::cout << "Відсортовано.\n";
                break;
            default:
                throw InvalidInputException("невідомий пункт меню");
            }
        } catch (const InvalidInputException& e) {
            std::cerr << e.what() << '\n';
            if (std::cin.eof()) break;
        } catch (const FileException& e) {
            std::cerr << e.what() << '\n';
        } catch (const ChipException& e) {
            std::cerr << e.what() << '\n';
        } catch (const std::exception& e) {
            std::cerr << "Стандартний виняток: " << e.what() << '\n';
        } catch (...) {
            std::cerr << "Невідома помилка\n";
        }
    }
    std::cout << "Роботу завершено.\n";
    return 0;
}
