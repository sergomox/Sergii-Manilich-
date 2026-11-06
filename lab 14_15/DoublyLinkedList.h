#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H

#include <string>
#include "Node.h"

// Клас двозв'язного списку мікросхем
class DoublyLinkedList {
private:
    Node* head;  // вказівник на початок
    Node* tail;  // вказівник на кінець

public:
    // Конструктор: створює порожній список
    DoublyLinkedList();

    // Деструктор: видаляє всі вузли
    ~DoublyLinkedList();

    // Копіювання заборонено (щоб уникнути подвійного видалення пам'яті)
    DoublyLinkedList(const DoublyLinkedList&) = delete;
    DoublyLinkedList& operator=(const DoublyLinkedList&) = delete;

    // Перевірка, чи список порожній
    bool is_empty() const;

    // Додавання елемента
    void push_front(const Microchip& chip);
    void push_back(const Microchip& chip);
    // Додавання після елемента з вказаним маркуванням; false, якщо елемент не знайдено
    bool insert_after(const std::string& name, const Microchip& chip);

    // Видалення елемента
    Microchip pop_front();
    Microchip pop_back();
    // Видалення першого елемента з вказаним маркуванням; false, якщо не знайдено
    bool remove_by_value(const std::string& name);

    // Виведення списку
    void display_forward() const;
    void display_backward() const;
};

#endif // DOUBLY_LINKED_LIST_H
