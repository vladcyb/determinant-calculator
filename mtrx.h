#ifndef MTRX_H
#define MTRX_H

#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <chrono>

int inputInt();
int signs(int x);
void find_max_signs(std::vector<std::vector<int>>& mtrx);
void print_matrix(std::vector<std::vector<int>>& mtrx);
void add_row(const int x, const int y);
void add_col(const int x, const int y);
void fill_matrix(std::vector<std::vector<int>>& mtrx);
void randomMatrix();
int det(std::vector< std::vector<int> >& v);
std::vector< std::vector<int> > minor1(std::vector< std::vector<int> >& v, int i, int j);
std::vector< std::vector<int> > complement(std::vector< std::vector<int> >& v);
void determ();

#endif
