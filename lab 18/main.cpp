#include <iostream>
#include <string>

#include "Microchip.h"
#include "MaxValue.h"
#include "Pair.h"
#include "Repository.h"

#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;

void demoFunctionTemplate() {
    cout << "\n=== Шаблон функції max_value ===" << endl;
    cout << "Max int:    " << max_value(10, 25) << endl;
    cout << "Max double: " << max_value(3.14, 2.71) << endl;
    cout << "Max string: " << max_value(string("Apple"), string("Banana")) << endl;

    Microchip m1("ATmega328P", 28, 5.0);
    Microchip m2("STM32F103", 48, 3.3);
    cout << "Max Microchip (за к-стю виводів): " << max_value(m1, m2) << endl;

    cout << "-- Повна спеціалізація для const char* --" << endl;
    cout << "Max const char*: " << max_value("Zebra", "Apple") << endl;
}

void demoPair() {
    cout << "\n=== Шаблон класу Pair ===" << endl;

    cout << "\nPair 1 (int, double) - основний шаблон:" << endl;
    Pair<int, double> p1(12, 3.14159);
    p1.print_pair();

    cout << "\nPair 2 (string, bool) - ПОВНА спеціалізація:" << endl;
    Pair<string, bool> p2("C++ is cool", true);
    p2.print_pair();

    cout << "\nPair 3 (string, int) - основний шаблон:" << endl;
    Pair<string, int> p3("ESP32", 38);
    p3.print_pair();

    cout << "\nPair 4 (int, int) - ЧАСТКОВА спеціалізація:" << endl;
    Pair<int, int> p4(7, 42);
    p4.print_pair();
    cout << "  Більший: " << p4.larger() << endl;
    p4.swap_items();
    cout << "  Після swap_items():" << endl;
    p4.print_pair();

    cout << "\nPair 5 (Microchip, Microchip) - ЧАСТКОВА спеціалізація:" << endl;
    Pair<Microchip, Microchip> p5(Microchip("NE555", 8, 12.0), Microchip("LM7805", 3, 12.0));
    p5.print_pair();
    cout << "  Більша мікросхема: " << p5.larger() << endl;

    cout << "\nPair 6 (Microchip, double) - основний шаблон:" << endl;
    Pair<Microchip, double> p6(Microchip("LM358", 8, 5.0), 0.75);
    p6.print_pair();
}

void demoRepository() {
    cout << "\n=== Шаблон класу Repository ===" << endl;

    cout << "Repository<int> (основний шаблон):" << endl;
    Repository<int> r1(7);
    r1.print();

    cout << "Repository<double> (спеціалізація print() - експоненціальний запис):" << endl;
    Repository<double> r2(8.4);
    r2.print();

    cout << "Repository<string> (основний шаблон):" << endl;
    Repository<string> r3("Привіт, шаблони!");
    r3.print();

    cout << "Repository<Microchip> (основний шаблон):" << endl;
    Repository<Microchip> r4(Microchip("74HC00", 14, 5.0));
    r4.print();

    cout << "Repository<bool> (ПОВНА спеціалізація класу):" << endl;
    Repository<bool> r5(true);
    r5.print();
    r5.toggle();
    cout << "  Після toggle():" << endl;
    r5.print();

    cout << "Repository<int*> (ЧАСТКОВА спеціалізація для вказівників):" << endl;
    int x = 100;
    Repository<int*> r6(&x);
    r6.print();
    Repository<int*> r7(nullptr);
    r7.print();

    cout << "Repository<Microchip*> (ЧАСТКОВА спеціалізація для вказівників):" << endl;
    Microchip chip("CD4017", 16, 9.0);
    Repository<Microchip*> r8(&chip);
    r8.print();
}

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);   // українські символи в консолі Windows
    SetConsoleCP(CP_UTF8);
#endif
    cout << "Лабораторна робота №18. Шаблони. Варіант 12 (Мікросхема)" << endl;

    demoFunctionTemplate();
    demoPair();
    demoRepository();

    cout << "\nКінець програми." << endl;
    return 0;
}
