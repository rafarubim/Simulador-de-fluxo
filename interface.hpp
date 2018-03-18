/*********************************************************************************
*	M�dulo Interface:
*		Interface
*	Letras identificadoras:
*		ITF
*	Nome do arquivo de inclus�o:
*		interface.hpp
*	Arquivos de defini��o:
*		interface.cpp
*	Projeto:
*		Simulador de fluxo experimental PUC-Rio
*	Desenvolvedores:
*		rrc	-	Rafael Rubim Cabral
*	Hist�rico de desenvolvimento:
*		Vers�o	-	Data		-	Coment�rios
*		1		-	11/07/17	-	Desenvolvimento completo do m�dulo.
*	Descri��o do m�dulo:
*		Implementa a classe puramente est�tica que gera uma interface com uma
*			janela do windows em display, implementada por openGL. Como a classe �
*			puramente est�tica, n�o pode ser instanciada, pois s� uma janela pode
*			ser criada em todo o programa.
*		A janela � criada quando se chama interface::Init(), mas faz�-lo cria um
*			loop Infinito que n�o permite a continua��o do programa e o m�todo nunca
*			retorna, portanto recomenda-se faz�-lo em uma thread separada.
*		A interface guarda ainda uma lista de callbacks que usa para desenhar elementos
*			na janela criada.
*********************************************************************************/

#pragma once

/*********************************************************************************
*	Inclus�es de bibliotecas utilizadas
*********************************************************************************/

#include <vector>
#include "vectorPlus.hpp"

/*********************************************************************************
*	Defini��o de tipos
*********************************************************************************/

typedef void(*desenharDecl)();

/*********************************************************************************
*	Defini��o da classe interface
*********************************************************************************/
class interface {
private:
	static void _Display();
	static float _bckColor[4];
	static vector<desenharDecl> _callbacksDesenho;
	static int _numDesenhos;
public:
	static void Init();
	static void SetBckColor(float r, float g, float b, float a = 1);
	static void AddDesenho(desenharDecl callbackDesenho);
	static void DelDesenho(desenharDecl callbackDesenho);
};