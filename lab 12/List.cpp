#include "List.h"

List::List() : head(nullptr), tail(nullptr), count(0) {}

List::List(const List& other) : head(nullptr), tail(nullptr), count(0) {
    copyFrom(other);
}

List::~List() {
    clear();
}

List& List::operator=(const List& other) {
    if (this != &other) {
        clear();
        copyFrom(other);
    }
    return *this;
}

void List::clear() {
    while (head != nullptr) {
        Node* tmp = head;
        head = head->next;
        delete tmp;
    }
    tail = nullptr;
    count = 0;
}

void List::copyFrom(const List& o) {
    for (Node* p = o.head; p != nullptr; p = p->next)
        pushBack(p->data);
}

void List::pushBack(int value) {
    Node* n = new Node(value);
    if (tail == nullptr)
        head = tail = n;
    else {
        tail->next = n;
        tail = n;
    }
    ++count;
}

int List::size() const {
    return count;
}

int List::getAt(int index) const {
    Node* p = head;
    for (int i = 0; i < index && p != nullptr; ++i)
        p = p->next;
    return p ? p->data : 0;
}

// Новий список без усіх входжень value
List operator-(const List& list, int value) {
    List result;
    for (List::Node* p = list.head; p != nullptr; p = p->next)
        if (p->data != value)
            result.pushBack(p->data);
    return result;
}

bool operator>=(const List& a, const List& b) {
    return a.size() >= b.size();
}

std::ostream& operator<<(std::ostream& out, const List& list) {
    out << "[";
    for (List::Node* p = list.head; p != nullptr; p = p->next) {
        out << p->data;
        if (p->next) out << ", ";
    }
    out << "]";
    return out;
}

// Формат вводу: спочатку кількість елементів, потім самі елементи
std::istream& operator>>(std::istream& in, List& list) {
    int n, value;
    in >> n;
    list.clear();
    for (int i = 0; i < n && in >> value; ++i)
        list.pushBack(value);
    return in;
}
