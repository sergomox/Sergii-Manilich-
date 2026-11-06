#include <iostream>
#include <memory>
#include <string>

#include "Microchip.h"
#include "ChildA.h"
#include "ChildB.h"
#include "CycleLeak.h"
#include "List.h"

#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;

void taskUniquePtr() {
    cout << "\n=== 3. std::unique_ptr ===" << endl;

    unique_ptr<Microchip> item1 = make_unique<Microchip>("ATmega328P", 28, 5.0);
    cout << "item1.get() = " << item1.get() << endl;

    // Копіювання заборонене - у unique_ptr видалений конструктор копіювання:
    // unique_ptr<Microchip> item2 = item1;   // ПОМИЛКА КОМПІЛЯЦІЇ

    {
        cout << "-- Входимо в блок, переміщуємо володіння --" << endl;
        unique_ptr<Microchip> item2 = move(item1);

        cout << "item1.get() = " << item1.get()
             << (item1 ? " (володіє)" : " (nullptr)") << endl;
        cout << "item2.get() = " << item2.get()
             << (item2 ? " (володіє)" : " (nullptr)") << endl;
        item2->print();

        cout << "-- Виходимо з блоку, item2 виходить з області видимості --" << endl;
    }
    cout << "-- Після блоку: пам'ять звільнено автоматично --" << endl;
}

void taskSharedPtr() {
    cout << "\n=== 4. std::shared_ptr ===" << endl;

    shared_ptr<Microchip> p1 = make_shared<Microchip>("STM32F103", 48, 3.3);
    shared_ptr<Microchip> p2 = p1;
    shared_ptr<Microchip> p3 = p1;
    cout << "Кількість посилань (p1, p2, p3): " << p1.use_count() << endl;

    {
        shared_ptr<Microchip> p4 = p1;
        cout << "Всередині блоку: " << p1.use_count() << endl;
    }
    cout << "Після виходу з блоку: " << p1.use_count() << endl;
    cout << "(p4 знищено, лічильник зменшився на 1; об'єкт живий, доки є p1, p2, p3)" << endl;
}

void taskWeakPtr() {
    cout << "\n=== 5. std::weak_ptr та циклічні посилання ===" << endl;

    weak_ptr<ChildA> obsA;
    weak_ptr<ChildB> obsB;
    {
        shared_ptr<ChildA> childA = make_shared<ChildA>("NE555", 8, 12.0);
        shared_ptr<ChildB> childB = make_shared<ChildB>("LM358", 8, 5.0);

        childA->b_ptr = childB;   // shared_ptr: A -> B
        childB->a_ptr = childA;   // weak_ptr:   B -> A

        obsA = childA;
        obsB = childB;

        cout << "use_count(childA) = " << childA.use_count()
             << " (weak_ptr не збільшує лічильник)" << endl;
        cout << "use_count(childB) = " << childB.use_count() << endl;
        cout << "-- Вихід з області видимості --" << endl;
    }
    cout << "Після блоку: childA.expired() = " << boolalpha << obsA.expired()
         << ", childB.expired() = " << obsB.expired() << endl;
    cout << "Лічильники дорівнюють 0 -> витоку пам'яті немає." << endl;

    cout << "\n-- Заміна weak_ptr на shared_ptr (StrongA <-> StrongB) --" << endl;
    weak_ptr<StrongA> leakA;
    weak_ptr<StrongB> leakB;
    {
        auto a = make_shared<StrongA>("TL431", 3, 2.5);
        auto b = make_shared<StrongB>("LM317", 3, 1.25);
        a->b_ptr = b;
        b->a_ptr = a;
        leakA = a;
        leakB = b;
        cout << "use_count(a) = " << a.use_count()
             << ", use_count(b) = " << b.use_count() << endl;
        cout << "-- Вихід з області видимості --" << endl;
    }
    cout << "Після блоку: a.expired() = " << leakA.expired()
         << ", b.expired() = " << leakB.expired() << endl;
    cout << "Деструктори не викликались -> ВИТІК ПАМ'ЯТІ." << endl;

    // Навмисно розриваємо цикл вручну, щоб програма не залишала витоку
    cout << "-- Ручне розірвання циклу --" << endl;
    if (auto b = leakB.lock()) {
        b->a_ptr.reset();
    }
}

void taskList() {
    cout << "\n=== 6. Двозв'язний список ===" << endl;

    auto head = make_shared<List>(make_shared<Microchip>("74HC00", 14, 5.0));
    auto tail = head;
    tail = List::append(tail, make_shared<Microchip>("CD4017", 16, 9.0));
    tail = List::append(tail, make_shared<Microchip>("LM7805", 3, 12.0));
    tail = List::append(tail, make_shared<Microchip>("ESP32", 38, 3.3));

    cout << "\n-- Прохід від початку до кінця (next) --" << endl;
    for (auto cur = head; cur; cur = cur->next) {
        cur->data->print();
    }

    cout << "\n-- Прохід від кінця до початку (prev.lock()) --" << endl;
    for (auto cur = tail; cur; cur = cur->prev.lock()) {
        cur->data->print();
    }

    cout << "\nuse_count(head) = " << head.use_count()
         << " (лише змінна head)" << endl;
    cout << "use_count(другого вузла) = " << head->next.use_count()
         << " (prev наступного вузла — weak_ptr, не рахується)" << endl;

    cout << "\n-- Знищення списку --" << endl;
    tail.reset();   // залишається лише head, який володіє ланцюжком
}

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);   // українські символи в консолі Windows
    SetConsoleCP(CP_UTF8);
#endif
    cout << "Лабораторна робота №17. Розумні вказівники. Варіант 12 (Мікросхема)" << endl;

    taskUniquePtr();
    taskSharedPtr();
    taskWeakPtr();
    taskList();

    cout << "\nКінець програми." << endl;
    return 0;
}
