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
    int arr1[3] = { 1, 2, 3 };
    int arr2[3] = { 4, 5, 6 };
    TDynamicVector<int> a(arr1, 3);
    TDynamicVector<int> b(a);
    std::cout << a << std::endl;
    std::cout << b << std::endl;
    //std::cout << (a == b) << '\n' << (a != b) << '\n';

    /*b *= 100;
    a = b;
    a -= b;
    a = a + 1;
    std::cout << b << std::endl;
    std::cout << a << std::endl;*/
    int c = a * b;
    std::cout << c << '\n';
}
//---------------------------------------------------------------------------
