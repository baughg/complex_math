#ifndef COMPLEX_ARRAY_H
#define COMPLEX_ARRAY_H
#include "complex.h"
#include <vector>
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
    ComplexArray& operator=(const Complex<T> &rhs);    
    ComplexArray& operator=(const T &rhs);
    ComplexArray& operator*=(const ComplexArray &rhs);
    ComplexArray& operator/=(const ComplexArray &rhs);
    ComplexArray& operator+=(const ComplexArray &rhs);
    ComplexArray& operator=(const ComplexArray &rhs);
    ComplexArray& operator+=(const T &rhs);
    ComplexArray& sqrt();
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