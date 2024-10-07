#include "s21_matrix_oop.h"

#include <gtest/gtest.h>

void FillMatrix(S21Matrix &matrix, double *array, int rows, int cols) {
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      matrix(i, j) = array[i * cols + j];
    }
  }
}

TEST(CreateMatrix, Basic) {
  S21Matrix matrix;
  EXPECT_EQ(matrix.GetRows(), 3);
  EXPECT_EQ(matrix.GetCols(), 3);
}

TEST(CreateMatrix, Params) {
  S21Matrix matrix(1, 1);
  EXPECT_EQ(matrix.GetRows(), 1);
  EXPECT_EQ(matrix.GetCols(), 1);
}

TEST(CreateMatrix, InvalidArgument) {
  EXPECT_THROW(S21Matrix matrix(0, -1), std::invalid_argument);
}

TEST(CreateMatrix, Copy) {
  S21Matrix matrix;
  S21Matrix matrix_copy(matrix);
  EXPECT_EQ(matrix_copy.GetRows(), 3);
  EXPECT_EQ(matrix_copy.GetCols(), 3);
}

TEST(CreateMatrix, Move) {
  S21Matrix matrix;
  S21Matrix mtrx_move(std::move(matrix));
  EXPECT_EQ(mtrx_move.GetRows(), 3);
  EXPECT_EQ(mtrx_move.GetCols(), 3);
}

TEST(EqualMatrix, Eq) {
  S21Matrix matrix;
  S21Matrix other;
  double array[9] = {1, 1, 1, 1, 1, 1, 1, 1, 1};
  FillMatrix(matrix, array, 3, 3);
  FillMatrix(other, array, 3, 3);
  EXPECT_EQ(matrix.EqMatrix(other), true);
}

TEST(EqualMatrix, NotEqulMatrix) {
  S21Matrix matrix;
  S21Matrix other;
  double array[9] = {1, 1, 1, 1, 1, 1, 1, 1, 1};
  double array_other[9] = {2, 2, 2, 2, 2, 2, 2, 2, 2};
  FillMatrix(matrix, array, 3, 3);
  FillMatrix(other, array_other, 3, 3);
  EXPECT_EQ(matrix.EqMatrix(other), false);
}

TEST(EqualMatrix, WrongSize) {
  S21Matrix matrix;
  S21Matrix other(3, 2);
  double array[9] = {1, 1, 1, 1, 1, 1, 1, 1, 1};
  double array_other[6] = {2, 2, 2, 2, 2, 2};
  FillMatrix(matrix, array, 3, 3);
  FillMatrix(other, array_other, 3, 2);
  EXPECT_EQ(matrix.EqMatrix(other), false);
}

TEST(SumMatrix, Sum) {
  S21Matrix matrix;
  S21Matrix other;
  S21Matrix matrix_check(3, 3);
  double array[9] = {1, 1, 1, 1, 1, 1, 1, 1, 1};
  double array_check[9] = {2, 2, 2, 2, 2, 2, 2, 2, 2};
  FillMatrix(matrix, array, 3, 3);
  FillMatrix(other, array, 3, 3);
  FillMatrix(matrix_check, array_check, 3, 3);
  matrix.SumMatrix(other);
  EXPECT_EQ(matrix.EqMatrix(matrix_check), true);
}

TEST(SumMatrix, OperationSum) {
  S21Matrix matrix;
  S21Matrix other;
  S21Matrix matrix_check(3, 3);
  S21Matrix matrix_result(3, 3);
  double array[9] = {1, 1, 1, 1, 1, 1, 1, 1, 1};
  double array_check[9] = {2, 2, 2, 2, 2, 2, 2, 2, 2};
  FillMatrix(matrix, array, 3, 3);
  FillMatrix(other, array, 3, 3);
  FillMatrix(matrix_check, array_check, 3, 3);
  matrix_result = matrix + other;
  EXPECT_EQ(matrix_result.EqMatrix(matrix_check), true);
}

TEST(SumMatrix, OutOfRangeException) {
  S21Matrix matrix;
  S21Matrix other(3, 2);
  double array[9] = {1, 1, 1, 1, 1, 1, 1, 1, 1};
  double array_other[6] = {2, 2, 2, 2, 2, 2};
  FillMatrix(matrix, array, 3, 3);
  FillMatrix(other, array_other, 3, 2);
  EXPECT_THROW(matrix.SumMatrix(other), std::invalid_argument);
}

