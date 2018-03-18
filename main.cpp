#include <iostream>
#include <vector>
#include "vectorPlus.hpp"
#include "matrix.hpp"
#include "numericalMethods.hpp"
#include "interface.hpp"
#include <thread>
#include "glut.h"
using namespace std;

#define EVER ;;

int _n = 0;
matrix<double> _A;
vector<double> _b;
vector<double> _x0;
vector<double> _x1;
vector<double> _x2;

void EscreverString(const char *str) {
	for (int i = 0; str[i] != '\0'; ++i) {
		glutStrokeCharacter(GLUT_STROKE_ROMAN, str[i]);
	}
}

void EscreverNum(const double num) {
	char buffer[100];
	snprintf(buffer, 100, "%.1f", num);
	EscreverString(buffer);
}

void DesenharSistema() {
	
	glColor3f(0, 0, 0);
	glMatrixMode(GL_MODELVIEW);

	glTranslatef(-0.6, 0.7, 0);
	glScalef(.002, .002, 1);
		EscreverString("Ax = b");
	glLoadIdentity();

	// A
	glBegin(GL_LINES);
		glVertex2f(-0.75, 0.6);
		glVertex2f(-0.8, 0.6);
		glVertex2f(-0.8, 0.6);
		glVertex2f(-0.8, 0);
		glVertex2f(-0.8, 0);
		glVertex2f(-0.75, 0);
	glEnd();

	glBegin(GL_LINES);
		glVertex2f(-0.25, 0.6);
		glVertex2f(-0.2, 0.6);
		glVertex2f(-0.2, 0.6);
		glVertex2f(-0.2, 0);
		glVertex2f(-0.2, 0);
		glVertex2f(-0.25, 0);
	glEnd();


	for (int i = 0; i < _A.GetM(); i++) {
		for (int j = 0; j < _A.GetN(); j++) {
			glTranslatef(-0.8 + 0.05 + j*0.6/_n, 0.6 + 0.07 - (i+1)*0.6/_n, 0);
			glScalef(.0005, .0005, 1);
				EscreverNum(_A[i][j]);
			glLoadIdentity();
		}
	}
	
	// x
	glBegin(GL_LINES);
		glVertex2f(-0.1, 0.6);
		glVertex2f(-0.15, 0.6);
		glVertex2f(-0.15, 0.6);
		glVertex2f(-0.15, 0);
		glVertex2f(-0.15, 0);
		glVertex2f(-0.1, 0);
	glEnd();

	glBegin(GL_LINES);
		glVertex2f(0, 0.6);
		glVertex2f(0.05, 0.6);
		glVertex2f(0.05, 0.6);
		glVertex2f(0.05, 0);
		glVertex2f(0.05, 0);
		glVertex2f(0, 0);
	glEnd();

	for (int i = 0; i < _n; i++) {
		glTranslatef(-0.15 + 0.05 , 0.6 + 0.07 - (i + 1)*0.6 / _n, 0);
		glScalef(.0005, .0005, 1);
			EscreverString("x");
			EscreverNum(i);
		glLoadIdentity();
	}

	glTranslatef(0.15, 0.2, 0);
	glScalef(.002, .002, 1);
		EscreverString("=");
	glLoadIdentity();

	// b
	glBegin(GL_LINES);
		glVertex2f(0.5, 0.6);
		glVertex2f(0.45, 0.6);
		glVertex2f(0.45, 0.6);
		glVertex2f(0.45, 0);
		glVertex2f(0.45, 0);
		glVertex2f(0.5, 0);
	glEnd();

	glBegin(GL_LINES);
		glVertex2f(0.6, 0.6);
		glVertex2f(0.65, 0.6);
		glVertex2f(0.65, 0.6);
		glVertex2f(0.65, 0);
		glVertex2f(0.65, 0);
		glVertex2f(0.6, 0);
	glEnd();

	for (unsigned int i = 0; i < _b.size(); i++) {
		glTranslatef(0.45 + 0.05, 0.6 + 0.07 - (i + 1)*0.6 / _n, 0);
		glScalef(.0005, .0005, 1);
			EscreverNum(_b[i]);
		glLoadIdentity();
	}
	
	// x Jacobi
	glTranslatef(-0.8, -0.3, 0);
	glScalef(.002, .002, 1);
		EscreverString("x:");
	glLoadIdentity();

	glTranslatef(-0.85, -0.4, 0);
	glScalef(.0005, .0005, 1);
	EscreverString("(Jacobi)");
	glLoadIdentity();

	glBegin(GL_LINES);
		glVertex2f(-0.45, -0.2);
		glVertex2f(-0.5, -0.2);
		glVertex2f(-0.5, -0.2);
		glVertex2f(-0.5, -0.8);
		glVertex2f(-0.5, -0.8);
		glVertex2f(-0.45, -0.8);
	glEnd();

	glBegin(GL_LINES);
		glVertex2f(-0.35, -0.2);
		glVertex2f(-0.3, -0.2);
		glVertex2f(-0.3, -0.2);
		glVertex2f(-0.3, -0.8);
		glVertex2f(-0.3, -0.8);
		glVertex2f(-0.35, -0.8);
	glEnd();

	for (unsigned int i = 0; i < _x1.size(); i++) {
		glTranslatef(-0.5 + 0.05, -0.2 + 0.07 - (i + 1)*0.6 / _n, 0);
		glScalef(.0005, .0005, 1);
			EscreverNum(_x1[i]);
		glLoadIdentity();
	}

	// x Gauss Seidel
	glTranslatef(0, -0.3, 0);
	glScalef(.002, .002, 1);
	EscreverString("x:");
	glLoadIdentity();

	glTranslatef(-0.15, -0.4, 0);
	glScalef(.0005, .0005, 1);
	EscreverString("(Gauss-Seidel)");
	glLoadIdentity();

	glBegin(GL_LINES);
		glVertex2f(0.45, -0.2);
		glVertex2f(0.4, -0.2);
		glVertex2f(0.4, -0.2);
		glVertex2f(0.4, -0.8);
		glVertex2f(0.4, -0.8);
		glVertex2f(0.45, -0.8);
	glEnd();

	glBegin(GL_LINES);
		glVertex2f(0.55, -0.2);
		glVertex2f(0.6, -0.2);
		glVertex2f(0.6, -0.2);
		glVertex2f(0.6, -0.8);
		glVertex2f(0.6, -0.8);
		glVertex2f(0.55, -0.8);
	glEnd();

	for (unsigned int i = 0; i < _x2.size(); i++) {
		glTranslatef(0.4 + 0.05, -0.2 + 0.07 - (i + 1)*0.6 / _n, 0);
		glScalef(.0005, .0005, 1);
		EscreverNum(_x2[i]);
		glLoadIdentity();
	}
}

