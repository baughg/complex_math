// dhm_c.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "complex.h"

int main()
{
  Number::Complex<double> a(2.0, 4.0);
  Number::Complex<double> b(5.0,-7.0);
  Number::Complex<double> c;

  c = a;
  c /= b; 
  return 0;
}

