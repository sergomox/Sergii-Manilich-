#ifndef MAXVALUE_H
#define MAXVALUE_H

// Шаблон функції: повертає більший з двох аргументів
template <typename T>
T max_value(T a, T b) {
    return (a > b) ? a : b;
}

// Повна спеціалізація шаблону функції для const char*
// (загальна версія порівнювала б адреси, а не рядки)
template <>
const char* max_value<const char*>(const char* a, const char* b);

#endif
