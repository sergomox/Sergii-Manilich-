#include "DoublyLinkedList.h"
#include <iostream>
#include <stdexcept>

DoublyLinkedList::DoublyLinkedList() : head(nullptr), tail(nullptr) {}

DoublyLinkedList::~DoublyLinkedList() {
    Node* current = head;
    while (current != nullptr) {
        Node* next_node = current->next;
        delete current;
        current = next_node;
    }
    head = tail = nullptr;
}

bool DoublyLinkedList::is_empty() const {
    return head == nullptr;
}

void DoublyLinkedList::push_front(const Microchip& chip) {
    Node* new_node = new Node(chip);
    if (is_empty()) {
        head = tail = new_node;
    } else {
        new_node->next = head;
        head->prev = new_node;
        head = new_node;
    }
    std::cout << "Додано " << chip << " на початок." << std::endl;
}

void DoublyLinkedList::push_back(const Microchip& chip) {
    Node* new_node = new Node(chip);
    if (is_empty()) {
        head = tail = new_node;
    } else {
        new_node->prev = tail;
        tail->next = new_node;
        tail = new_node;
    }
    std::cout << "Додано " << chip << " на кінець." << std::endl;
}

bool DoublyLinkedList::insert_after(const std::string& name, const Microchip& chip) {
    Node* current = head;
    while (current != nullptr && current->data.getName() != name) {
        current = current->next;
    }
    if (current == nullptr) {
        return false;  // елемент не знайдено
    }

    Node* new_node = new Node(chip);
    new_node->prev = current;
    new_node->next = current->next;
    if (current->next != nullptr) {
        current->next->prev = new_node;
    } else {
        tail = new_node;  // вставка після останнього вузла
    }
    current->next = new_node;

    std::cout << "Додано " << chip << " після елемента \"" << name << "\"." << std::endl;
    return true;
}

Microchip DoublyLinkedList::pop_front() {
    if (is_empty()) {
        throw std::out_of_range("Список порожній, неможливо видалити з початку.");
    }
    Node* temp = head;
    Microchip value = temp->data;
    if (head == tail) {  // список з одним елементом
        head = tail = nullptr;
    } else {
        head = head->next;
        head->prev = nullptr;
    }
    delete temp;
    return value;
}

Microchip DoublyLinkedList::pop_back() {
    if (is_empty()) {
        throw std::out_of_range("Список порожній, неможливо видалити з кінця.");
    }
    Node* temp = tail;
    Microchip value = temp->data;
    if (head == tail) {  // список з одним елементом
        head = tail = nullptr;
    } else {
        tail = tail->prev;
        tail->next = nullptr;
    }
    delete temp;
    return value;
}

bool DoublyLinkedList::remove_by_value(const std::string& name) {
    if (is_empty()) {
        throw std::out_of_range("Список порожній, неможливо видалити елемент.");
    }
    Node* current = head;
    while (current != nullptr && current->data.getName() != name) {
        current = current->next;
    }
    if (current == nullptr) {
        return false;  // елемент не знайдено
    }

    if (current == head) {
        head = current->next;
    } else {
        current->prev->next = current->next;
    }
    if (current == tail) {
        tail = current->prev;
    } else {
        current->next->prev = current->prev;
    }
    delete current;
    return true;
}

void DoublyLinkedList::display_forward() const {
    if (is_empty()) {
        std::cout << "Список порожній." << std::endl;
        return;
    }
    Node* current = head;
    std::cout << "Прямий список: ";
    while (current != nullptr) {
        std::cout << current->data;
        if (current->next != nullptr) {
            std::cout << " <-> ";
        }
        current = current->next;
    }
    std::cout << std::endl;
}

void DoublyLinkedList::display_backward() const {
    if (is_empty()) {
        std::cout << "Список порожній." << std::endl;
        return;
    }
    Node* current = tail;
    std::cout << "Зворотний список: ";
    while (current != nullptr) {
        std::cout << current->data;
        if (current->prev != nullptr) {
            std::cout << " <-> ";
        }
        current = current->prev;
    }
    std::cout << std::endl;
}
