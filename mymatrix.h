#ifndef MYMATRIX_H
#define MYMATRIX_H

#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <chrono>

typedef std::vector<std::vector<int>> matrix;
int inputInt();
int signs(int x);
int findMaxSigns(matrix& mtrx);
void printMatrix(matrix& mtrx);
void fillMatrix(matrix& mtrx, int, int);
void randomMatrix();
int det(matrix& v);
matrix minor1(matrix& v, int i, int j);
matrix complement(matrix& v);
void determ();

#endif
