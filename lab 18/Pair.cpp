#include "Pair.h"

// ----- Повна спеціалізація Pair<std::string, bool> -----
// (звичайний клас після спеціалізації - реалізація у .cpp)
Pair<std::string, bool>::Pair(const std::string& a, bool b) : first(a), second(b) {}

Pair<std::string, bool>::~Pair() {}

void Pair<std::string, bool>::print_pair() const {
    std::cout << "  [Повна спеціалізація Pair<string, bool>]" << std::endl;
    std::cout << "  Перший:  " << first << " (тип: " << typeName<std::string>() << ")" << std::endl;
    std::cout << "  Другий:  " << (second ? "так" : "ні") << " (тип: bool)" << std::endl;
}
