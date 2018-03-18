/*********************************************************************************
*	Módulo Interface:
*		Adicionais de vetor
*	Letras identificadoras:
*		VECP
*	Nome do arquivo de inclusão:
*		vectorPlus.hpp
*	Arquivos de definição:
*		vectorPlus.cpp
*	Projeto:
*		Simulador de fluxo experimental PUC-Rio
*	Desenvolvedores:
*		rrc	-	Rafael Rubim Cabral
*	Histórico de desenvolvimento:
*		Versão	-	Data		-	Comentários
*		1		-	24/05/17	-	Desenvolvimento de várias operações básicas
*									de sobrecarga e impressão por iostream.
*	Descrição do módulo:
*		Implementa operações adicionais para a classe vector através da sobrecarga
*			de operadores e funções.
*		Possibilita também impressão de vetor pela classe ostream.
*********************************************************************************/
#pragma once

/*********************************************************************************
*	Inclusões de bibliotecas utilizadas
*********************************************************************************/

#include <vector>

/*********************************************************************************
*	Interface de funções exportadas pelo módulo
*********************************************************************************/

/*********************************************************************************
*	Função:
*		Operador <<: ostream << vector
*	Descrição:
*		Permite a impressão do vetor vec por uma classe ostream (cout, cerr)
*********************************************************************************/
template <typename Type> std::ostream& operator<<(std::ostream& out, const std::vector<Type> vec);

/*********************************************************************************
*	Função:
*		Operador +: vector + vector
*	Descrição:
*		Retorna a soma de dois vetores. Os vetores devem ter tamanhos iguais. Essa
*		função é uma sobrecarga do método Operador + para vetores.
*	Excessões:
*		VECP_TAM_INCONSISTENTE	-	Os vetores não possuem tamanhos compatíveis
*********************************************************************************/
template <typename Type> std::vector<Type> operator+(std::vector<Type> a, std::vector<Type> b);

/*********************************************************************************
*	Função:
*		Operador -: - vector
*	Descrição:
*		Retorna o vetor com sinal inverso. Essa função é uma sobrecarga do método
*		Operador - para vetores.
*********************************************************************************/
template <typename Type> std::vector<Type> operator-(std::vector<Type> a);

/*********************************************************************************
*	Função:
*		Operador -: vector - vector
*	Descrição:
*		Retorna a subtração de dois vetores. Os vetores devem ter tamanhos iguais.
*		Essa função é uma sobrecarga do método Operador - para vetores.
*	Excessões:
*		VECP_TAM_INCONSISTENTE	-	Os vetores não possuem tamanhos compatíveis
*********************************************************************************/
template <typename Type> std::vector<Type> operator-(std::vector<Type> a, std::vector<Type> b);

/*********************************************************************************
*	Função:
*		Operador *: const * vector
*	Descrição:
*		Retorna a multiplicação de uma constante por um vetor. Essa função é uma
*		sobrecarga do método Operador * para vetores.
*********************************************************************************/
template <typename Type> std::vector<Type> operator*(const Type alpha, std::vector<Type> a);

/*********************************************************************************
*	Função:
*		Operador *: vector * const
*	Descrição:
*		Retorna a multiplicação de um vetor por uma constante. Essa função é uma
*		sobrecarga do método Operador * para vetores.
*********************************************************************************/
template <typename Type> std::vector<Type> operator*(std::vector<Type> a, const Type alpha);

/*********************************************************************************
*	Inclusão do arquivo de definições de funções/métodos template ou inline
*********************************************************************************/
#ifndef VECTORPLUS_OWN
/* Se VECTORPLUS_OWN está definido, então o arquivo atual está sendo incluido no
próprio vectorPlus.cpp e não deve incluí-lo */
#include "vectorPlus.cpp"
#endif