#ifndef COMPLEX_H
#define COMPLEX_H

#define M_PI   3.14159265358979323846264338327950288

namespace Number {
  template<class T>
  class Complex
  {
  public:
    Complex();
    Complex(Complex& init);
    Complex(T real, T imag);
    ~Complex();
    Complex operator+(const Complex &rhs);
    Complex operator-(const Complex &rhs);
    Complex operator/(const Complex &rhs);
    Complex operator*(const Complex &rhs);
    Complex& operator+=(const Complex &rhs);
    Complex& operator-=(const Complex &rhs);
    Complex& operator*=(const Complex &rhs);
    Complex& operator/=(const Complex &rhs);
    Complex& operator=(const Complex &rhs);
    Complex& operator=(const T &rhs);  
    Complex& operator+=(const T &rhs);
    Complex& operator*=(const T &rhs);
    void sqrt();
    void exp();
    void get_components(T &real, T &imag);
  private:
    T real_;
    T imag_;
  };

  template<class T>
  Complex<T>::Complex()
    : real_(0.0),
    imag_(0.0)
  {
  }

  template<class T>
  Complex<T>::Complex(Complex<T> &init)
    : real_(init.real_),
    imag_(init.imag_)
  {
  }

  template<class  T>
  Complex<T>::~Complex()
  {
  }

  template<class  T>
  Complex<T>::Complex(T real, T imag)
  {
    real_ = real;
    imag_ = imag;
  }

  template<class  T>
  Complex<T>& Complex<T>::operator=(const Complex<T> &rhs)
  {
    real_ = rhs.real_;
    imag_ = rhs.imag_;
    return *this;
  }

  template<class  T>
  Complex<T>& Complex<T>::operator=(const T &rhs)
  {
    real_ = rhs; 
    imag_ = (T)0.0;
    return *this;
  }

  template<class  T>
  void Complex<T>::sqrt()
  {
    real_ = std::sqrt(real_);
    imag_ = (T)0.0;
  }

  template<class  T>
  void Complex<T>::get_components(T &real, T &imag)
  {
    real = real_;
    imag = imag_;
  }

  template<class  T>
  void Complex<T>::exp()
  {
    T real_scale = std::exp(real_);
    real_ = cos(imag_) * real_scale;
    imag_ = sin(imag_) * real_scale;
  }

  template<class  T>
  Complex<T>& Complex<T>::operator+=(const Complex<T> &rhs)
  {
    real_ += rhs.real_;
    imag_ += rhs.imag_;
    return *this;
  }

  template<class  T>
  Complex<T>& Complex<T>::operator+=(const T &rhs)
  {
    real_ += rhs;  
    return *this;
  }

  template<class  T>
  Complex<T>& Complex<T>::operator*=(const T &rhs)
  {
    real_ *= rhs;
    imag_ *= rhs;
    return *this;
  }

  template<class  T>
  Complex<T> Complex<T>::operator+(const Complex<T> &rhs)
  {
    Complex sum;
    sum.real_ = real_ + rhs.real_;
    sum.imag_ = imag_ + rhs.imag_;
    return sum;
  }

  template<class  T>
  Complex<T> Complex<T>::operator-(const Complex<T> &rhs)
  {
    Complex sum;
    sum.real_ = real_ - rhs.real_;
    sum.imag_ = imag_ - rhs.imag_;
    return sum;
  }

  template<class  T>
  Complex<T> Complex<T>::operator*(const Complex<T> &rhs)
  {
    Complex sum(*this);
    sum *= rhs; 
    return sum;
  }

  template<class  T>
  Complex<T> Complex<T>::operator/(const Complex<T> &rhs)
  {
    Complex sum(*this);
    sum /= rhs;
    return sum;
  }

  template<class  T>
  Complex<T>& Complex<T>::operator*=(const Complex<T> &rhs)
  {
    T real, imag;
    real = real_ * rhs.real_ - imag_ * rhs.imag_;
    imag = real_ * rhs.imag_ + rhs.real_ * imag_;
    real_ = real;
    imag_ = imag;
    return *this;
  }

  template<class  T>
  Complex<T>& Complex<T>::operator/=(const Complex<T> &rhs)
  {
    T real, imag, scale;
    scale = 1.0 / (rhs.real_ * rhs.real_ + rhs.imag_ * rhs.imag_);
    real = real_ * rhs.real_ + imag_ * rhs.imag_;
    imag = rhs.real_ * imag_ - real_ * rhs.imag_;
    real_ = real * scale;
    imag_ = imag * scale;
    return *this;
  }

  template<class  T>
  Complex<T>& Complex<T>::operator-=(const Complex<T> &rhs)
  {
    real_ -= rhs.real_;
    imag_ -= rhs.imag_;
    return *this;
  }
}
#endif

