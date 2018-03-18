#include <vector>
#include "matrix.hpp"
#pragma once
/* Crit�rio: A ser quadrada diagonal dominante */
vector<double> JacobiSolve(matrix<double> A, vector<double> b, vector<double> x0, int iter = 10);

/* Crit�rio: A ser quadrada diagonal dominante ou A ser sim�trica positiva definida */
vector<double> GaussSeidelSolve(matrix<double> A, vector<double> b, vector<double> x0, int iter = 10);