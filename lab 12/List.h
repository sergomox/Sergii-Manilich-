#ifndef LIST_H
#define LIST_H

#include <iostream>

// Клас "Однозв'язний список цілих чисел"
class List {
private:
    // Структура, вкладена в клас: вузол списку
    struct Node {
        int data;
        Node* next;
        Node(int d, Node* n = nullptr) : data(d), next(n) {}
    };

    Node* head;   // перший вузол
    Node* tail;   // останній вузол
    int count;    // кількість елементів

    void clear();                 // очищення списку
    void copyFrom(const List& o); // копіювання елементів

public:
    List();                          // конструктор за замовчуванням
    List(const List& other);         // конструктор копіювання
    ~List();                         // деструктор
    List& operator=(const List& other);

    void pushBack(int value);        // додати елемент в кінець
    int size() const;                // кількість елементів (геттер)
    int getAt(int index) const;      // елемент за індексом (геттер)

    // Вилучення заданого елемента зі списку (усіх входжень);
    // лівий операнд не змінюється -> дружня функція
    friend List operator-(const List& list, int value);

    // Ввід / вивід полів класу
    friend std::ostream& operator<<(std::ostream& out, const List& list);
    friend std::istream& operator>>(std::istream& in, List& list);
};

// Порівняння двох списків за кількістю елементів
// (використовує геттер size(), тому звичайна функція)
bool operator>=(const List& a, const List& b);

#endif
