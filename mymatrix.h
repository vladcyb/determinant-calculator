#ifndef MYMATRIX_H
#define MYMATRIX_H

#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <chrono>
#include <thread>

typedef std::vector<std::vector<int>> matrix;
int inputInt();
int signs(int);
int findMaxSigns(matrix&);
void printMatrix(matrix&);
void fillMatrix(matrix& mtrx, int n, int favorite);
void randomMatrix();
int det(matrix&, int, int);
matrix minor1(matrix&, int, int);
matrix complement(matrix&);
void determ();
void checkNext();
void writeDeterminantToX (int& x, matrix& v, int idx_from, int idx_to);
int len(int);
int findMaxLength(matrix& a);
void addRow(matrix& a, const int x, const int y);
void addCol(matrix& a, const int x, const int y);

#endif
