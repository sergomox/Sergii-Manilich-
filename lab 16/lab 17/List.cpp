#include "List.h"
#include <iostream>

List::List(std::shared_ptr<Microchip> chip) : data(std::move(chip)) {
    std::cout << "  [List] вузол створено: " << data->getName() << std::endl;
}

List::~List() {
    std::cout << "  [List] вузол знищується: " << data->getName() << std::endl;
}

std::shared_ptr<List> List::append(const std::shared_ptr<List>& tail,
                                   std::shared_ptr<Microchip> chip) {
    auto node = std::make_shared<List>(std::move(chip));
    tail->next = node;   // власник: попередній вузол -> наступний
    node->prev = tail;   // спостерігач: наступний -> попередній
    return node;
}
