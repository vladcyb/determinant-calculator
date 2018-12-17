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
void fillMatrix(matrix&, int, int);
void randomMatrix();
int det(matrix&, int, int);
matrix minor1(matrix&, int, int);
matrix complement(matrix&);
void determ();

#endif
