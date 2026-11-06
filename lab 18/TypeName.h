#ifndef TYPENAME_H
#define TYPENAME_H

#include <string>
#include <typeinfo>
#include <cstdlib>
#ifdef __GNUC__
#include <cxxabi.h>
#endif

// Повертає читабельну назву типу (typeid(T).name() у GCC повертає "закодовану" назву)
template <typename T>
std::string typeName() {
    std::string result = typeid(T).name();
#ifdef __GNUC__
    int status = 0;
    char* demangled = abi::__cxa_demangle(result.c_str(), nullptr, nullptr, &status);
    if (status == 0 && demangled) {
        result = demangled;
        std::free(demangled);
    }
    const std::string longStr =
        "std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >";
    size_t pos;
    while ((pos = result.find(longStr)) != std::string::npos)
        result.replace(pos, longStr.size(), "std::string");
#endif
    return result;
}

#endif
