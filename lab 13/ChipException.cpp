#include "ChipException.h"

ChipException::ChipException(const std::string& message) : message_(message) {}
ChipException::~ChipException() noexcept {}
const char* ChipException::what() const noexcept { return message_.c_str(); }

InvalidInputException::InvalidInputException(const std::string& message)
    : ChipException("Помилка введення: " + message) {}

FileException::FileException(const std::string& message)
    : ChipException("Помилка файлу: " + message) {}

IndexException::IndexException(const std::string& message)
    : ChipException("Помилка індексу: " + message) {}
