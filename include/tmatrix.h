// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
//

#ifndef __TDynamicMatrix_H__
#define __TDynamicMatrix_H__

#include <iostream>

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
		if (sz > MAX_VECTOR_SIZE)
		{
			throw out_of_range("The vector size is too long");
		}
		if (sz == 0)// Проверять случай sz < 0 не нужно т.к. sz иммеет тип size_t 
			throw out_of_range("Vector size should be greater than zero");
		pMem = new T[sz]();// {}; // У типа T д.б. констуктор по умолчанию
	}
	TDynamicVector(T* arr, size_t s) : sz(s)
	{
		if (sz > MAX_VECTOR_SIZE)
			throw out_of_range("The vector size is too long");
		assert(arr != nullptr && "TDynamicVector ctor requires non-nullptr arg");
		pMem = new T[sz];
		std::copy(arr, arr + sz, pMem);
	}
	TDynamicVector(const TDynamicVector& v)
	{
		sz = v.sz;
		pMem = new T[sz];
		std::copy(v.pMem, v.pMem + sz, pMem);
	}
	TDynamicVector(TDynamicVector&& v) noexcept
	{
		pMem = nullptr;
		swap(*this, v);
	}
	~TDynamicVector()
	{
		delete[] pMem;
	}
	TDynamicVector& operator=(const TDynamicVector& v)
	{
		if (this == &v)
			return *this;
		TDynamicVector tmp(v);
		swap(*this, tmp);
		return *this;


	}
	TDynamicVector& operator=(TDynamicVector&& v) noexcept
	{
		if (pMem != nullptr)
		{
			delete[] pMem;
			pMem = nullptr;
		}
		swap(*this, v);
		return *this;
	}

	size_t size() const noexcept { return sz; }

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
		if (ind >= sz || ind < 0)
			throw out_of_range("Bad index");
		return pMem[ind];
	}
	const T& at(size_t ind) const
	{
		if (ind >= sz || ind < 0)
			throw out_of_range("Bad index");
		return pMem[ind];
	}

	// сравнение
	bool operator==(const TDynamicVector& v) const noexcept
	{
		if (sz != v.sz)
			return false;
		for (size_t i = 0; i < sz; i++)
		{
			if (pMem[i] != v.pMem[i])
				return false;
		}
		return true;
	}
	bool operator!=(const TDynamicVector& v) const noexcept
	{
		return !(*this == v);
	}

	// скалярные операции
	TDynamicVector operator+(T val)
	{
		TDynamicVector tmp(sz);
		for (size_t i = 0; i < sz; i++)
		{
			tmp.pMem[i] = pMem[i] + val;
		}
		return tmp;
	}
	TDynamicVector operator-(double val)
	{
		TDynamicVector tmp(sz);
		for (size_t i = 0; i < sz; i++)
		{
			tmp.pMem[i] = pMem[i] - val;
		}
		return tmp;
	}
	TDynamicVector operator*(double val)
	{
		TDynamicVector tmp(sz);
		for (size_t i = 0; i < sz; i++)
		{
			tmp.pMem[i] = pMem[i] * val;
		}
		return tmp;
	}

	// векторные операции
	TDynamicVector operator+(const TDynamicVector& v)
	{
		if (sz != v.sz)
			throw out_of_range("differet sizes of vectors");
		TDynamicVector tmp(sz);
		for (size_t i = 0; i < sz; i++)
		{
			tmp.pMem[i] = pMem[i] + v.pMem[i];
		}
		return tmp;
	}
	TDynamicVector operator-(const TDynamicVector& v)
	{
		if (sz != v.sz)
			throw out_of_range("differet sizes of vectors");
		TDynamicVector tmp(sz);
		for (size_t i = 0; i < sz; i++)
		{
			tmp.pMem[i] = pMem[i] - v.pMem[i];
		}
		return tmp;
	}
	T operator*(const TDynamicVector& v)
	{
		if (sz != v.sz)
			throw out_of_range("differet sizes of vectors");
		T result = {};
		for (size_t i = 0; i < sz; i++)
		{
			result += pMem[i] * v.pMem[i];
		}
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
		if (sz > MAX_MATRIX_SIZE)
		{
			throw out_of_range("The vector size is too long");
		}
		for (size_t i = 0; i < sz; i++)
			pMem[i] = TDynamicVector<T>(sz);
	}
	size_t size() const noexcept { return sz; }
	using TDynamicVector<TDynamicVector<T>>::operator[];

	// сравнение
	bool operator==(const TDynamicMatrix& m) const noexcept
	{
		return TDynamicVector<TDynamicVector<T>>::operator==(m);
	}

	// матрично-скалярные операции
	TDynamicMatrix operator*(const T& val)
	{
		TDynamicMatrix tmp(sz);
		for (size_t i = 0; i < sz; i++)
		{
			tmp.pMem[i] = pMem[i] * val;
		}
		return tmp;
	}

	// матрично-векторные операции
	TDynamicVector<T> operator*(const TDynamicVector<T>& v)
	{
		TDynamicVector<T> tmp(sz);
		for (size_t i = 0; i < sz; i++)
		{
			tmp[i] = pMem[i] * v;
		}
		return tmp;
	}

	// матрично-матричные операции
	TDynamicMatrix operator+(const TDynamicMatrix& m)
	{
		TDynamicMatrix tmp(sz);
		for (size_t i = 0; i < sz; i++)
		{
			tmp.pMem[i] = pMem[i] + m.pMem[i];
		}
		return tmp;
	}
	TDynamicMatrix operator-(const TDynamicMatrix& m)
	{
		TDynamicMatrix tmp(sz);
		for (size_t i = 0; i < sz; i++)
		{
			tmp.pMem[i] = pMem[i] - m.pMem[i];
		}
		return tmp;
	}
	TDynamicMatrix operator*(const TDynamicMatrix& m)
	{
		if (m.size() == size())
		{
			TDynamicMatrix tmp(sz);
			for (size_t i = 0; i < sz; i++)
				for (size_t j = 0; j < sz; j++)
					for (size_t k = 0; k < sz; k++)
						tmp[i][j] += pMem[i][k] * m[k][j];
			return tmp;
		}
		else
			throw exception("bad size");
	}

	// ввод/вывод
	friend istream& operator>>(istream& istr, TDynamicMatrix& v)
	{
		for (size_t i = 0; i < v.sz; i++)
			for (size_t j = 0; j < v.sz; j++)
				istr >> v.pMem[i][j];
		return istr;
	}
	friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& v)
	{
		ostr << "\n";
		for (size_t i = 0; i < v.sz; i++)
		{
			for (size_t j = 0; j < v.sz; j++)
				ostr << v.pMem[i][j] << " ";
			ostr << "\n";
		}
		return ostr;
	}

	T& at(size_t ind1, size_t ind2)              // для теста throws_when_set_element_with_negative_index нужна индексация с контролем,
	{											 // которая без перегрузки не вызывается ([] предпологает отсутсвие проверки)					
		if (ind1 >= sz || ind1 < 0 || ind2 >= sz || ind2 < 0)
			throw out_of_range("Bad index");
		return pMem[ind1][ind2];
	}
	const T& at(size_t ind1, size_t ind2) const
	{
		if (ind1 >= sz || ind1 < 0 || ind2 >= sz || ind2 < 0)
			throw out_of_range("Bad index");
		return pMem[ind1][ind2];
	}
};

#endif
