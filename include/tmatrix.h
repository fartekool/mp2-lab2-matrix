// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
//

#ifndef __TDynamicMatrix_H__
#define __TDynamicMatrix_H__

#include <iostream>
#include <algorithm>
#include <cassert>
using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// Динамический вектор - 
// шаблонный вектор на динамической памяти
template<typename T>
class TDynamicVector
{
protected:
    size_t sz;
    T* pMem;
public:
    TDynamicVector(size_t size = 1) : sz(size)
    {
        if (sz == 0 || sz > MAX_VECTOR_SIZE)
            throw out_of_range("Vector size must be between 1 and 100000000");
        pMem = new T[sz]();// {}; // У типа T д.б. констуктор по умолчанию
    }
    TDynamicVector(T* arr, size_t s) : sz(s)
    {
        assert(arr != nullptr && "TDynamicVector ctor requires non-nullptr arg");
        pMem = new T[sz];
        std::copy(arr, arr + sz, pMem);
    }
    TDynamicVector(const TDynamicVector& v): sz(v.sz)
    { 
        pMem = new T[sz];
        for (size_t i = 0; i < sz; ++i)
        {
            pMem[i] = v.pMem[i];
        }
    }
    TDynamicVector(TDynamicVector&& v) noexcept
    {
        pMem = nullptr;
        sz = 0;
        swap(*this, v);
    }
    ~TDynamicVector()
    {
        sz = 0;
        delete[] pMem;
    }
    TDynamicVector& operator=(const TDynamicVector& v)
    {
        if (this == &v)
            return *this;
        if (sz != v.sz)
        {   
            sz = v.sz;
            delete[] pMem;
            pMem = new T[sz];
        }
        for (size_t i = 0; i < sz; ++i)
            pMem[i] = v.pMem[i];
        return *this;
    }
    TDynamicVector& operator=(TDynamicVector&& v) noexcept
    {
        swap(*this, v);
        v.pMem = nullptr;
        v.sz = 0;
        return *this;
    }

    size_t size() const noexcept
    {
        return sz; 
    }

    // индексация
    T& operator[](size_t ind)
    {
        return pMem[ind];
    }
    const T& operator[](size_t ind) const
    {
        return pMem[ind];
    }
    // индексация с контролем
    T& at(size_t ind)
    {
        if (ind >= sz)
            throw out_of_range("Index is out of range");
        else
            return pMem[ind];
    }
    const T& at(size_t ind) const
    {
        if (ind >= sz)
            throw out_of_range("Index is out of range");
        else
            return pMem[ind];
    }

    // сравнение
    bool operator==(const TDynamicVector& v) const noexcept
    {
        if (sz != v.sz)
            return false;
        for (size_t i = 0; i < sz; ++i)
        {
            if (pMem[i] != v.pMem[i])
            {
                return false;
            }
        }
        return true;
    }
    bool operator!=(const TDynamicVector& v) const noexcept
    {
        return !(operator==(v));
    }

    // скалярные операции
    TDynamicVector operator+(T val)
    {
        TDynamicVector<T> result(*this);
        for (size_t i = 0; i < sz; ++i)
            result[i] = result[i] + val;
        return result;
    }
    TDynamicVector& operator+=(T val) // added
    {
        for (size_t i = 0; i < sz; ++i)
        {
            pMem[i] = pMem[i] + val;
        }
        return *this;
    }
    TDynamicVector operator-(T val)
    {
        TDynamicVector<T> result(*this);
        for (size_t i = 0; i < sz; ++i)
            result[i] = result[i] - val;
        return result;
    }
    TDynamicVector& operator-=(T val) // added
    {
        for (size_t i = 0; i < sz; ++i)
        {
            pMem[i] = pMem[i] - val;
        }
        return *this;
    }
    TDynamicVector operator*(T val)
    {
        TDynamicVector<T> result(*this);
        for (size_t i = 0; i < sz; ++i)
            result[i] = result[i] * val;
        return result;
    }
    TDynamicVector& operator*=(T val) // added
    {
        for (size_t i = 0; i < sz; ++i)
        {
            pMem[i] = pMem[i] * val;
        }
        return *this;
    }

