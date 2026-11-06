#include <iostream>
#include <windows.h>
#include "List.h"

using namespace std;

// Сортування обміном за СПАДАННЯМ кількості елементів.
// Обмін, якщо !(a[j] >= a[j+1]), тобто a[j] менший за a[j+1]
void sortDescending(List* arr, int n) {
    for (int i = 0; i < n - 1; ++i)
        for (int j = 0; j < n - 1 - i; ++j)
            if (!(arr[j] >= arr[j + 1])) {
                List tmp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = tmp;
            }
}

void printAll(const List* arr, int n) {
    for (int i = 0; i < n; ++i)
        cout << i + 1 << ") " << arr[i] << "  (елементів: "
             << arr[i].size() << ")" << endl;
}

int main() {
    // Встановлюємо кодування UTF-8 для вводу та виводу консолі Windows
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    int n;
    cout << "Кількість списків: ";
    cin >> n;
    if (n <= 0) {
        cout << "Некоректна кількість списків" << endl;
        return 1;
    }

    List* arr = new List[n];
    for (int i = 0; i < n; ++i) {
        cout << "Список " << i + 1
             << " (спочатку кількість, потім елементи): ";
        cin >> arr[i];
    }

    cout << "\nВихідний масив:" << endl;
    printAll(arr, n);

    sortDescending(arr, n);
    cout << "\nПісля сортування за спаданням кількості елементів:" << endl;
    printAll(arr, n);

    // Після сортування список з найменшою кількістю елементів — останній.
    // Копія потрібна, бо сам цей список теж буде змінено.
    List smallest = arr[n - 1];
    cout << "\nСписок з найменшою кількістю елементів: " << smallest << endl;

    for (int i = 0; i < n; ++i)
        for (int k = 0; k < smallest.size(); ++k)
            arr[i] = arr[i] - smallest.getAt(k);

    cout << "\nПісля вилучення елементів найменшого спискy:" << endl;
    printAll(arr, n);

    delete[] arr;
    return 0;
}