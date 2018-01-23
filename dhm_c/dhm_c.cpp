// dhm_c.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "complex.h"
#include "complex_array.h"

int main()
{
  typedef double fpxx;


  const fpxx dx = (fpxx)8e-6;          // active pixel spacing
  const fpxx dy = (fpxx)8e-6;          // active pixel spacing
  const fpxx d = (fpxx)0.15;
  const uint32_t N = 2048;
  Number::ComplexArray<fpxx> m(N, N);
  Number::ComplexArray<fpxx> n(m);
  Number::ComplexArray<fpxx> &tempb = m;

  fpxx start_lin = -((double)N) / 2.0;
  start_lin *= dx;
  m.linear_x(start_lin, dx);
  n.linear_y(start_lin, dy);
  
  n *= n;
  m *= m;
  m += (d*d);
  m += n;

  tempb = m.sqrt();
  
  /*dx = 8e-6;          %active pixel spacing
    dy = 8e-6;          %active pixel spacing
    M = 2 ^ ceil(log2(size(imge, 1)));
  N = 2 ^ ceil(log2(size(imge, 2)));

  [Mi, Ni] = size(imge);
  hol = zeros(M, N);
  hol(M / 2 - Mi / 2 + 1:M / 2 + Mi / 2, N / 2 - Ni / 2 + 1 : N / 2 + Ni / 2) = double(imge);
  [m, n] = meshgrid(-M / 2:M / 2 - 1, -N / 2 : N / 2 - 1);

  %--------------------------------------------------------------------------
    %-- - Impulse response - g calcuated, Then take FFT(g)
    % --------------------------------------------------------------------------

    tempa = i / lambda;

  tempb = sqrt(d ^ 2 + (m.*dx). ^ 2 + (n.*dy). ^ 2);*/

  return 0;
}

