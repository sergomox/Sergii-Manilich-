#include "PowerHandler.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <limits>

using std::cin;
using std::cout;
using std::string;

// ---------- допоміжні функції безпечного введення ----------
static double readDouble(const string& prompt, double minValue) {
    while (true) {
        cout << prompt;
        string line;
        std::getline(cin, line);
        try {
            size_t pos;
            double v = std::stod(line, &pos);
            if (pos == line.size() && v >= minValue) return v;
        } catch (...) {}
        cout << "  Помилка: введіть число >= " << minValue << "\n";
    }
}

static int readInt(const string& prompt, int minValue) {
    while (true) {
        cout << prompt;
        string line;
        std::getline(cin, line);
        try {
            size_t pos;
            int v = std::stoi(line, &pos);
            if (pos == line.size() && v >= minValue) return v;
        } catch (...) {}
        cout << "  Помилка: введіть ціле число >= " << minValue << "\n";
    }
}

static string readLine(const string& prompt) {
    string s;
    do {
        cout << prompt;
        std::getline(cin, s);
    } while (s.empty());
    return s;
}

// ---------- клас PowerHandler ----------
PowerHandler::PowerHandler() { cout << "[Конструктор PowerHandler]\n"; }
PowerHandler::~PowerHandler() { cout << "[Деструктор PowerHandler]\n"; }

void PowerHandler::inputPowerBank() {
    PowerBank p;
    cout << "\n--- Введення павербанка ---\n";
    p.data.model   = readLine("Модель: ");
    p.data.voltage = readDouble("Вихідна напруга, В: ", 0.1);
    p.data.power   = readDouble("Максимальна потужність, Вт: ", 0.1);
    p.data.price   = readDouble("Ціна, грн: ", 0);
    p.pb.capacityMah = readDouble("Ємність, мА·год: ", 1);
    p.pb.usbPorts    = readInt("Кількість USB-портів: ", 1);
    banks.push_back(p);
}

void PowerHandler::inputGenerator() {
    Generator g;
    cout << "\n--- Введення генератора ---\n";
    g.data.model   = readLine("Модель: ");
    g.data.voltage = readDouble("Вихідна напруга, В: ", 0.1);
    g.data.power   = readDouble("Максимальна потужність, Вт: ", 0.1);
    g.data.price   = readDouble("Ціна, грн: ", 0);
    while (true) {
        g.gen.fuel = readLine("Пальне (бензин/дизель): ");
        if (g.gen.fuel == "бензин" || g.gen.fuel == "дизель") break;
        cout << "  Помилка: введіть «бензин» або «дизель»\n";
    }
    g.gen.consumption = readDouble("Витрата пального, л/год: ", 0.01);
    g.gen.tank        = readDouble("Об'єм баку, л: ", 0.1);
    gens.push_back(g);
}

void PowerHandler::inputAll() {
    int n = readInt("Скільки павербанків ввести? ", 0);
    for (int i = 0; i < n; ++i) inputPowerBank();
    int m = readInt("Скільки генераторів ввести? ", 0);
    for (int i = 0; i < m; ++i) inputGenerator();
}

void PowerHandler::printPowerBank(const PowerBank& p, int num) const {
    cout << num << ". " << p.typeName() << " | " << p.data.model
         << " | " << p.data.voltage << " В"
         << " | " << p.data.power << " Вт"
         << " | " << p.pb.capacityMah << " мА·год"
         << " | USB: " << p.pb.usbPorts
         << " | " << p.data.price << " грн\n";
}

void PowerHandler::printGenerator(const Generator& g, int num) const {
    cout << num << ". " << g.typeName() << " | " << g.data.model
         << " | " << g.data.voltage << " В"
         << " | " << g.data.power << " Вт"
         << " | " << g.gen.fuel
         << " | " << g.gen.consumption << " л/год"
         << " | бак " << g.gen.tank << " л"
         << " | " << g.data.price << " грн\n";
}

void PowerHandler::printAll() const {
    cout << "\n========== ВХІДНІ ДАНІ ==========\n";
    cout << "Павербанки (" << banks.size() << "):\n";
    for (size_t i = 0; i < banks.size(); ++i) printPowerBank(banks[i], i + 1);
    cout << "Генератори (" << gens.size() << "):\n";
    for (size_t i = 0; i < gens.size(); ++i) printGenerator(gens[i], i + 1);
}

void PowerHandler::process() const {
    cout << "\n========== РЕЗУЛЬТАТИ ==========\n";
    cout << std::fixed << std::setprecision(2);

    if (banks.empty() && gens.empty()) {
        cout << "Даних немає.\n";
        return;
    }

    // 1. Загальна вартість та загальна кількість пристроїв
    double total = 0;
    for (const auto& p : banks) total += p.data.price;
    for (const auto& g : gens)  total += g.data.price;
    cout << "Кількість пристроїв: " << banks.size() + gens.size() << "\n";
    cout << "Загальна вартість: " << total << " грн\n";

    // 2. Павербанки: енергія E = C * U / 1000 (Вт·год) та сумарна енергія
    if (!banks.empty()) {
        double sumE = 0;
        const PowerBank* best = &banks[0];
        for (const auto& p : banks) {
            double e = p.pb.capacityMah * p.data.voltage / 1000.0;
            sumE += e;
            cout << "  " << p.data.model << ": запас енергії = " << e << " Вт·год\n";
            if (p.pb.capacityMah > best->pb.capacityMah) best = &p;
        }
        cout << "Сумарна енергія павербанків: " << sumE << " Вт·год\n";
        cout << "Павербанк з найбільшою ємністю: " << best->data.model
             << " (" << best->pb.capacityMah << " мА·год)\n";
    }

    // 3. Генератори: час роботи = бак / витрата, найпотужніший
    if (!gens.empty()) {
        const Generator* strongest = &gens[0];
        for (const auto& g : gens) {
            double t = g.gen.tank / g.gen.consumption;
            cout << "  " << g.data.model << ": час роботи на одному баку = " << t << " год\n";
            if (g.data.power > strongest->data.power) strongest = &g;
        }
        cout << "Найпотужніший генератор: " << strongest->data.model
             << " (" << strongest->data.power << " Вт)\n";
    }

    // 4. Максимальна потужність серед усіх джерел
    double maxP = 0;
    string maxName;
    for (const auto& p : banks) if (p.data.power > maxP) { maxP = p.data.power; maxName = p.data.model; }
    for (const auto& g : gens)  if (g.data.power > maxP) { maxP = g.data.power; maxName = g.data.model; }
    cout << "Максимальна потужність серед усіх джерел: " << maxP << " Вт (" << maxName << ")\n";
}
