#pragma once
#include <stdio.h>

class fl {
protected:
    int mant;  // мантисса (целое число от 1000 до 9999 или -9999 до -1000)
    int exp;   // экспонента (показатель степени 10)

public:
    fl();
    fl(double v);      // конструктор из double
    fl(int a, int b);  // конструктор из мантиссы и экспоненты
    void print();      // вывод числа
    void sokr();       // нормализация числа

    // Дружественные операторы для арифметических операций
    friend fl operator+ (fl, fl);
    friend fl operator- (fl, fl);
    friend fl operator* (fl, fl);
};
