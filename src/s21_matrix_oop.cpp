#include "s21_matrix_oop.h"

S21Matrix::S21Matrix() noexcept : rows_{3}, cols_{3}, matrix_{} {
  ConstructMatrix();
}

S21Matrix::S21Matrix(int rows, int cols) {
  if (rows < 1 || cols < 1) {
    throw std::invalid_argument("Rows and/or columns must be at least 1");
  }
  rows_ = rows;
  cols_ = cols;
  ConstructMatrix();
}

void S21Matrix::ConstructMatrix() {
  matrix_ = new double *[rows_];
  for (int i = 0; i < rows_; i++) {
    matrix_[i] = new double[cols_];
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = 0;
    }
  }
}

void S21Matrix::DestructMatrix() noexcept {
  for (int i = 0; i < rows_; i++) {
    delete[] matrix_[i];
  }
  delete[] matrix_;
  matrix_ = {};
  rows_ = {};
  cols_ = {};
}

S21Matrix::S21Matrix(const S21Matrix &other)
    : rows_(other.rows_), cols_(other.cols_) {
  if (&other == this) {
    throw std::logic_error("Self-copying is not allowed");
  }
  CopyMatrix(other);
}

void S21Matrix::CopyMatrix(const S21Matrix &other) {
  ConstructMatrix();
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = other(i, j);
    }
  }
}

S21Matrix::S21Matrix(S21Matrix &&other) noexcept {
  if (this != &other) {
    rows_ = std::exchange(other.rows_, 0);
    cols_ = std::exchange(other.cols_, 0);
    matrix_ = std::exchange(other.matrix_, nullptr);
  }
}

S21Matrix::~S21Matrix() { DestructMatrix(); }

int S21Matrix::GetRows() const noexcept { return rows_; }

int S21Matrix::GetCols() const noexcept { return cols_; }

void S21Matrix::SetRows(int rows) {
  if (rows < 1) {
    throw std::invalid_argument("Rows must be at least 1");
  }
  S21Matrix new_matrix(rows, cols_);
  double edge = rows_;
  if (rows < rows_) edge = rows;
  FillMatrix(new_matrix, edge, cols_);
  *this = std::move(new_matrix);
}

void S21Matrix::SetCols(int cols) {
  if (cols < 1) {
    throw std::invalid_argument("Columns must be at least 1");
  }
  S21Matrix new_matrix(rows_, cols);
  double edge = cols_;
  if (cols < cols_) edge = cols;
  FillMatrix(new_matrix, rows_, edge);
  *this = std::move(new_matrix);
}

void S21Matrix::FillMatrix(S21Matrix &new_matrix, int rows, int cols) {
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      new_matrix(i, j) = matrix_[i][j];
    }
  }
}

bool S21Matrix::EqMatrix(const S21Matrix &other) const noexcept {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    return false;
  }
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      if (fabs(matrix_[i][j] - other(i, j)) >= 1e-07) {
        return false;
      }
    }
  }
  return true;
}

void S21Matrix::SumMatrix(const S21Matrix &other) {
  CheckIfMatricesSizesAreEqual(other);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] += other(i, j);
    }
  }
}

void S21Matrix::SubMatrix(const S21Matrix &other) {
  CheckIfMatricesSizesAreEqual(other);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] -= other(i, j);
    }
  }
}

void S21Matrix::CheckIfMatricesSizesAreEqual(const S21Matrix &other) const {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::invalid_argument(
        "The number of rows and/or columns is not equal");
  }
}

void S21Matrix::MulNumber(const double num) noexcept {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] *= num;
    }
  }
}

void S21Matrix::MulMatrix(const S21Matrix &other) {
  if (cols_ != other.rows_) {
    throw std::invalid_argument(
        "The number of columns in the first matrix does not equal the number "
        "of rows in the second");
  }
  S21Matrix res(rows_, other.cols_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < other.cols_; j++) {
      res(i, j) = 0;
      for (int k = 0; k < cols_; k++) {
        res(i, j) += matrix_[i][k] * other.matrix_[k][j];
      }
    }
  }
  *this = std::move(res);
}

