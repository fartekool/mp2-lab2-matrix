// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
// Тестирование матриц

#include <iostream>
#include "tmatrix.h"
//---------------------------------------------------------------------------

void main()
{
    /*TDynamicMatrix<int> a(5), b(5), c(5);
    int i, j;

    setlocale(LC_ALL, "Russian");
    cout << "Тестирование класс работы с матрицами"
        << endl;
    for (i = 0; i < 5; i++)
        for (j = i; j < 5; j++ )
        {
        a[i][j] =  i * 10 + j;
        b[i][j] = (i * 10 + j) * 100;
        }
    c = a + b;
    cout << "Matrix a = " << endl << a << endl;
    cout << "Matrix b = " << endl << b << endl;
    cout << "Matrix c = a + b" << endl << c << endl;*/
    /*int arr1[3] = { 1, 2, 3 };
    int arr2[3] = { 4, 5, 6 };
    TDynamicVector<int> a(arr1, 3);
    TDynamicVector<int> b(a);
    std::cout << a << std::endl;
    std::cout << b << std::endl;*/
    //std::cout << (a == b) << '\n' << (a != b) << '\n';

    /*b *= 100;
    a = b;
    a -= b;
    a = a + 1;
    std::cout << b << std::endl;
    std::cout << a << std::endl;*/
    /*int c = a * b;
    std::cout << c << '\n';*/
    
    TDynamicMatrix<int> A(5), C(5);
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            A[i][j] = i * 5 + j + 1;
            C[i][j] = 1;
        }
    }
    std::cout << A << std::endl;
    int arr[5] = { 1, 1, 1, 1, 1 };
    TDynamicVector<int> a(arr, 5);
    TDynamicVector<int> b(A * a);
    
    
    /*int arr[3] = { 1, 1, 1 };
    TDynamicVector<int> a(arr, 3), b(arr, 3);
    TDynamicVector<int> c(3), d(3);
    c = ++a;
    d = b++;
    std::cout << a << '\n' << b << '\n' << c << '\n' << d;*/
    
    TDynamicMatrix<int> B(A * A);
    std::cout << B << std::endl;
    C = B;
    C *= 2;
    B *= 3;
    std::cout << C << '\n' << B;
}
//---------------------------------------------------------------------------
