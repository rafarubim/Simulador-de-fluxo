#include <vector>
#include "matrix.hpp"
#pragma once
/* Critério: A ser quadrada diagonal dominante */
vector<double> JacobiSolve(matrix<double> A, vector<double> b, vector<double> x0, int iter = 10);

/* Critério: A ser quadrada diagonal dominante ou A ser simétrica positiva definida */
vector<double> GaussSeidelSolve(matrix<double> A, vector<double> b, vector<double> x0, int iter = 10);