    // векторные операции
    TDynamicVector operator+(const TDynamicVector& v)
    {   
        if (sz != v.sz)
            throw "Different sizes";
        TDynamicVector<T> result(*this);
        for (size_t i = 0; i < sz; ++i)
            result[i] = result[i] + v[i];
        return result;
    }
    TDynamicVector& operator+=(const TDynamicVector& v) // added
    {
        if (sz != v.sz)
            throw "Different sizes";
        for (size_t i = 0; i < sz; ++i)
            pMem[i] = pMem[i] + v[i];
        return *this;
    }
    TDynamicVector operator-(const TDynamicVector& v)
    {
        if (sz != v.sz)
            throw "Different sizes";
        TDynamicVector<T> result(*this);
        for (size_t i = 0; i < sz; ++i)
            result[i] = result[i] - v[i];
        return result;
    }
    TDynamicVector& operator-=(const TDynamicVector& v) // added
    {
        if (sz != v.sz)
            throw "Different sizes";
        for (size_t i = 0; i < sz; ++i)
            pMem[i] = pMem[i] - v[i];
        return *this;
    }
    T operator*(const TDynamicVector& v) noexcept(noexcept(T()))
    {
        if (sz != v.sz)
            throw "Different sizes";
        T result = 0;
        for (size_t i = 0; i < sz; ++i)
            result = result + pMem[i] * v.pMem[i];
        return result;
    }

    friend void swap(TDynamicVector& lhs, TDynamicVector& rhs) noexcept
    {
        std::swap(lhs.sz, rhs.sz);
        std::swap(lhs.pMem, rhs.pMem);
    }

    // ввод/вывод
    friend istream& operator>>(istream& istr, TDynamicVector& v)
    {
        for (size_t i = 0; i < v.sz; i++)
        istr >> v.pMem[i]; // требуется оператор>> для типа T
        return istr;
    }
    friend ostream& operator<<(ostream& ostr, const TDynamicVector& v)
    {
        for (size_t i = 0; i < v.sz; i++)
        ostr << v.pMem[i] << ' '; // требуется оператор<< для типа T
        return ostr;
    }
};


// Динамическая матрица - 
// шаблонная матрица на динамической памяти
template<typename T>
class TDynamicMatrix : private TDynamicVector<TDynamicVector<T>>
{
    using TDynamicVector<TDynamicVector<T>>::pMem;
    using TDynamicVector<TDynamicVector<T>>::sz;
public:
    TDynamicMatrix(size_t s = 1) : TDynamicVector<TDynamicVector<T>>(s)
    {   
        if (s > MAX_MATRIX_SIZE)
            throw out_of_range("Matrix size must be between 1 and 10000");
        for (size_t i = 0; i < sz; ++i)
            pMem[i] = TDynamicVector<T>(sz);
    }
    
    using TDynamicVector<TDynamicVector<T>>::operator[];

    // сравнение
    bool operator==(const TDynamicMatrix& m) const noexcept
    {
        for (size_t i = 0; i < sz; ++i)
        {
            if (pMem[i] != m.pMem[i])
                return false;
        }
        return true;
    }

    // матрично-скалярные операции
    TDynamicMatrix operator*(const T& val)
    {
    }

    // матрично-векторные операции
    TDynamicVector<T> operator*(const TDynamicVector<T>& v)
    {
    }

    // матрично-матричные операции
    TDynamicMatrix operator+(const TDynamicMatrix& m)
    {
    }
    TDynamicMatrix operator-(const TDynamicMatrix& m)
    {
    }
    TDynamicMatrix operator*(const TDynamicMatrix& m)
    {
    }

    // ввод/вывод
    friend istream& operator>>(istream& istr, TDynamicMatrix& v)
    {
    }
    friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& v)
    {
    }
};

#endif
