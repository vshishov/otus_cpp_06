#include "matrix.h"

#include <gtest/gtest.h>

using namespace testing;

TEST(Matrix_2D, Create) { 
  Otus::Matrix<int, -1> matrix;
  ASSERT_EQ(matrix.size(), (size_t)0);

  auto a = matrix[0][0];
  ASSERT_EQ((int)a, -1);
  ASSERT_EQ(matrix.size(), (size_t)0);

  matrix[100][100] = 100500;
  ASSERT_EQ((int)matrix[100][100], 100500);
  ASSERT_EQ(matrix.size(), (size_t)1);

  for (auto c : matrix) {
    int x;
    int y;
    int v;
    std::tie(x, y, v) = c;
    EXPECT_EQ(x, 100) << "Row index";
    EXPECT_EQ(y, 100) << "Column index";
    ASSERT_EQ(v, 100500) << "Value";
  }
}

TEST(Matrix_2D, DefaultValue) { 
  const long lDefault = -2;
  Otus::Matrix<long, lDefault> matrix;
  ASSERT_EQ((long)matrix[0][0], lDefault);
  ASSERT_EQ((long)matrix[0][10], lDefault) << "Matrix size must have " << lDefault;
  ASSERT_EQ((long)matrix[5][10], lDefault) << "Matrix size must have " << lDefault;
  ASSERT_EQ((long)matrix[10][0], lDefault) << "Matrix size must have " << lDefault;
  ASSERT_EQ((long)matrix[10][5], lDefault) << "Matrix size must have " << lDefault;
  ASSERT_EQ((long)matrix[10][10], lDefault) << "Matrix size must have " << lDefault;  
}

TEST(Matrix_2D, Main_Diagonal) {
  const short nDefault = -1;
  Otus::Matrix<int, nDefault> matrix;

  int nCount = 500;
  for (int i = 0; i < nCount; ++i) {
    matrix[i][i] = i;
  }

  ASSERT_EQ(matrix.size(), (size_t)nCount);

  for (int i = 0; i < nCount; ++i) {
    for (int j = 0; j < nCount; ++j) {
      int nRequiredValue = nDefault;
      if (i == j) {
        nRequiredValue = i;
      }

      ASSERT_EQ((int)matrix[i][j], nRequiredValue) << '[' << i << "][" << j << "] == " << nRequiredValue;
    }
  }
}

TEST(Matrix_2D, Minor_Diagonal) {
  const short nDefault = -1;
  Otus::Matrix<int, nDefault> matrix;

  int nCount = 500;
  for (int i = 0; i < nCount; ++i) {
    int nPrivIdx = nCount - 1 - i; 
    matrix[nPrivIdx][i] = nPrivIdx;
  }

  ASSERT_EQ(matrix.size(), (size_t)nCount);

  for (int i = 0; i < nCount; ++i) {
    for (int j = 0; j < nCount; ++j) {
      int nRequiredValue = nDefault;
      int nPrivIdx = nCount - 1 - j;
      if (nPrivIdx == i) {
        nRequiredValue = nPrivIdx;
      }

      ASSERT_EQ((int)matrix[i][j], nRequiredValue) << '[' << i << "][" << j << "] == " << nRequiredValue;
    }
  }
}

TEST(Matrix_2D, Exercise) { 
  const short nDefault = 0;
  Otus::Matrix<int, nDefault> matrix;

  int nCount = 10;
  for (int i = 0; i < nCount; ++i) {
    matrix[i][i] = i;
    matrix[nCount - 1 - i][i] = nCount - 1 - i;
  }

  ASSERT_EQ(matrix.size(), (size_t)18);

  for (int i = 0; i < nCount; ++i) {
    ASSERT_TRUE(matrix[i][i] == i) << '[' << i << "][" << i << "] == " << i;
  }

  for (int i = 0; i < nCount; ++i) {
    ASSERT_TRUE(matrix[nCount - 1 - i][i] == nCount - 1 - i) << '[' << nCount - 1 - i << "][" << i << "] == " << nCount - 1 - i;
  }

  int nCountForTest = 500;
  for (int i = 0; i < nCountForTest; ++i) {
    for (int j = 0; j < nCountForTest; ++j) {
      if (i >= nCount || j >= nCount) {
        ASSERT_TRUE(matrix[i][j] == nDefault) << '[' << i << "][" << j << "] == " << nDefault;
      }
    }
  }
}

TEST(Matrix_4D, Create) { 
  Otus::Matrix<int, -1, 4> matrix;
  ASSERT_EQ(matrix.size(), (size_t)0);

  auto a = matrix[0][0][0][0];
  ASSERT_TRUE(a == -1);
  ASSERT_EQ(matrix.size(), (size_t)0);

  matrix[99][100][101][102] = 100500;
  ASSERT_EQ((int)matrix[99][100][101][102], 100500);
  ASSERT_EQ(matrix.size(), (size_t)1);

  for (auto c : matrix) {
    int x;
    int y;
    int z;
    int w;
    int v;
    std::tie(x, y, z, w, v) = c;
    EXPECT_EQ(x, 99);
    EXPECT_EQ(y, 100);
    EXPECT_EQ(z, 101);
    EXPECT_EQ(w, 102);
    ASSERT_EQ(v, 100500) << "Value of matrix";
  }  
}