S21Matrix S21Matrix::CalcComplements() const {
  CheckIfMatrixIsSquare();
  if (rows_ == 1) {
    throw std::logic_error(
        "It is not possible to calculate the complements for a matrix with a "
        "size less than 2");
  }
  S21Matrix result(rows_, cols_);
  ComplementsHandle(result);
  return result;
}

S21Matrix S21Matrix::Transpose() const {
  S21Matrix transposed(cols_, rows_);
  for (int i = 0; i < transposed.rows_; i++) {
    for (int j = 0; j < transposed.cols_; j++) {
      transposed(i, j) = matrix_[j][i];
    }
  }
  return transposed;
}

void S21Matrix::CheckIfMatrixIsSquare() const {
  if (rows_ != cols_) {
    throw std::logic_error("The matrix is not a square matrix");
  }
}

void S21Matrix::ComplementsHandle(S21Matrix &complements) const {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      S21Matrix minor(rows_ - 1, cols_ - 1);
      FindMinor(minor, i, j);
      complements(i, j) = pow(-1, (i + j)) * minor.Determinant();
      minor.DestructMatrix();
    }
  }
}

void S21Matrix::FindMinor(S21Matrix &minor, int row, int col) const noexcept {
  int row_counter = 0, col_counter = 0;
  for (int i = 0; i < rows_; i++) {
    if (i != row) {
      col_counter = 0;
      for (int j = 0; j < cols_; j++) {
        if (j != col) {
          minor.matrix_[row_counter][col_counter] = matrix_[i][j];
          col_counter++;
        }
      }
      row_counter++;
    }
  }
}

double S21Matrix::Determinant() const {
  CheckIfMatrixIsSquare();
  return DeterminantHandle();
}

double S21Matrix::DeterminantHandle() const {
  double total = 0;
  if (rows_ == 1) {
    total = matrix_[0][0];
  } else {
    for (int j = 0; j < cols_; j++) {
      S21Matrix minor(rows_ - 1, cols_ - 1);
      FindMinor(minor, 0, j);
      total += matrix_[0][j] * pow(-1, j) * minor.DeterminantHandle();
      minor.DestructMatrix();
    }
  }
  return total;
}

S21Matrix S21Matrix::InverseMatrix() const {
  const double determinant = Determinant();
  if (fabs(determinant) <= 1.0e-7) {
    throw std::logic_error("The determinant of a matrix cannot be 0");
  }
  S21Matrix inversed = CalcComplements();
  inversed = inversed.Transpose();
  inversed *= (1.0 / determinant);
  return inversed;
}

S21Matrix S21Matrix::operator+(const S21Matrix &other) {
  S21Matrix result(*this);
  result.SumMatrix(other);
  return result;
}

S21Matrix S21Matrix::operator-(const S21Matrix &other) {
  S21Matrix result(*this);
  result.SubMatrix(other);
  return result;
}

S21Matrix S21Matrix::operator*(const S21Matrix &other) {
  S21Matrix result(*this);
  result.MulMatrix(other);
  return result;
}

S21Matrix S21Matrix::operator*(const double mul) {
  S21Matrix result(*this);
  result.MulNumber(mul);
  return result;
}

bool S21Matrix::operator==(const S21Matrix &other) const noexcept {
  return EqMatrix(other);
}

S21Matrix &S21Matrix::operator=(S21Matrix &&other) {
  if (this == &other) {
    return *this;
  }
  DestructMatrix();
  rows_ = other.rows_;
  cols_ = other.cols_;
  CopyMatrix(other);
  return *this;
}

S21Matrix S21Matrix::operator+=(const S21Matrix &other) {
  SumMatrix(other);
  return *this;
}

S21Matrix S21Matrix::operator-=(const S21Matrix &other) {
  SubMatrix(other);
  return *this;
}

S21Matrix S21Matrix::operator*=(const S21Matrix &other) {
  MulMatrix(other);
  return *this;
}

S21Matrix S21Matrix::operator*=(const double mul) {
  MulNumber(mul);
  return *this;
}

double &S21Matrix::operator()(int row, int col) const {
  CheckIfIndexIsOutOfBounds(row, col);
  return matrix_[row][col];
}

void S21Matrix::CheckIfIndexIsOutOfBounds(int row, int col) const {
  if (row < 0 || col < 0 || row >= rows_ || col >= cols_) {
    throw std::out_of_range("Matrix index(es) are out of bounds");
  }
}