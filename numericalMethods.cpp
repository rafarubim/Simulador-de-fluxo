#include <vector>
#include "vectorPlus.hpp"
#include "matrix.hpp"

/* Critério: A ser quadrada diagonal dominante */
vector<double> JacobiSolve(matrix<double> A, vector<double> b, vector<double> x0, int iter) {
	matrix<double> X(x0);
	matrix<double> B(b);
	matrix<double> D(A.GetM(), A.GetN());
	matrix<double> Dinv(A.GetM(), A.GetN());
	for (int i = 0; i < A.GetM(); i++) {
		D[i][i] = A[i][i];
		Dinv[i][i] = 1 / A[i][i];
	}
	matrix<double> R = A - D;
	for (int i = 0; i < iter; i++) {
		X = Dinv * (B - (R * X)); \
	}
	return X.CastToVec();
}

/* Critério: A ser quadrada diagonal dominante ou A ser simétrica positiva definida */
vector<double> GaussSeidelSolve(matrix<double> A, vector<double> b, vector<double> x0, int iter) {
	matrix<double> X(x0);
	matrix<double> B(b);
	matrix<double> X1(x0);

	for (int k = 0; k < iter; k++) {

		for (int i = 0; i < X1.GetM(); i++) {
			double sum = 0;
			for (int j = 0; j < A.GetN(); j++) {
				if (i != j) {
					sum += A[i][j] * X[j][0];
				}
			}
			X1[i][0] = (B[i][0] - sum) / A[i][i];
		}

		X = X1;
	}

	return X.CastToVec();
}