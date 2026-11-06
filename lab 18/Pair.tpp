// Реалізація шаблонів Pair (підключається в кінці Pair.h)
#include <utility>

// ----- Основний шаблон -----
template <typename T1, typename T2>
Pair<T1, T2>::Pair(T1 a, T2 b) : first(a), second(b) {}

template <typename T1, typename T2>
Pair<T1, T2>::~Pair() {}

template <typename T1, typename T2>
void Pair<T1, T2>::print_pair() const {
    std::cout << "  Перший:  " << first
              << " (тип: " << typeName<T1>() << ")" << std::endl;
    std::cout << "  Другий:  " << second
              << " (тип: " << typeName<T2>() << ")" << std::endl;
}

// ----- Часткова спеціалізація Pair<T, T> -----
template <typename T>
Pair<T, T>::Pair(T a, T b) : first(a), second(b) {}

template <typename T>
Pair<T, T>::~Pair() {}

template <typename T>
void Pair<T, T>::print_pair() const {
    std::cout << "  [Часткова спеціалізація: обидва елементи типу "
              << typeName<T>() << "]" << std::endl;
    std::cout << "  Перший:  " << first << std::endl;
    std::cout << "  Другий:  " << second << std::endl;
}

template <typename T>
T Pair<T, T>::larger() const {
    return (first > second) ? first : second;
}

template <typename T>
void Pair<T, T>::swap_items() {
    std::swap(first, second);
}
