#ifndef LIST_H
#define LIST_H

#include "Microchip.h"
#include <memory>

// Вузол двозв'язного списку
class List {
public:
    std::shared_ptr<Microchip> data;  // корисні дані (мікросхема)
    std::shared_ptr<List> next;       // "прямий" зв'язок - володіння
    std::weak_ptr<List> prev;         // "зворотний" зв'язок - спостереження

    explicit List(std::shared_ptr<Microchip> chip);
    ~List();

    // Додає новий вузол після 'tail' і повертає його
    static std::shared_ptr<List> append(const std::shared_ptr<List>& tail,
                                        std::shared_ptr<Microchip> chip);
};

#endif
