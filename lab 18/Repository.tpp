// Реалізація шаблонів Repository (підключається в кінці Repository.h)

// ----- Основний шаблон -----
template <class T>
Repository<T>::Repository(T value) : m_value(value) {}

template <class T>
Repository<T>::~Repository() {}

template <class T>
void Repository<T>::print() const {
    std::cout << "  " << m_value << std::endl;
}

// ----- Часткова спеціалізація Repository<T*> -----
template <class T>
Repository<T*>::Repository(T* value) : m_value(value) {}

template <class T>
Repository<T*>::~Repository() {}

template <class T>
void Repository<T*>::print() const {
    if (m_value)
        std::cout << "  [вказівник] значення за адресою: " << *m_value << std::endl;
    else
        std::cout << "  [вказівник] nullptr" << std::endl;
}
