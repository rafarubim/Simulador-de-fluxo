/*********************************************************************************
*	M�dulo Interface:
*		Adicionais de vetor
*	Letras identificadoras:
*		VECP
*	Nome do arquivo de inclus�o:
*		vectorPlus.hpp
*	Arquivos de defini��o:
*		vectorPlus.cpp
*	Projeto:
*		Simulador de fluxo experimental PUC-Rio
*	Desenvolvedores:
*		rrc	-	Rafael Rubim Cabral
*	Hist�rico de desenvolvimento:
*		Vers�o	-	Data		-	Coment�rios
*		1		-	24/05/17	-	Desenvolvimento de v�rias opera��es b�sicas
*									de sobrecarga e impress�o por iostream.
*	Descri��o do m�dulo:
*		Implementa opera��es adicionais para a classe vector atrav�s da sobrecarga
*			de operadores e fun��es.
*		Possibilita tamb�m impress�o de vetor pela classe ostream.
*********************************************************************************/
#pragma once

/*********************************************************************************
*	Inclus�es de bibliotecas utilizadas
*********************************************************************************/

#include <vector>

/*********************************************************************************
*	Interface de fun��es exportadas pelo m�dulo
*********************************************************************************/

/*********************************************************************************
*	Fun��o:
*		Operador <<: ostream << vector
*	Descri��o:
*		Permite a impress�o do vetor vec por uma classe ostream (cout, cerr)
*********************************************************************************/
template <typename Type> std::ostream& operator<<(std::ostream& out, const std::vector<Type> vec);

/*********************************************************************************
*	Fun��o:
*		Operador +: vector + vector
*	Descri��o:
*		Retorna a soma de dois vetores. Os vetores devem ter tamanhos iguais. Essa
*		fun��o � uma sobrecarga do m�todo Operador + para vetores.
*	Excess�es:
*		VECP_TAM_INCONSISTENTE	-	Os vetores n�o possuem tamanhos compat�veis
*********************************************************************************/
template <typename Type> std::vector<Type> operator+(std::vector<Type> a, std::vector<Type> b);

/*********************************************************************************
*	Fun��o:
*		Operador -: - vector
*	Descri��o:
*		Retorna o vetor com sinal inverso. Essa fun��o � uma sobrecarga do m�todo
*		Operador - para vetores.
*********************************************************************************/
template <typename Type> std::vector<Type> operator-(std::vector<Type> a);

/*********************************************************************************
*	Fun��o:
*		Operador -: vector - vector
*	Descri��o:
*		Retorna a subtra��o de dois vetores. Os vetores devem ter tamanhos iguais.
*		Essa fun��o � uma sobrecarga do m�todo Operador - para vetores.
*	Excess�es:
*		VECP_TAM_INCONSISTENTE	-	Os vetores n�o possuem tamanhos compat�veis
*********************************************************************************/
template <typename Type> std::vector<Type> operator-(std::vector<Type> a, std::vector<Type> b);

/*********************************************************************************
*	Fun��o:
*		Operador *: const * vector
*	Descri��o:
*		Retorna a multiplica��o de uma constante por um vetor. Essa fun��o � uma
*		sobrecarga do m�todo Operador * para vetores.
*********************************************************************************/
template <typename Type> std::vector<Type> operator*(const Type alpha, std::vector<Type> a);

/*********************************************************************************
*	Fun��o:
*		Operador *: vector * const
*	Descri��o:
*		Retorna a multiplica��o de um vetor por uma constante. Essa fun��o � uma
*		sobrecarga do m�todo Operador * para vetores.
*********************************************************************************/
template <typename Type> std::vector<Type> operator*(std::vector<Type> a, const Type alpha);

/*********************************************************************************
*	Inclus�o do arquivo de defini��es de fun��es/m�todos template ou inline
*********************************************************************************/
#ifndef VECTORPLUS_OWN
/* Se VECTORPLUS_OWN est� definido, ent�o o arquivo atual est� sendo incluido no
pr�prio vectorPlus.cpp e n�o deve inclu�-lo */
#include "vectorPlus.cpp"
#endif