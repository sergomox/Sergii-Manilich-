#ifndef CHIPEXCEPTION_H
#define CHIPEXCEPTION_H

#include <exception>
#include <string>

// Базовий клас-виняток програми (нащадок std::exception)
class ChipException : public std::exception {
protected:
    std::string message_;
public:
    explicit ChipException(const std::string& message);
    virtual ~ChipException() noexcept;
    const char* what() const noexcept override;
};

// Некоректні вхідні дані
class InvalidInputException : public ChipException {
public:
    explicit InvalidInputException(const std::string& message);
};

// Помилки роботи з файлами
class FileException : public ChipException {
public:
    explicit FileException(const std::string& message);
};

// Вихід за межі колекції
class IndexException : public ChipException {
public:
    explicit IndexException(const std::string& message);
};

#endif
