#include <iostream>
#include "PowerHandler.h"
#ifdef _WIN32
#include <windows.h>
#endif

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif
    PowerHandler handler;
    handler.inputAll();
    handler.printAll();
    handler.process();
    return 0;
}
