#ifndef PAIR_H
#define PAIR_H

#include <iostream>
#include <string>
#include "TypeName.h"

// ===== Основний шаблон класу =====
template <typename T1, typename T2>
class Pair {
private:
    T1 first;
    T2 second;

public:
    Pair(T1 a, T2 b);
    ~Pair();

    void print_pair() const;
    T1 get_first() const { return first; }
    T2 get_second() const { return second; }
};

// ===== Часткова спеціалізація: обидва типи однакові =====
template <typename T>
class Pair<T, T> {
private:
    T first;
    T second;

public:
    Pair(T a, T b);
    ~Pair();

    void print_pair() const;
    T larger() const;      // додатковий метод, можливий лише коли типи однакові
    void swap_items();     // обмін елементів місцями
};

// ===== Повна спеціалізація: Pair<std::string, bool> =====
template <>
class Pair<std::string, bool> {
private:
    std::string first;
    bool second;

public:
    Pair(const std::string& a, bool b);
    ~Pair();

    void print_pair() const;
    std::string get_first() const { return first; }
    bool get_second() const { return second; }
};

#include "Pair.tpp"

#endif
