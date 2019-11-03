#include <iostream>
#include <string>

template <typename T>
class Matrix {
public:
  int n, m;
  T** ar;

  Matrix(const int n, const int m);
  Matrix(const int n, const int m, const T x[]);
  Matrix(const int n, const int m, const Matrix<T> &x);
  void operator=(const Matrix<T> &x);

  T& at(const int i, const int j) { return ar[i][j]; }
  T* operator[](const int i) const {  return ar[i];  }
  // [i] -> ar[i]

  Matrix<T> operator+(const Matrix<T> &other) {
    Matrix<T> res = *this;
    for (int i = 0; i < this->n; ++i)
      for (int j = 0; j < this->m; ++j)
        res.ar[i][j] += other.ar[i][j];
    return res;
  }

  Matrix<T> operator-(const Matrix<T> &other) {
    Matrix<T> res = *this;
    for (int i = 0; i < this->n; ++i)
      for (int j = 0; j < this->m; ++j)
        res.ar[i][j] -= other.ar[i][j];
    return res;
  }

  Matrix<T> operator*(const T Scalar) {
    Matrix<T> res = *this;
    for (int i = 0; i < this->n; ++i)
      for (int j = 0; j < this->m; ++j)
        res.ar[i][j] *= Scalar;
    return res;
  }

  Matrix<T> operator*(const Matrix<T> &other) {
    Matrix<T> res(this->n, other.m);
    for (int i = 0; i < this->n; ++i) {
      for (int k = 0; k < this->m; ++k) {
        for (int j = 0; j < other.m; ++j) {
          res.ar[i][j] += this->ar[i][k] * other.ar[k][j];
        }
      }
    }
    return res;
  }

  static Matrix<T> eye(const int n);

  static Matrix<T> zero(const int n, const int m);

  static Matrix<T> ones(const int n, const int m);

  /*
  void output(std::string s) {
    std::cout << s << ":\n";
    for (int i = 0; i < this->n; ++i) {
      for (int j = 0; j < this->m; ++j)
        std::cout << this->ar[i][j] << " ";
      std::cout << "\n";
    }
  }
  */
};

template <typename T>
Matrix<T>::Matrix(const int n, const int m) {
  this->n = n;
  this->m = m;

  this->ar = new T*[n];
  for (int i = 0; i < n; ++i) {
    this->ar[i] = new T[m];
    for (int j = 0; j < m; ++j) {
      ar[i][j] = 0;
    }
  }
}

template <typename T>
Matrix<T>::Matrix(const int n, const int m, const T x[]) {
  this->n = n;
  this->m = m;

  this->ar = new T*[n];
  for (int i = 0; i < n; ++i)
    this->ar[i] = new T[m];

  for (int i = 0; i < n; ++i)
    for (int j = 0; j < m; ++j)
      this->ar[i][j] = x[i*m + j];
}

template <typename T>
Matrix<T>::Matrix(const int n, const int m, const Matrix<T> &x) {
  /*
  this->n = n;
  this->m = m;

  ar = new T*[n];
  for (int i = 0; i < n; ++i)
    ar[i] = new T[m];

  for (int i = 0; i < n; ++i)
    for (int j = 0; j < m; ++j)
      ar[i][j] = x.ar[i][j];
  */
  this->n = n;
  this->m = m;
  this->ar = x.ar;
}

template <typename T>
void Matrix<T>::operator=(const Matrix<T> &x) {
  this->n = x.n;
  this->m = x.m;
  this->ar = x.ar;
}

template <typename T>
Matrix<T> Matrix<T>::eye(const int n) {
  Matrix<T> res(n, n);
  for (int i = 0; i < n; ++i)
    res[i][i] = 1;
  return res;
}

template <typename T>
Matrix<T> Matrix<T>::zero(const int n, const int m) {
  Matrix<T> res(n, m);
  return res;
}

template <typename T>
Matrix<T> Matrix<T>::ones(const int n, const int m) {
  Matrix<T> res(n, m);
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < m; ++j)
      res[i][j] = 1;
  return res;
}

template <typename T>
std::ostream& operator<<(std::ostream &out, const Matrix<T> &X) {
  for (int i = 0; i < X.n; ++i) {
    for (int j = 0; j < X.m; ++j)
      out << X[i][j] << " ";
    out << "\n";
  }
  return out;
}

int main() {
  double values[] = {0, 1, 2, 3};
  Matrix<double> x(2, 2, values);
  std::cout << "original x\n" << x << "\n";

  Matrix<double> y(2, 2, x);
  std::cout << "original y\n" << y << "\n";

  y.at(0, 0) = 100;
  std::cout << "modified y\n" << y << "\n";

  x = y;
  std::cout << "original x\n" << x << "\n";

  Matrix<double> z = x + y;
  std::cout << "original z\n" << z << "\n";

  std::cout << "scaled z\n" << z * 3.0 << "\n";

  double Avals[] = {2, 4, 1, 3};
  Matrix<double> A(2, 2, Avals);
  std::cout << "A\n" << A << "\n";

  double Bvals[] = {0, 1, 1, 0};
  Matrix<double> B(2, 2, Bvals);
  std::cout << "B\n" << B << "\n";

  std::cout << "A*B\n" << A*B << "\n";


  std::cout << "eye\n" << Matrix<double>::eye(6) << "\n";

  std::cout << "zero\n" << Matrix<double>::zero(3, 2) << "\n";

  std::cout << "ones\n" << Matrix<double>::ones(2, 3) << "\n";

  std::cout << "bonus:\n";
  std::cout << A.ar[0][0]<<"\n";
  std::cout << A[0][0] << "\n";

  return 0;
}
