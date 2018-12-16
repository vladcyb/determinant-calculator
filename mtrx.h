#ifndef MTRX_H
#define MTRX_H

#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <chrono>

typedef std::vector<std::vector<int>> matrix;
int inputInt();
int signs(int x);
void find_max_signs(matrix& mtrx);
void print_matrix(matrix& mtrx);
void add_row(const int x, const int y);
void add_col(const int x, const int y);
void fill_matrix(matrix& mtrx);
void randomMatrix();
int det(matrix& v);
matrix minor1(matrix& v, int i, int j);
matrix complement(matrix& v);
void determ();

#endif
