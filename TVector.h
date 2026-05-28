#pragma once
#include <iostream>
#include <stdexcept>

/**
 * Шаблонный класс вектор (динамический массив)
 * T - тип элементов (может быть int, double, fl, Satur и т.д.)
 */
template <typename T>
class TVector {
private:
    T* v;     // Указатель на динамический массив элементов
    int sz;   // Размер вектора (количество элементов)

public:

    // Конструктор по умолчанию (создает вектор из 5 элементов)
    TVector();

    // Конструктор с заданным размером
    TVector(int s);

    // Конструктор копирования
    TVector(const TVector& other);

    // Деструктор
    ~TVector();


    // Оператор присваивания (копирование)
    TVector& operator=(const TVector& other);

    // Неконстантная версия (для изменения элементов)
    T& operator[](int i);

    // КОНСТАНТНАЯ ВЕРСИЯ (для чтения из const-объектов)
    const T& operator[](int i) const;

    //методы

        // Получить размер (inline - для эффективности)
    inline int size() const { return sz; }

    // Изменить размер вектора
    void resize(int newSize);

    // Вывод вектора на экран
    void print() const;
};



//Конструктор по умолчанию

template <typename T>
TVector<T>::TVector() {
    sz = 5;                                          // размер по умолчанию
    v = new T[sz];                                   // выделяем память
    for (int i = 0; i < sz; i++) {
        v[i] = T();                                  // T() - значение по умолчанию
    }                                                // для int это 0, для Satur это 0
}

//Конструктор с заданным размером

template <typename T>
TVector<T>::TVector(int s) {
    if (s < 1) {
        throw std::invalid_argument("Incorrect length");
    }
    sz = s;
    v = new T[sz];                                   // выделяем память
    for (int i = 0; i < sz; i++) {
        v[i] = T();                                  // инициализируем значением по умолчанию
    }
}


//Конструктор копирования

template <typename T>
TVector<T>::TVector(const TVector& other) {
    sz = other.sz;                                   // копируем размер
    v = new T[sz];                                   // выделяем СВОЮ память
    for (int i = 0; i < sz; i++) {
        v[i] = other.v[i];                           // копируем каждый элемент
    }
}

//Деструктор

template <typename T>
TVector<T>::~TVector() {
    delete[] v;                                      // удаляем массив
    v = nullptr;                                     // для безопасности (необязательно)
    sz = 0;
}

// Оператор присваивания копированием

//ВАЖНО: освобождает старую память и выделяет новую

template <typename T>
TVector<T>& TVector<T>::operator=(const TVector& other) {
    // Защита от самоприсваивания (a = a)
    if (this == &other) {
        return *this;
    }


    T* new_v = new T[other.sz];                      // выделяем новую память

    for (int i = 0; i < other.sz; i++) {
        new_v[i] = other.v[i];                       // копируем элементы
    }

    delete[] v;                                      // освобождаем старую память
    v = new_v;                                       // переключаемся на новую
    sz = other.sz;

    return *this;
}

/**
 * Оператор доступа по индексу (неконстантный)
 * Для изменения элементов: vec[0] = value;
 */
template <typename T>
T& TVector<T>::operator[](int i) {
    if (i < 0 || i >= sz) {
        throw std::out_of_range("Error: index out of range");
    }
    return v[i];
}

/**
  Оператор доступа по индексу (КОНСТАНТНЫЙ)
 Для чтения элементов из const-объектов
  БЕЗ ЭТОГО операторы + и - НЕ РАБОТАЮТ!
  */
 
template <typename T>
const T& TVector<T>::operator[](int i) const {  // ← вот эта реализация была пропущена!
    if (i < 0 || i >= sz) {
        throw std::out_of_range("Error: index out of range");
    }
    return v[i];
}


//Изменение размера вектора

 // Если новый размер БОЛЬШЕ - новые элементы заполняются значением по умолчанию
 // Если новый размер МЕНЬШЕ - лишние элементы отбрасываются

template <typename T>
void TVector<T>::resize(int newSize) {
    if (newSize < 1) {
        throw std::invalid_argument("Incorrect length for resize");
    }

    // Выделяем новую память
    T* new_v = new T[newSize];

    // Копируем существующие элементы (сколько поместится)
    int elementsToCopy = (newSize > sz) ? sz : newSize;  // минимум из sz и newSize

    for (int i = 0; i < elementsToCopy; i++) {
        new_v[i] = v[i];
    }

    // Если новый размер больше - заполняем новые элементы значением по умолчанию
    for (int i = elementsToCopy; i < newSize; i++) {
        new_v[i] = T();                                 // T() - значение по умолчанию
    }

    // Освобождаем старую память и переключаемся на новую
    delete[] v;
    v = new_v;
    sz = newSize;
}

/**
 * Вывод вектора на экран
 */
 // ============ ОБЩАЯ ВЕРСИЯ (для встроенных типов) ============
 // Эта версия работает для int, double, char, string и любых типов,
 

template <typename T>
void TVector<T>::print() const {
    std::cout << "[";
    for (int i = 0; i < sz; i++) {
        std::cout << v[i];        // использует operator<<
        if (i < sz - 1) {
            std::cout << ", ";
        }
    }
    std::cout << "]";
}

// ============ СПЕЦИАЛИЗАЦИЯ ДЛЯ fl (нет operator<<) ============
template <>
inline void TVector<fl>::print() const {
    std::cout << "[";
    for (int i = 0; i < sz; i++) {
        v[i].print();             // использует метод print() класса fl
        if (i < sz - 1) {
            std::cout << ", ";
        }
    }
    std::cout << "]";
}
//специализация имеет приоритет над общим шаблоном.

//Специализации важнее общего шаблона. Компилятор всегда выбирает наиболее конкретную версию.
//
//Когда вызывается print() для TVector<int> — общая версия подходит идеально.
//Когда для TVector<fl> — компилятор видит, что есть специализация именно для fl, и выбирает её.
// ============ СПЕЦИАЛИЗАЦИЯ ДЛЯ Satur (нет operator<<) ============
template <>
inline void TVector<Satur>::print() const {
    std::cout << "[";
    for (int i = 0; i < sz; i++) {
        v[i].print();             // использует метод print() класса Satur
        if (i < sz - 1) {
            std::cout << ", ";
        }
    }
    std::cout << "]";
}

//Оператор сложения двух векторов (поэлементно)
//Требует, чтобы для типа T был определен оператор +

template <typename T>
TVector<T> operator+(const TVector<T>& a, const TVector<T>& b) {
    if (a.size() != b.size()) {
        throw std::invalid_argument("Error: vectors have different sizes for addition");
    }

    TVector<T> result(a.size());

    for (int i = 0; i < a.size(); i++) {
        result[i] = a[i] + b[i];   // использует operator+ для типа T
    }

    return result;
}

//Оператор вычитания двух векторов (поэлементно)

template <typename T>
TVector<T> operator-(const TVector<T>& a, const TVector<T>& b) {
    if (a.size() != b.size()) {
        throw std::invalid_argument("Error: vectors have different sizes for subtraction");
    }

    TVector<T> result(a.size());

    for (int i = 0; i < a.size(); i++) {
        result[i] = a[i] - b[i];   // использует operator- для типа T
    }

    return result;
}
