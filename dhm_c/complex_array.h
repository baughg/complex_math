#ifndef COMPLEX_ARRAY_H
#define COMPLEX_ARRAY_H
#include "complex.h"
#include <vector>
#include <string>
#include <stdint.h>

namespace Number {
  template<class T>
  class ComplexArray {
  public:
    ComplexArray();    
    ComplexArray(uint32_t m, uint32_t n);
    ComplexArray(ComplexArray<T> &init);
    ~ComplexArray();
    void set_mn(uint32_t m, uint32_t n);
    void save(const std::string &file_name);
    ComplexArray& operator=(const Complex<T> &rhs);    
    ComplexArray& operator=(const T &rhs);
    ComplexArray& operator*=(const ComplexArray &rhs);
    ComplexArray& operator*=(const Complex<T> &rhs);
    ComplexArray& operator/=(const ComplexArray &rhs);
    ComplexArray& operator+=(const ComplexArray &rhs);
    ComplexArray& operator=(const ComplexArray &rhs);
    ComplexArray& operator+=(const T &rhs);
    Complex<T> &element(const uint32_t m, const uint32_t n);
    ComplexArray& sqrt();
    ComplexArray& exp();
    ComplexArray& fft();
    void linear_x(
      const T &start,       
      const T &step);
    void linear_y(
      const T &start,
      const T &step);
  private:
    uint32_t M_;
    uint32_t N_;
    std::vector<Complex<T>> array_;
  };

  template<class T>
  ComplexArray<T>::ComplexArray()
  {
  }

  template<class T>
  ComplexArray<T>::ComplexArray(uint32_t m, uint32_t n)
    : M_(m),
      N_(n)
  {
    array_.resize(M_*N_);
  }

  template<class T>
  ComplexArray<T>::ComplexArray(ComplexArray<T> &init)
    : M_(init.M_),
    N_(init.N_)
  {
    array_.resize(M_*N_);
  }

  template<class T>
  ComplexArray<T>::~ComplexArray()
  {
  }

  template<class T>
  void ComplexArray<T>::set_mn(uint32_t m, uint32_t n)
  {
    M_ = m;
    N_ = n;
    array_.resize(M_*N_);
  }

  template<class T>
  Complex<T> &ComplexArray<T>::element(const uint32_t m, const uint32_t n)
  {
    static Complex<T> dummy;

    if (m >= M_ || n >= N_)
      return dummy;

    return array_[m*N_ + n];
  }

  template<class T>
  void ComplexArray<T>::save(const std::string &file_name)
  {
    FILE* array_file = nullptr;

    array_file = fopen(file_name.c_str(), "wb");
    const uint32_t cells = M_ * N_;

    T real, imag;

    if (array_file)
    {
      fwrite(&M_, sizeof(M_), 1, array_file);
      fwrite(&N_, sizeof(N_), 1, array_file);
      
      for (uint32_t c = 0; c < cells; ++c)
      {
        array_[c].get_components(real,imag);
        fwrite(&real, sizeof(real), 1, array_file);
        fwrite(&imag, sizeof(imag), 1, array_file);
      }

      fclose(array_file);
    }
  }

  template<class T>
  ComplexArray<T>& ComplexArray<T>::operator=(const Complex<T> &rhs)
  {
    const uint32_t cells = M_ * N_;

    for (uint32_t c = 0; c < cells; ++c)
    {
      array_[c] = rhs;
    }

    return *this;
  }

  template<class T>
  ComplexArray<T>& ComplexArray<T>::operator*=(const ComplexArray<T> &rhs)
  {
    const uint32_t cells = M_ * N_;

    for (uint32_t c = 0; c < cells; ++c)
    {
      array_[c] *= rhs.array_[c];
    }

    return *this;
  }

  template<class T>
  ComplexArray<T>& ComplexArray<T>::operator*=(const Complex<T> &rhs)
  {
    const uint32_t cells = M_ * N_;

    for (uint32_t c = 0; c < cells; ++c)
    {
      array_[c] *= rhs;
    }

    return *this;
  }

  template<class T>
  ComplexArray<T>& ComplexArray<T>::operator/=(const ComplexArray<T> &rhs)
  {
    const uint32_t cells = M_ * N_;

    for (uint32_t c = 0; c < cells; ++c)
    {
      array_[c] /= rhs.array_[c];
    }

    return *this;
  }

