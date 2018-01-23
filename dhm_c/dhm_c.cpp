// dhm_c.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "complex.h"
#include "complex_array.h"

int main()
{
  Number::Complex<double> a(2.0, 4.0);
  Number::Complex<double> b(5.0,-7.0);
  Number::Complex<double> c;
  Number::Complex<double> d;

  d = a + b * a;
  c = a;
  c /= b;

  Number::ComplexArray<double> arr1;

  arr1 = d;
  return 0;
}

