#include "MaxValue.h"
#include <cstring>

template <>
const char* max_value<const char*>(const char* a, const char* b) {
    return (std::strcmp(a, b) > 0) ? a : b;
}
