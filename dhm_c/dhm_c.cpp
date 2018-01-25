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
  const fpxx lambda = (fpxx)650e-9;                // Wavelength of light(peak....as its an LED!!)
  //const uint32_t N = 2048;
  const uint32_t N = 16;
  Number::ComplexArray<fpxx> m(N, N);
  Number::ComplexArray<fpxx> n(m);
  Number::ComplexArray<fpxx> tempa(m);

  Number::ComplexArray<fpxx> &expTotal = n;
  Number::ComplexArray<fpxx> &tempb = m;
  Number::ComplexArray<fpxx> &impAmpl = tempa;  
  Number::ComplexArray<fpxx> &expSide = expTotal;
  Number::ComplexArray<fpxx> &g = expTotal;
  Number::ComplexArray<fpxx> &g_scale = m;
  Number::ComplexArray<fpxx> &G = g;
  Number::Complex<fpxx> a((fpxx)0.0, (fpxx)1.0);
  Number::Complex<fpxx> a_scale((fpxx)1.0 / lambda, (fpxx)0.0);
  Number::Complex<fpxx> expConst((fpxx)0.0, -2.0*M_PI / lambda);

  fpxx start_lin = -((double)N) / 2.0;
  start_lin *= dx;
  m.linear_x(start_lin, dx);
  n.linear_y(start_lin, dy);
  
  n *= n;
  m *= m;
  m += (d*d);
  m += n;

  tempb = m.sqrt();
  tempa = a;
  tempa /= tempb;

  expTotal = tempb;
  expTotal *= expConst;
  expSide = expTotal.exp();
  g *= impAmpl;
  g_scale = g;
  g_scale *= a_scale;
  g.save("C:\\Movidius\\IntelLabs\\Code\\c\\g_in.dat");
  //g = Number::Complex<fpxx>(1.0, 1.0);
  //g.element(1, 1) = Number::Complex<fpxx>(0.5, 0.1);;
  g.fft();
  g.save("C:\\Movidius\\IntelLabs\\Code\\c\\G_fft.dat");
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

   /* impAmpl = tempa. / tempb;                 %JW
    expConst = -1i * 2 * pi / lambda;             %JW
    expTotal = expConst.*tempb;             %JW
    expSide = exp(expTotal);                %JW
    g = impAmpl.*expSide;                     %JW*/

  return 0;
}

