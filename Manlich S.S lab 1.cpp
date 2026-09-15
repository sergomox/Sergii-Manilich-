#include <iostream>
#include <iomanip>

using namespace std;

const int SIZE = 4;

// Обов'язкова структура за методичкою
struct data_t {
    void* values[SIZE];
    int types[SIZE];
};

// Функція для виводу значень
void print_data(data_t* data) {
    for (int i = 0; i < SIZE; i++) {
        if (data->types[i] == 0) cout << "a = " << *static_cast<short*>(data->values[i]) << endl;
        if (data->types[i] == 1) cout << "b = " << *static_cast<long*>(data->values[i]) << endl;
        if (data->types[i] == 2) cout << "c = " << *static_cast<int*>(data->values[i]) << endl;
        if (data->types[i] == 3) cout << "d = " << *static_cast<float*>(data->values[i]) << endl;
    }
}

int main() {
    // 1. Створюємо змінні
    short a = 45;
    long b = 130;
    int c = 120;
    float d = 0.8f;

    // 2. Заповнюємо структуру
    data_t my_data;
    my_data.values[0] = &a; my_data.types[0] = 0;
    my_data.values[1] = &b; my_data.types[1] = 1;
    my_data.values[2] = &c; my_data.types[2] = 2;
    my_data.values[3] = &d; my_data.types[3] = 3;

    // 3. Виводимо на екран
    print_data(&my_data);

    // 4. Обчислюємо двома способами
    float implicit_res = (a / (b - c)) * d;
    float explicit_res = (static_cast<float>(a) / static_cast<float>(b - c)) * d;

    // 5. Виводимо результати
    cout << fixed << setprecision(3);
    cout << "Неявне перетворення: " << implicit_res << endl;
    cout << "Явне перетворення: " << explicit_res << endl;

    return 0;
}