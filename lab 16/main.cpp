#include <iostream>
#include <utility>
#include "Microchip.h"

#ifdef _WIN32
#include <windows.h>
#endif

// Передача об'єкта у функцію за значенням
void passByValue(Microchip chip)
{
    chip.print("  Всередині passByValue: ");
}

// Повернення об'єкта з функції
Microchip createChip()
{
    Microchip temp("LM358", 8, 5.0);
    return temp;
}

// Повернення тимчасового об'єкта (rvalue)
Microchip createTemporary()
{
    return Microchip("NE555", 8, 12.0);
}

int main()
{
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);   // UTF-8 у консолі Windows
    SetConsoleCP(CP_UTF8);
#endif

    std::cout << "=== 1. Створення об'єкта ===" << std::endl;
    Microchip a("ATmega328P", 28, 5.0);
    a.print("  ");

    std::cout << "\n=== 2. Конструктор копіювання (Microchip b = a) ===" << std::endl;
    Microchip b = a;
    b.print("  b: ");

    std::cout << "\n=== 3. Передача у функцію за значенням (копія) ===" << std::endl;
    passByValue(a);

    std::cout << "\n=== 4. Передача у функцію через std::move ===" << std::endl;
    passByValue(std::move(a));
    a.print("  Після std::move, a: ");

    std::cout << "\n=== 5. Повернення з функції ===" << std::endl;
    Microchip c = createChip();
    c.print("  c: ");

    std::cout << "\n=== 6. Присвоювання переміщенням з тимчасового об'єкта ===" << std::endl;
    Microchip d("STM32F103", 48, 3.3);
    d = createTemporary();
    d.print("  d: ");

    std::cout << "\n=== 7. Оператор присвоювання копіюванням ===" << std::endl;
    Microchip e("74HC00", 14, 5.0);
    e = b;
    e.print("  e: ");

    std::cout << "\n=== 8. Конструктор переміщення через std::move ===" << std::endl;
    Microchip f = std::move(c);
    f.print("  f: ");
    c.print("  Після std::move, c: ");

    std::cout << "\n=== 9. Оператор присвоювання переміщенням через std::move ===" << std::endl;
    Microchip g("TL431", 3, 2.5);
    g = std::move(e);
    g.print("  g: ");
    e.print("  Після std::move, e: ");

    std::cout << "\n=== Завершення main (деструктори) ===" << std::endl;
    return 0;
}
