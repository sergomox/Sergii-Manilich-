#include <iostream>
#include <string>

// Визначення класу Microchip (Варіант 12)
class Microchip {
private:
    std::string name;     // Назва/маркування
    int pinCount;         // Кількість виводів
    double supplyVoltage; // Напруга живлення

public:
    // Конструктор за замовчуванням
    Microchip() {
        name = "Невідомо";
        pinCount = 0;
        supplyVoltage = 0.0;
        std::cout << "[Конструктор за замовчуванням] Створено порожній об'єкт." << std::endl;
    }

    // Конструктор класу з параметрами
    Microchip(const std::string& chipName, int chipPins, double chipVoltage) {
        setName(chipName);
        setPinCount(chipPins);
        setSupplyVoltage(chipVoltage);
        std::cout << "[Конструктор з параметрами] Створено об'єкт " << name << std::endl;
    }

    // Деструктор класу
    ~Microchip() {
        std::cout << "Деструктор Знищено об'єкт " << name << std::endl;
    }

    // Методи зміни полів класу з перевіркою валідності
    void setName(const std::string& newName) {
        if (!newName.empty()) {
            name = newName;
        } else {
            std::cout << "Попередження: назва не може бути порожньою!" << std::endl;
        }
    }

    void setPinCount(int newPins) {
        if (newPins > 0) {
            pinCount = newPins;
        } else {
            std::cout << "Попередження: кількість виводів (" << newPins << ") має бути більшою за 0!" << std::endl;
        }
    }

    void setSupplyVoltage(double newVoltage) {
        if (newVoltage > 0.0) {
            supplyVoltage = newVoltage;
        } else {
            std::cout << "Попередження: напруга живлення (" << newVoltage << " В) має бути додатною!" << std::endl;
        }
    }

    // Метод для виведення інформації про мікросхему
    void displayInfo() const {
        std::cout << "Назва: " << name 
                  << ", Виводи: " << pinCount 
                  << " шт., Напруга: " << supplyVoltage << " В" 
                  << std::endl;
    }
};

// Функція, що приймає посилання на об'єкт Microchip
void changeMicrochipData(Microchip& chip, int newPins, double newVoltage) {
    std::cout << "Changing microchip data using a reference..." << std::endl;
    chip.setPinCount(newPins);
    chip.setSupplyVoltage(newVoltage);
}

int main() {
    // 1. Створення об'єкта через конструктор за замовчуванням
    std::cout << "--- Initial default microchip info ---" << std::endl;
    Microchip chip1;
    chip1.displayInfo();

    // Заповнення значень через методи
    chip1.setName("NEBO");
    chip1.setPinCount(8);
    chip1.setSupplyVoltage(5.0);
    std::cout << "\nUpdated chip1 info:" << std::endl;
    chip1.displayInfo();

    // 2. Створення об'єкта через конструктор з параметрами (як у прикладі Student)
    std::cout << "\n--- Initial microchip info (chip2) ---" << std::endl;
    Microchip chip2("MEGA", 28, 5.0);
    chip2.displayInfo();

    // 3. Перевірка валідації на некоректні дані
    std::cout << "\n--- Testing data validation ---" << std::endl;
    chip2.setPinCount(-10);
    chip2.setSupplyVoltage(-3.3);

    // 4. Виклик функції, що змінює дані мікросхеми через посилання
    std::cout << std::endl;
    changeMicrochipData(chip2, 32, 3.3);

    // Виведення оновленої інформації
    std::cout << "\nUpdated microchip info:" << std::endl;
    chip2.displayInfo();

    std::cout << std::endl;
    return 0;
}