  template<class T>
  ComplexArray<T>& ComplexArray<T>::operator+=(const ComplexArray<T> &rhs)
  {
    const uint32_t cells = M_ * N_;

    for (uint32_t c = 0; c < cells; ++c)
    {
      array_[c] += rhs.array_[c];
    }

    return *this;
  }
  
  template<class T>
  ComplexArray<T>& ComplexArray<T>::sqrt()
  {
    const uint32_t cells = M_ * N_;

    for (uint32_t c = 0; c < cells; ++c)
    {
      array_[c].sqrt();
    }

    return *this;
  }

  template<class T>
  ComplexArray<T>& ComplexArray<T>::exp()
  {
    const uint32_t cells = M_ * N_;

    for (uint32_t c = 0; c < cells; ++c)
    {
      array_[c].exp();
    }

    return *this;
  }

  template<class T>
  ComplexArray<T>& ComplexArray<T>::fft()
  {
    const uint32_t cells = M_ * N_;
    
    T exponent = -(T)2.0 * (T)M_PI / (T)N_;
    T ept = exponent;
    uint32_t offset = 0;
    ComplexArray<T> result(*this);
    Complex<T> sum, prod;

    for (uint32_t y = 0; y < M_; ++y) {
      offset = y * N_;

      for (uint32_t k = 0; k < N_; ++k)
      {
        sum = (T)0.0;

        for (uint32_t n = 0; n < N_; ++n)
        {
          ept = exponent * (T)(n * k);
          Complex<T> twiddle((T)0.0, ept);
          twiddle.exp();
          prod = array_[n + offset];
          prod *= twiddle;
          sum += prod;
        }

        result.array_[k + offset] = sum;
      }
    }

    *this = result;
    exponent = -(T)2.0 * (T)M_PI / (T)M_;

    for (uint32_t x = 0; x < N_; ++x) {
      offset = x * N_;

      for (uint32_t k = 0; k < M_; ++k)
      {
        sum = (T)0.0;

        for (uint32_t n = 0; n < M_; ++n)
        {          
          ept = exponent * (T)(n * k);
          Complex<T> twiddle((T)0.0, ept);
          twiddle.exp();
          prod = array_[n*N_ + x];
          prod *= twiddle;
          sum += prod;
        }

        result.array_[k + offset] = sum;
      }
    }

    *this = result;
    return *this;
  }

  template<class T>
  ComplexArray<T>& ComplexArray<T>::operator=(const ComplexArray<T> &rhs)
  {
    M_ = rhs.M_;
    N_ = rhs.N_;
    
    if (this == &rhs)
      return *this;

    const uint32_t cells = M_ * N_;
    array_.resize(cells);

    for (uint32_t c = 0; c < cells; ++c)
    {
      array_[c] = rhs.array_[c];
    }

    return *this;
  }

  template<class T>
  void ComplexArray<T>::linear_x(
    const T &start,    
    const T &step)
  {
    uint32_t i = 0;
    T val = start;

    for (uint32_t y = 0; y < M_; ++y)
    {
      for (uint32_t x = 0; x < N_; ++x)
      {        
        array_[i++] = val;
        val += step;
      }

      val = start;
    }
  }

  template<class T>
  void ComplexArray<T>::linear_y(
    const T &start,
    const T &step)
  {
    uint32_t i = 0;
    T val = start;

    for (uint32_t y = 0; y < M_; ++y)
    {
      for (uint32_t x = 0; x < N_; ++x)
      {
        array_[i++] = val;
      }

      val += step;
    }
  }

  template<class T>
  ComplexArray<T>& ComplexArray<T>::operator+=(const T &rhs)
  {
    const uint32_t cells = M_ * N_;

    for (uint32_t c = 0; c < cells; ++c)
    {
      array_[c] += rhs;
    }

    return *this;
  }

  template<class T>
  ComplexArray<T>& ComplexArray<T>::operator=(const T &rhs)
  {
    const uint32_t cells = M_ * N_;

    for (uint32_t c = 0; c < cells; ++c)
    {
      array_[c] = rhs;
    }

    return *this;
  }
}
#endif