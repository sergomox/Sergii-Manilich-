#ifndef REPOSITORY_H
#define REPOSITORY_H

#include <iostream>

// ===== Основний шаблон =====
template <class T>
class Repository {
private:
    T m_value;

public:
    Repository(T value);
    ~Repository();

    void print() const;
};

// Повна спеціалізація методу print() для double (експоненціальний запис)
// Реалізація - у Repository.cpp
template <>
void Repository<double>::print() const;

// ===== Повна спеціалізація класу для bool =====
template <>
class Repository<bool> {
private:
    bool m_value;

public:
    Repository(bool value);
    ~Repository();

    void print() const;
    void toggle();   // метод, якого немає в основному шаблоні
};

// ===== Часткова спеціалізація класу для вказівників T* =====
template <class T>
class Repository<T*> {
private:
    T* m_value;

public:
    Repository(T* value);
    ~Repository();

    void print() const;
};

#include "Repository.tpp"

#endif