int main() {

	thread thrInterface(interface::Init);

	// Exemplo Matriz A: { { 8,1,-1 }, { 1,-7,2 }, { 2,1,9 } }
	// Exemplo Vetor b: {8,-4, 12}
	// Exemplo Vetor x esperado: {1, 1, 1}

	for (EVER) {
		cout << "O programa resolvera o sistema Ax = b.\nComece digitando a dimensao da matriz quadrada A: ";
		cin >> _n;
		interface::AddDesenho(DesenharSistema);
		_A = matrix<double>(_n, _n);
		cout << "Digite as entradas da matriz A:\n";
		for (int i = 0; i < _n; i++) {
			for (int j = 0; j < _n; j++) {
				cout << "A[" << i << "][" << j << "] = ";
				cin >> _A[i][j];
			}
		}
		cout << "Digite agora as entradas do vetor b (dimensao " << _n << "):\n";
		_b = vector<double>(_n);
		for (int i = 0; i < _n; i++) {
			cout << "b[" << i << "] = ";
			cin >> _b[i];
		}
		cout << "--A:\n" << _A << endl;
		cout << "--b:\n" << _b << endl;
		_x0 = vector<double>(_n);
		_x1 = JacobiSolve(_A, _b, _x0, 20);
		cout << "--Resolucao pelos metodos numericos:\n-Jacobi -> x:\n" << _x1 << endl;
		_x2 = GaussSeidelSolve(_A, _b, _x0, 20);
		cout << "-Gauss-Seidel -> x:\n" << _x2 << endl;
		system("pause");
		system("cls");
		interface::DelDesenho(DesenharSistema);
	}

	thrInterface.join();

	return 0;
}