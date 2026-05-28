#include "myF.h"
#include "Satur.h" 
#include "vector.h"
#include "TVector.h"
#include <stdlib.h>
#include <locale.h>
#include <utility> 
vector create() {
    vector temp(3);
    temp[0] = Satur(10);
    temp[1] = Satur(20);
    temp[2] = Satur(30);
    return temp;  // возвращает ВРЕМЕННЫЙ объект
}
//условно, создается вектор temp, который переписывается в вектор с. vector c = temp. поскольку temp локальная переменная, временный объект,
// он уничтожается при выходе из функции, сразу после передачи значений в с. копирование перемещением

int main(void)
{
    setlocale(LC_ALL, "Russian");
    printf("\n=== Тест временного объекта ===\n");

    // create() возвращает ВРЕМЕННЫЙ объект → перемещение!
    vector c = create();

    printf("Результат c = ");
    c.print();
    printf("\n");

    printf("\nчисла:  \n");
    double frs = 1234.501;
    Satur  myff(frs);
    myff.print();
    printf("\n     \n");

    double sc = 1234.345;
    Satur  sc2(sc);
    sc2.print();

    Satur deistvie = myff + sc2;
    //1:вызов operator+((fl)myff, (fl)sc2) satur наследует fl, в fl содружественный опереатор+
    // 
    // а и b локальные переменные в функции. копируют часть fl в myff и sc2 и работают с ней.
    // 
    // создаются КОПИИ (а и b). параметры передаются по значению (не ссылка), поэтому копии. оператор+ не должен изменять исходные числа.
    // MyF.cpp строка 72 -> (fl a, fl b) — КОПИИ (передача по значению) 
    // если бы было: (fl& a, fl& b) — ССЫЛКИ (без копий, работаем с оригиналом) или (const fl& a, const fl& b) — КОНСТАНТНЫЕ ССЫЛКИ (без копий, но менять нельзя)
    // 
    //2:создается временный объект типа fl 
    //3:Вызов конструктора: Satur::Satur( fl ) для создания deistvie
    //4:Готовый объект deistvie (тип Satur)
    printf("\n-- сложение --\n");
    (deistvie).print();

    deistvie = sc2 - myff;
    printf("\n-- вычитание --\n");
    (deistvie).print();

    printf("\n-- умножение --\n");
    deistvie = sc2 * myff;
    (deistvie).print();

    printf("\n");

    // ========== Тестирование класса vector ==========
    printf("\n=== Тестирование класса vector ===\n");

    // Создаем векторы
    vector vec1(3);
    vector vec2(3);

    // Заполняем первый вектор
    vec1[0] = Satur(123.456);
    vec1[1] = Satur(78.9);
    vec1[2] = Satur(0.0123);

    // Заполняем второй вектор
    vec2[0] = Satur(100.0);
    vec2[1] = Satur(20.0);
    vec2[2] = Satur(0.005);

    // Выводим исходные векторы
    printf("vec1 = ");
    vec1.print();

    printf("vec2 = ");
    vec2.print();

    // Сложение векторов
    vector sum = vec1 + vec2; // ПЕРЕМЕЩЕНИЕ sum переписывает себе значение vec1 + vec2  и vec1 + vec2 уничтожается
    printf("vec1 + vec2 = ");
    sum.print();
    (vec1 + vec2).print();

    // Вычитание векторов
    vector diff = vec1 - vec2;
    printf("vec1 - vec2 = ");
    diff.print();
  
    // Копирование вектора КОПИРОВАНИЕМ
    vector vec3 = vec1;
    printf("vec3 (копия vec1) = ");
    vec3.print();
    //Копирование вектора ПЕРЕМЕЩЕНИЕМ
    //
    //
    //
   

    

 
    
    // 
    //
    //
    printf("\n Тестирование TVector \n");

    printf("vector double: ");
    TVector<double> vecD(4);
    vecD.print();
    printf("\n \n");
    printf("vector char: ");
    TVector<char> vecC(4);
    vecC.print();
    printf("\n \n");printf("vector int: ");
    TVector<int> vecI(4);
    vecI.print();
    printf("\n \n");
    TVector<Satur> vec(3);

    vec[0] = Satur(123.456);
    vec[1] = Satur(78.9);
    vec[2] = Satur(0.0123);

    // Вывод - работает, потому что у Satur есть метод print()
    printf("vec1 = ");
    vec.print();  // [123.5000[1235*10^3], 78.9000[7890*10^2], 0.0123[1230*10^-1]]
    printf("\n");

    // Сложение векторов
    TVector<Satur> vec5(3);
    vec5[0] = Satur(100);
    vec5[1] = Satur(20);
    vec5[2] = Satur(0.005);

    printf("vec2 = ");
    vec5.print();
    TVector<Satur> sum1= vec + vec5;
    printf("\n");
    printf("sum = ");
    sum1.print();  // результат сложения
    return 0;
}
