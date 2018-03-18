/*********************************************************************************
*	Módulo Interface:
*		Interface
*	Letras identificadoras:
*		ITF
*	Nome do arquivo de inclusão:
*		interface.hpp
*	Arquivos de definição:
*		interface.cpp
*	Projeto:
*		Simulador de fluxo experimental PUC-Rio
*	Desenvolvedores:
*		rrc	-	Rafael Rubim Cabral
*	Histórico de desenvolvimento:
*		Versão	-	Data		-	Comentários
*		1		-	11/07/17	-	Desenvolvimento completo do módulo.
*	Descrição do módulo:
*		Implementa a classe puramente estática que gera uma interface com uma
*			janela do windows em display, implementada por openGL. Como a classe é
*			puramente estática, não pode ser instanciada, pois só uma janela pode
*			ser criada em todo o programa.
*		A janela é criada quando se chama interface::Init(), mas fazê-lo cria um
*			loop Infinito que não permite a continuação do programa e o método nunca
*			retorna, portanto recomenda-se fazê-lo em uma thread separada.
*		A interface guarda ainda uma lista de callbacks que usa para desenhar elementos
*			na janela criada.
*********************************************************************************/

#pragma once

/*********************************************************************************
*	Inclusões de bibliotecas utilizadas
*********************************************************************************/

#include <vector>
#include "vectorPlus.hpp"

/*********************************************************************************
*	Definição de tipos
*********************************************************************************/

typedef void(*desenharDecl)();

/*********************************************************************************
*	Definição da classe interface
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