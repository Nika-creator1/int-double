#pragma once
#include "MyF.h"
#include <stdio.h> 

class Satur : public fl {
    char ValueFlag;      // флаг переполнения: 1 - число вышло за пределы
    void checkflag();    // проверка и корректировка переполнения

public:
    Satur();                     // конструктор по умолчанию (создает 0)
    Satur(int, int);             // конструктор из мантиссы и экспоненты
    Satur(double);               // конструктор из double
    Satur(fl f);                 // конструктор из fl
    void print();                // переопределенный вывод (с * при переполнении)
    Satur& operator=(const Satur& other);  // оператор присваивания
};
