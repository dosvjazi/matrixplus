#pragma once

#include <cmath>
#include <iostream>
#include <utility>

class S21Matrix {
 public:
  S21Matrix() noexcept;
  S21Matrix(int rows, int cols);
  S21Matrix(const S21Matrix& other);
  S21Matrix(S21Matrix&& other) noexcept;
  ~S21Matrix();

  int GetRows() const noexcept;
  int GetCols() const noexcept;
  void SetRows(int rows);
  void SetCols(int cols);

  bool EqMatrix(const S21Matrix& other) const noexcept;
  void SumMatrix(const S21Matrix& other);
  void SubMatrix(const S21Matrix& other);
  void MulNumber(const double num) noexcept;
  void MulMatrix(const S21Matrix& other);
  S21Matrix CalcComplements() const;
  S21Matrix Transpose() const;
  double Determinant() const;
  S21Matrix InverseMatrix() const;

  S21Matrix operator+(const S21Matrix& other);
  S21Matrix operator-(const S21Matrix& other);
  S21Matrix operator*(const S21Matrix& other);
  S21Matrix operator*(const double mul);
  bool operator==(const S21Matrix& other) const noexcept;
  S21Matrix& operator=(S21Matrix&& other);
  S21Matrix operator+=(const S21Matrix& other);
  S21Matrix operator-=(const S21Matrix& other);
  S21Matrix operator*=(const S21Matrix& other);
  S21Matrix operator*=(const double mul);
  double& operator()(int row, int col) const;

 private:
  int rows_, cols_;
  double** matrix_;

  void ConstructMatrix();
  void CopyMatrix(const S21Matrix& other);
  void DestructMatrix() noexcept;
  void FillMatrix(S21Matrix& new_matrix, int rows, int cols);
  void CheckIfMatricesSizesAreEqual(const S21Matrix& other) const;
  void CheckIfMatrixIsSquare() const;
  void ComplementsHandle(S21Matrix& complements) const;
  void FindMinor(S21Matrix& minor, int row, int col) const noexcept;
  double DeterminantHandle() const;
  void CheckIfIndexIsOutOfBounds(int row, int col) const;
};