#include "Repository.h"

// ----- Повна спеціалізація print() для double -----
template <>
void Repository<double>::print() const {
    std::cout << "  " << std::scientific << m_value << std::defaultfloat << std::endl;
}

// ----- Повна спеціалізація класу Repository<bool> -----
Repository<bool>::Repository(bool value) : m_value(value) {}

Repository<bool>::~Repository() {}

void Repository<bool>::print() const {
    std::cout << "  " << (m_value ? "увімкнено (true)" : "вимкнено (false)") << std::endl;
}

void Repository<bool>::toggle() {
    m_value = !m_value;
}
