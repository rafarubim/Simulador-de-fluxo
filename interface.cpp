/*********************************************************************************
*	M�dulo de Defini��o:
*		Interface
*	Letras identificadoras:
*		ITF
*	Nome do arquivo de defini��o:
*		interface.cpp
*	Arquivo de interface:
*		interface.hpp
*	Projeto:
*		Simulador de fluxo experimental PUC-Rio
*	Desenvolvedores:
*		rrc	-	Rafael Rubim Cabral
*	Hist�rico de desenvolvimento:
*		Vers�o	-	Data		-	Coment�rios
*		1		-	11/07/17	-	Desenvolvimento completo do m�dulo.
*********************************************************************************/

/*********************************************************************************
*	Inclus�o do arquivo de interface
*/
#include "interface.hpp"

/*********************************************************************************
*	Inclus�es de bibliotecas utilizadas
*********************************************************************************/

#include "glut.h"
#include <iostream>
using namespace std;

/*********************************************************************************
*	Defini��es de m�todos privados
*********************************************************************************/

/*********************************************************************************
*	M�todo:	Display
*/
void interface::_Display() {

	glClearColor(_bckColor[0], _bckColor[1], _bckColor[2], _bckColor[3]);
	glClear(GL_COLOR_BUFFER_BIT |  GL_DEPTH_BUFFER_BIT);

	for (int i = 0; i < _numDesenhos; i++) {

		_callbacksDesenho[i]();
	}
	glutPostRedisplay();
	glutSwapBuffers();
}	/* fim m�todo Display */

/*********************************************************************************
*	Defini��es de m�todos p�blicos
*********************************************************************************/

/*********************************************************************************
*	M�todo:	Init
*/
void interface::Init() {

	int argc = 1;
	char* argv[2] = { "", 0 };

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(800, 800);
	glutCreateWindow("Simulador");
	glutDisplayFunc(_Display);
	gluOrtho2D(-1, 1, -1, 1);
	glutMainLoop();
}	/* fim m�todo Init */

/*********************************************************************************
*	M�todo:	Atribuir cor de fundo
*/
void interface::SetBckColor(float r, float g, float b, float a) {

	_bckColor[0] = r;
	_bckColor[1] = g;
	_bckColor[2] = b;
	_bckColor[3] = a;
}	/* fim m�todo Atribuir cor de fundo */

/*********************************************************************************
*	M�todo:	Adicionar desenho
*/
void interface::AddDesenho(desenharDecl callbackDesenho) {

	_callbacksDesenho.push_back(callbackDesenho);
	_numDesenhos++;
	glutPostRedisplay();
}	/* fim m�todo Adicionar desenho */

/*********************************************************************************
*	M�todo:	Deletar desenho
*/
void interface:: DelDesenho(desenharDecl callbackDesenho) {
	for (int i = 0; i < _numDesenhos; i++) {
		if (_callbacksDesenho[i] == callbackDesenho) {
			_callbacksDesenho.erase(_callbacksDesenho.begin() + i);
			_numDesenhos--;
			glutPostRedisplay();
			return;
		}
	}
}	/* fim m�todo Deletar desenho */

/*********************************************************************************
*	Defini��es de vari�veis-membro est�ticas
*********************************************************************************/

float interface::_bckColor[4] = {1, 1, 1, 1};
vector<desenharDecl> interface::_callbacksDesenho;
int interface::_numDesenhos(0);