#ifndef NODE_H
#define NODE_H

#include "Microchip.h"

// Базовий елемент (вузол) двозв'язного списку
struct Node {
    Microchip data;  // дані вузла
    Node* prev;      // вказівник на попередній вузол
    Node* next;      // вказівник на наступний вузол

    // Конструктор
    explicit Node(const Microchip& value)
        : data(value), prev(nullptr), next(nullptr) {}
};

#endif // NODE_H