TEST(SumMatrix, OperationSumPr) {
  S21Matrix matrix;
  S21Matrix other;
  S21Matrix matrix_check(3, 3);
  double array[9] = {1, 1, 1, 1, 1, 1, 1, 1, 1};
  double array_check[9] = {2, 2, 2, 2, 2, 2, 2, 2, 2};
  FillMatrix(matrix, array, 3, 3);
  FillMatrix(other, array, 3, 3);
  FillMatrix(matrix_check, array_check, 3, 3);
  matrix += other;
  EXPECT_EQ(matrix.EqMatrix(matrix_check), true);
}

TEST(SubMatrix, Sub) {
  S21Matrix matrix;
  S21Matrix other;
  S21Matrix matrix_check(3, 3);
  double array[9] = {1, 1, 1, 1, 1, 1, 1, 1, 1};
  double array_check[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
  FillMatrix(matrix, array, 3, 3);
  FillMatrix(other, array, 3, 3);
  FillMatrix(matrix_check, array_check, 3, 3);
  matrix.SubMatrix(other);
  EXPECT_EQ(matrix.EqMatrix(matrix_check), true);
}

TEST(SubMatrix, OperationSub) {
  S21Matrix matrix;
  S21Matrix other;
  S21Matrix matrix_check(3, 3);
  S21Matrix matrix_result;
  double array[9] = {1, 1, 1, 1, 1, 1, 1, 1, 1};
  double array_check[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
  FillMatrix(matrix, array, 3, 3);
  FillMatrix(other, array, 3, 3);
  FillMatrix(matrix_check, array_check, 3, 3);
  matrix_result = matrix - other;
  EXPECT_EQ(matrix_result.EqMatrix(matrix_check), true);
}

TEST(SubMatrix, OperationSubPr) {
  S21Matrix matrix;
  S21Matrix other;
  S21Matrix matrix_check(3, 3);
  double array[9] = {1, 1, 1, 1, 1, 1, 1, 1, 1};
  double array_check[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
  FillMatrix(matrix, array, 3, 3);
  FillMatrix(other, array, 3, 3);
  FillMatrix(matrix_check, array_check, 3, 3);
  matrix -= other;
  EXPECT_EQ(matrix.EqMatrix(matrix_check), true);
}

TEST(SubMatrix, OutOfRangeException) {
  S21Matrix matrix;
  S21Matrix other(3, 2);
  double array[9] = {1, 1, 1, 1, 1, 1, 1, 1, 1};
  double array_other[6] = {2, 2, 2, 2, 2, 2};
  FillMatrix(matrix, array, 3, 3);
  FillMatrix(other, array_other, 3, 2);
  EXPECT_THROW(matrix.SubMatrix(other), std::invalid_argument);
}

TEST(MulNumber, Basic) {
  S21Matrix matrix;
  double number = 2;
  S21Matrix matrix_check(3, 3);
  double array[9] = {1, 1, 1, 1, 1, 1, 1, 1, 1};
  double array_check[9] = {2, 2, 2, 2, 2, 2, 2, 2, 2};
  FillMatrix(matrix, array, 3, 3);
  FillMatrix(matrix_check, array_check, 3, 3);
  matrix.MulNumber(number);
  EXPECT_EQ(matrix.EqMatrix(matrix_check), true);
}

TEST(MulNumber, OperatorF) {
  S21Matrix matrix;
  double number = 2;
  S21Matrix matrix_check(3, 3);
  S21Matrix matrix_result;
  double array[9] = {1, 1, 1, 1, 1, 1, 1, 1, 1};
  double array_check[9] = {2, 2, 2, 2, 2, 2, 2, 2, 2};
  FillMatrix(matrix, array, 3, 3);
  FillMatrix(matrix_check, array_check, 3, 3);
  matrix_result = matrix * number;
  EXPECT_EQ(matrix_result.EqMatrix(matrix_check), true);
}

TEST(MulNumber, OperatorPr) {
  S21Matrix matrix;
  double number = 2;
  S21Matrix matrix_check(3, 3);
  double array[9] = {1, 1, 1, 1, 1, 1, 1, 1, 1};
  double array_check[9] = {2, 2, 2, 2, 2, 2, 2, 2, 2};
  FillMatrix(matrix, array, 3, 3);
  FillMatrix(matrix_check, array_check, 3, 3);
  matrix *= number;
  EXPECT_EQ(matrix.EqMatrix(matrix_check), true);
}

TEST(MulMatrix, OperationNmulm) {
  S21Matrix matrix;
  S21Matrix matrixx(3, 3);
  S21Matrix matrix_check(3, 3);
  S21Matrix matrix_result;
  double array[9] = {1, 1, 1, 1, 1, 1, 1, 1, 1};
  double arrayy[9] = {2, 2, 2, 2, 2, 2, 2, 2, 2};
  double array_check[9] = {6, 6, 6, 6, 6, 6, 6, 6, 6};
  FillMatrix(matrix, array, 3, 3);
  FillMatrix(matrixx, arrayy, 3, 3);
  FillMatrix(matrix_check, array_check, 3, 3);
  matrix_result = matrix * matrixx;
  EXPECT_EQ(matrix_result.EqMatrix(matrix_check), true);
}

TEST(MulMatrix, OperationNmulmPr) {
  S21Matrix matrix;
  S21Matrix matrixx(3, 3);
  S21Matrix matrix_check(3, 3);
  double array[9] = {1, 1, 1, 1, 1, 1, 1, 1, 1};
  double arrayy[9] = {2, 2, 2, 2, 2, 2, 2, 2, 2};
  double array_check[9] = {6, 6, 6, 6, 6, 6, 6, 6, 6};
  FillMatrix(matrix, array, 3, 3);
  FillMatrix(matrixx, arrayy, 3, 3);
  FillMatrix(matrix_check, array_check, 3, 3);
  matrix *= matrixx;
  EXPECT_EQ(matrix.EqMatrix(matrix_check), true);
}

TEST(MulMatrix, Basic) {
  S21Matrix matrix;
  S21Matrix matrixx(3, 3);
  S21Matrix matrix_check(3, 3);
  double array[9] = {1, 1, 1, 1, 1, 1, 1, 1, 1};
  double arrayy[9] = {2, 2, 2, 2, 2, 2, 2, 2, 2};
  double array_check[9] = {6, 6, 6, 6, 6, 6, 6, 6, 6};
  FillMatrix(matrix, array, 3, 3);
  FillMatrix(matrixx, arrayy, 3, 3);
  FillMatrix(matrix_check, array_check, 3, 3);
  matrix.MulMatrix(matrixx);
  EXPECT_EQ(matrix.EqMatrix(matrix_check), true);
}

TEST(MulMatrix, OutOfRangeException) {
  S21Matrix matrix;
  S21Matrix other(2, 2);
  double array[9] = {1, 1, 1, 1, 1, 1, 1, 1, 1};
  double array_other[4] = {2, 2, 2, 2};
  FillMatrix(matrix, array, 3, 3);
  FillMatrix(other, array_other, 2, 2);
  EXPECT_THROW(matrix.MulMatrix(other), std::invalid_argument);
}

TEST(ReloadBrackes, Basic) {
  S21Matrix matrix;
  double element;
  double array[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  FillMatrix(matrix, array, 3, 3);
  element = matrix(1, 1);
  EXPECT_EQ(element, 5);
}

TEST(ReloadBrackes, OutOfRangeExceptionBigger) {
  S21Matrix matrix;
  double array[9] = {1, 1, 1, 1, 1, 1, 1, 1, 1};
  FillMatrix(matrix, array, 3, 3);
  EXPECT_THROW(matrix(1, 10), std::out_of_range);
}

TEST(ReloadBrackes, OutOfRangeExceptionSmaller) {
  S21Matrix matrix;
  double array[9] = {1, 1, 1, 1, 1, 1, 1, 1, 1};
  FillMatrix(matrix, array, 3, 3);
  EXPECT_THROW(matrix(1, -1), std::out_of_range);
}

TEST(Transpose, Squard) {
  S21Matrix matrix;
  S21Matrix matrix_check(3, 3);
  double array[9] = {9, 8, 7, 6, 5, 4, 3, 2, 1};
  double array_check[9] = {9, 6, 3, 8, 5, 2, 7, 4, 1};
  FillMatrix(matrix, array, 3, 3);
  FillMatrix(matrix_check, array_check, 3, 3);
  S21Matrix matrix_new(matrix.Transpose());
  EXPECT_EQ(matrix_new.EqMatrix(matrix_check), true);
}

TEST(Transpose, ManyRows) {
  S21Matrix matrix(3, 2);
  S21Matrix matrix_check(2, 3);
  double array[6] = {6, 5, 4, 3, 2, 1};
  double array_check[6] = {6, 4, 2, 5, 3, 1};
  FillMatrix(matrix, array, 3, 2);
  FillMatrix(matrix_check, array_check, 2, 3);
  S21Matrix matrix_new(2, 3);
  matrix_new = matrix.Transpose();
  EXPECT_EQ(matrix_new.EqMatrix(matrix_check), true);
}

TEST(Transpose, ManyCols) {
  S21Matrix matrix(2, 3);
  S21Matrix matrix_check(3, 2);
  double array[6] = {6, 5, 4, 3, 2, 1};
  double array_check[6] = {6, 3, 5, 2, 4, 1};
  FillMatrix(matrix, array, 2, 3);
  FillMatrix(matrix_check, array_check, 3, 2);
  S21Matrix matrix_new(3, 2);
  matrix_new = matrix.Transpose();
  EXPECT_EQ(matrix_new.EqMatrix(matrix_check), true);
}

TEST(CalcComplements, Basic) {
  S21Matrix matrix;
  S21Matrix matrix_check(3, 3);
  double array[9] = {1, 2, 5, 2, 4, 0, 3, 2, 1};
  double array_check[9] = {4, -2, -8, 8, -14, 4, -20, 10, 0};
  FillMatrix(matrix, array, 3, 3);
  FillMatrix(matrix_check, array_check, 3, 3);
  S21Matrix matrix_new(3, 3);
  matrix_new = matrix.CalcComplements();
  EXPECT_EQ(matrix_new.EqMatrix(matrix_check), true);
}

TEST(CalcComplements, One) {
  S21Matrix matrix(1, 1);
  double array[1] = {1};
  FillMatrix(matrix, array, 1, 1);
  EXPECT_THROW(matrix.CalcComplements(), std::logic_error);
}

TEST(CalcComplements, TwoTwo) {
  S21Matrix matrix(2, 2);
  S21Matrix matrix_check(2, 2);
  double array[4] = {4, 3, 2, 1};
  double array_check[4] = {1, -2, -3, 4};
  FillMatrix(matrix, array, 2, 2);
  FillMatrix(matrix_check, array_check, 2, 2);
  S21Matrix matrix_new(2, 2);
  matrix_new = matrix.CalcComplements();
  EXPECT_EQ(matrix_new.EqMatrix(matrix_check), true);
}

TEST(CalcComplements, LogicError) {
  S21Matrix matrix(3, 2);
  double array[6] = {2, 2, 2, 2, 2, 2};
  FillMatrix(matrix, array, 3, 2);
  EXPECT_THROW(matrix.CalcComplements(), std::logic_error);
}

TEST(Inverse, Basic) {
  S21Matrix matrix;
  S21Matrix matrix_check(3, 3);
  double array[9] = {1, 2, -1, -2, 0, 1, 1, -1, 0};
  double array_check[9] = {1, 1, 2, 1, 1, 1, 2, 3, 4};
  FillMatrix(matrix, array, 3, 3);
  FillMatrix(matrix_check, array_check, 3, 3);
  S21Matrix matrix_new(3, 3);
  matrix_new = matrix.InverseMatrix();
  EXPECT_EQ(matrix_new.EqMatrix(matrix_check), true);
}

TEST(Inverse, OutOfRangeException) {
  S21Matrix matrix;
  double array[9] = {9, 8, 7, 6, 5, 4, 3, 2, 1};
  FillMatrix(matrix, array, 3, 3);
  EXPECT_THROW(matrix.InverseMatrix(), std::logic_error);
}

TEST(Determinant, Basic) {
  S21Matrix matrix;
  double check = 24;
  double array[9] = {1, 8, 7, 6, 5, 4, 3, 2, 1};
  FillMatrix(matrix, array, 3, 3);
  double det = matrix.Determinant();
  EXPECT_EQ(det, check);
}

TEST(Determinant, One) {
  S21Matrix matrix(1, 1);
  double check = 1;
  double array[1] = {1};
  FillMatrix(matrix, array, 1, 1);
  double det = matrix.Determinant();
  EXPECT_EQ(det, check);
}

TEST(Determinant, LogicError) {
  S21Matrix matrix(3, 2);
  double array[6] = {2, 2, 2, 2, 2, 2};
  FillMatrix(matrix, array, 3, 2);
  EXPECT_THROW(matrix.Determinant(), std::logic_error);
}

int main(int argc, char *argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
