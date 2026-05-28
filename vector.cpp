#include <stdio.h>
#include <stdlib.h>
#include "vector.h"

// Конструктор с заданным размером
vector::vector(int s) {
    if (s < 1) error("Error: size must be positive");  // проверка размера
    sz = s;
    v = new Satur[s];  // выделяем память для s объектов Satur
    if (v == nullptr) error("Error: memory allocation failed");
}

// Конструктор по умолчанию - создает вектор из 99 элементов
vector::vector() : vector(99) {}

// Конструктор копирования - создает копию
vector::vector(const vector& other) {
    sz = other.sz;
    v = new Satur[sz];  // выделяем новую память

    // Копируем каждый элемент
    for (int i = 0; i < sz; ++i) {
        v[i] = other.v[i];
    }
}

// Конструктор перемещения - забирает ресурсы у другого объекта (эффективно)
vector::vector(vector&& other) noexcept {
    v = other.v;          // забираем указатель
    sz = other.sz;        // забираем размер

    // Обнуляем other, чтобы его деструктор не удалил наши данные
    other.v = nullptr;
    other.sz = 0;
}

// Деструктор - освобождает память
vector::~vector() {
    delete[] v;  // освобождаем массив
}

// Получить размер вектора
int vector::size() {
    return sz;
}

// Оператор доступа по индексу с проверкой границ
Satur& vector::operator[](int i) {
    if (i < 0 || i >= sz) error("Error: index out of range");
    return v[i];
}

// Метод доступа по индексу
Satur& vector::elem(int i) {
    return v[i];
}

// Функция обработки ошибок - выводит сообщение и завершает программу
void error(const char* p) {
    printf("%s\n", p);
    exit(1);
}

// Оператор присваивания копированием
vector& vector::operator=(const vector& other) {
    if (this == &other) return *this;  // защита от самоприсваивания

    // Если размеры совпадают, просто копируем данные (без перевыделения памяти)
    if (sz == other.sz) {
        for (int i = 0; i < sz; ++i)
            v[i] = other.v[i];
        return *this;
    }

    // Разные размеры - нужно перевыделять память
    Satur* new_v = new Satur[other.sz];  // выделяем новую память
    for (int i = 0; i < other.sz; ++i)
        new_v[i] = other.v[i];

    delete[] v;     // освобождаем старую память
    v = new_v;      // устанавливаем новый указатель
    sz = other.sz;  // обновляем размер

    return *this;
}

// Оператор присваивания перемещением
vector& vector::operator=(vector&& other) noexcept {
    if (this == &other) return *this;  // защита от самоприсваивания

    delete[] v;                // освобождаем свои старые ресурсы
    v = other.v;               // забираем ресурсы other
    sz = other.sz;

    other.v = nullptr;         // обнуляем other
    other.sz = 0;

    return *this;
}

// Оператор сложения векторов (поэлементное сложение)
vector operator+(vector& a, vector& b) {
    int s = a.size();
    if (s != b.size()) error("Error: vectors have different sizes");

    vector sum(s);  // создаем вектор-результат

    // Поэлементное сложение
    for (int i = 0; i < s; i++) {
        sum.elem(i) = a.elem(i) + b.elem(i);  // использует operator+ класса Satur
    }

    return sum;
}

// Оператор вычитания векторов (поэлементное вычитание)
vector operator-(vector& a, vector& b) {
    int s = a.size();
    if (s != b.size()) error("Error: vectors have different sizes");

    vector sub(s);

    // Используем указатели для эффективности (без проверки границ)
    Satur* sp = sub.v;    // указатель на результат
    Satur* ap = a.v;      // указатель на первый вектор
    Satur* bp = b.v;      // указатель на второй вектор

    // Поэлементное вычитание с использованием арифметики указателей
    for (int i = 0; i < s; i++) {
        *sp++ = *ap++ - *bp++;  // использует operator- класса Satur
    }

    return sub;
}

// Печать вектора
void vector::print() {
    printf("[ ");
    for (int i = 0; i < sz; ++i) {
        v[i].print();  // вызываем print для каждого элемента
        if (i < sz - 1) {
            printf(", ");
        }
    }
    printf(" ]\n");
}
