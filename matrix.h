#pragma once
#include "stdlib.h"
#include <iostream>
#include <complex>
#include <iterator>
#include <vector>
using namespace std;

template <class T>
class matrix
{
private:
	vector<T> arr;
	unsigned size1;
	unsigned size2;
public:
	struct Iterator
	{
		Iterator(T* ptr) : m_ptr(ptr) {}
		T& operator*() const { return *m_ptr; }
		T* operator->() { return m_ptr; }
		Iterator& operator++() 
		{ 
			m_ptr++;
			return *this;
		}
		Iterator operator++(int) { Iterator tmp = *this; ++(*this); return tmp; }
		friend bool operator== (const Iterator& a, const Iterator& b) { return a.m_ptr == b.m_ptr; };
		friend bool operator!= (const Iterator& a, const Iterator& b) { return a.m_ptr != b.m_ptr; };
	private:
		T* m_ptr;
	};

	Iterator begin() { return Iterator(&arr[0]); }
	Iterator end() { return Iterator(&arr[0]+size1*size2); } 

	matrix(const unsigned size1 = 2, const unsigned size2 = 2, const T value = 0) : arr(vector<T>(size1*size2, value)), size1(size1), size2(size2) {}

	const unsigned GetSize1() const { return size1; }
	const unsigned GetSize2() const { return size2; }

	T& operator()(const unsigned x, const unsigned y)
	{
		if ((x >= this->GetSize1()) || (x < 0)) { throw"Invalid Index"; }
		if ((y >= this->GetSize2()) || (y < 0)) { throw"Invelid Index"; }
		return arr.at(x*size2 + y);
	}

	matrix operator+(matrix& m2)
	{
		if ((this->GetSize1() != m2.GetSize2()) || (this->GetSize2() != m2.GetSize2())) { throw"Different sizes;"; }
		matrix res(this->GetSize1(), this->GetSize2(), 0);
		for (unsigned i = 0; i < this->GetSize1(); i++)
		{
			for (unsigned j = 0; j < this->GetSize2(); j++)
			{
				res(i, j) = (*this)(i, j) + m2(i, j);
			}
		}
		return res;
	}

	matrix operator-(matrix& m2)
	{
		if ((this->GetSize1() != m2.GetSize1()) || (this->GetSize2() != m2.GetSize2())) { throw"Different sizes;"; }
		matrix res(this->GetSize1(), this->GetSize2(), 0);
		for (unsigned i = 0; i < res.GetSize1(); i++)
		{
			for (unsigned j = 0; j < res.GetSize2(); j++)
			{
				res(i, j) = (*this)(i, j) - m2(i, j);
			}
		}
		return res;
	}

	matrix operator*(matrix& m2)
	{
		if (this->GetSize2() != m2.GetSize1()) { throw"Multiplication is impossible"; }
		matrix res(this->GetSize1(), m2.GetSize2());
		for (unsigned i = 0; i < res.GetSize1(); i++)
		{
			for (unsigned j = 0; j < res.GetSize2(); j++)
			{
				res(i, j) = 0;
				for (unsigned k = 0; k < this->GetSize2(); k++)
					res(i, j) += (*this)(i, k) * m2(k, j);
			}
		}
		return res;
	}

	matrix operator/(T v)
	{
		if (abs(v) == 0) { throw"Division by zero"; }
		matrix res(this->GetSize1(), this->GetSize2());
		for (unsigned i = 0; i < this->GetSize1(); i++)
		{
			for (unsigned j = 0; j < this->GetSize2(); j++)
			{
				res(i, j) = (*this)(i, j) / v;
			}
		}
		return res;
	}

	T Trace()
	{
		if (this->GetSize1() != this->GetSize2()) { throw "It is not a square matrix"; }
		T res = 0;
		for (unsigned i = 0; i < this->GetSize1(); i++)
		{
			for (unsigned j = 0; j < this->GetSize2(); j++)
			{
				if (i == j) { res += (*this)(i, j); }
			}
		}
		return res;
	}

	friend ostream& operator<<(ostream& out, matrix& m1)
	{
		for (unsigned i = 0; i < m1.GetSize1(); i++)
		{
			for (unsigned j = 0; j < m1.GetSize2(); j++)
			{
				out << m1(i, j);
				out << '\t';
			}
			out << '\n';
		}
		return out;
	}

	friend matrix operator*(matrix& m1, const T value)
	{
		matrix res(m1.GetSize1(), m1.GetSize2());
		for (unsigned i = 0; i < res.GetSize1(); i++)
		{
			for (unsigned j = 0; j < res.GetSize2(); j++)
			{
				res(i, j) = m1(i, j) * value;
			}
		}
		return res;
	}

	friend matrix operator*(const T value, matrix& m1)
	{
		return m1 * value;
	}

	friend bool operator==(matrix& m1, matrix& m2)
	{
		if ((m1.GetSize1() != m2.GetSize1()) || (m1.GetSize2() != m2.GetSize2())) { return false; }
		for (unsigned i = 0; i < m1.GetSize1(); i++)
		{
			for (unsigned j = 0; j < m1.GetSize2(); j++)
			{
				if (abs(m1(i, j) != m2(i, j))) { return false; }
			}
		}
		return true;
	}

	friend bool operator!=(matrix& m1, matrix& m2)
	{
		return !(operator==(m1, m2));
	}
};

