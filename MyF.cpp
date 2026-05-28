#include "myF.h"
#include <cmath>

fl::fl() {
    mant = 0;
    exp = 0;

}

// Конструктор из double
fl::fl(double v) {
    exp = 0;

    // Обработка нуля
    if (v == 0.0) {
        mant = 0;
        exp = 0;
        return;
    }

    // Нормализация: приводим число к диапазону [0.1, 1.0) по модулю
    double abs_v = (v < 0) ? -v : v;

    while (abs_v >= 1.0) {
        abs_v /= 10;
        exp++;
    }
    while (abs_v < 0.1) {
        abs_v *= 10;
        exp--;
    }

    // Округление до 4 знаков
    abs_v += 0.00005;
    mant = (int)(abs_v * 10000);

    // Восстанавливаем знак
    if (v < 0) {
        mant = -mant;
    }
}

// Конструктор из мантиссы и экспоненты
fl::fl(int m, int e) {
    mant = m;
    exp = e;
    if (mant == 0) {
        exp = 0;
    }
    sokr();
}

// Вывод числа
void fl::print() {
    double value = (mant / 10000.0) * pow(10, exp);
    printf("%.4f[%d*10^%d] ", value, mant, exp);
}

// Нормализация: мантисса должна быть в [1000, 9999] или [-9999, -1000]
void fl::sokr() {
    if (mant == 0) {
        exp = 0;
        return;
    }

    int abs_mant = (mant < 0) ? -mant : mant;
    int sign = (mant < 0) ? -1 : 1;

    while (abs_mant >= 10000) {
        abs_mant /= 10;
        exp++;
    }

    mant = sign * abs_mant;
}

// Оператор сложения (исправлен для отрицательных экспонент)
fl operator+ (fl a, fl b) {   // ПЕРЕДАЧА ПО ЗНАЧЕНИЮ, СОЗДАЮТСЯ КОПИИ. оригинал не меняется
    // Выравниваем экспоненты (приводим к большей экспоненте)
    while (a.exp > b.exp) {
        b.mant *= 10;
        b.exp++;
        // Нормализация при переполнении
        if (b.mant >= 100000 || b.mant <= -100000) {
            int last_digit = b.mant % 10;
            b.mant /= 10;
            b.exp--;
            if (last_digit >= 5 || last_digit <= -5) {
                b.mant += (b.mant > 0 ? 1 : -1);
            }
        }
    }

    while (b.exp > a.exp) {
        a.mant *= 10;
        a.exp++;
        if (a.mant >= 100000 || a.mant <= -100000) {
            int last_digit = a.mant % 10;
            a.mant /= 10;
            a.exp--;
            if (last_digit >= 5 || last_digit <= -5) {
                a.mant += (a.mant > 0 ? 1 : -1);
            }
        }
    }

    int result_mant = a.mant + b.mant;
    int result_exp = a.exp;

    fl result(result_mant, result_exp);
    return result;
}

// Оператор вычитания
fl operator- (fl a, fl b) {
    b.mant = -b.mant;
    return a + b;
}

// Оператор умножения
fl operator* (fl a, fl b) {
    long long temp_mant = (long long)a.mant * b.mant;
    int result_exp = a.exp + b.exp;

    int sign = 1;
    if (temp_mant < 0) {
        sign = -1;
        temp_mant = -temp_mant;
    }

    temp_mant = (temp_mant + 5000) / 10000;

    fl result((int)(sign * temp_mant), result_exp);
    return result;
}
