/*********************************************************************************
*	Módulo Interface:
*		Matriz
*	Letras identificadoras:
*		MAT
*	Nome do arquivo de inclusão:
*		matrix.hpp
*	Arquivos de definição:
*		matrix.cpp
*	Projeto:
*		Simulador de fluxo experimental PUC-Rio
*	Desenvolvedores:
*		rrc	-	Rafael Rubim Cabral
*	Histórico de desenvolvimento:
*		Versão	-	Data		-	Comentários
*		1		-	23/05/17	-	Desenvolvimento de vários métodos básicos de
*									operações em matriz e arrumação de templates em
*									declarações/definições e documentação
*	Descrição do módulo:
*		Implementa matrizes (2D) e operações sobre elas. Este módulo inclui o módulo
*			"vector", permitindo conversões/contruções matriz/vetor. Acessar uma linha
*			de uma matriz também equivale a acessar um vetor que representa essa linha.
*		Possibilita também impressão de vetor/matriz pela classe ostream.
*		Um objeto matriz é representado pela class template matrix. O tipo do template
*			representa o tipo de cada entrada da matriz. O módulo implementa métodos, 
*			funções e operadores sobre o uso de matrizes.
*		As operações em geral definidas sobre a matriz assumem que a matriz é uma
*			matriz de um tipo numérico. Se não for, várias operações sobre a matriz
*			funcionarão apenas se os elementos da matriz puderem ser operados através
*			de sobrecarga das operações individuais necessárias para os elementos.
*			São operações abstratamente conhecidas. Exemplo: para que a multiplicação
*			de matrizes seja válida, é necessário ser possível somar e multiplicar seus
*			elementos individualmente.
*		Uma matriz só pode ser operada após ser inicializada através de algum de seus
*			métodos que permite alterar o valor de pelo menos um de seus elementos.
*		Se uma exceção ocorrer através do uso de uma matriz, o módulo faz uma chamada
*			I/O para imprimir na saída de erro padrão (stderr) uma mensagem com o
*			problema encontrado e a linha/arquivo onde o erro ocorreu.
*********************************************************************************/
#pragma once

/*********************************************************************************
*	Inclusões de bibliotecas utilizadas
*********************************************************************************/

#include <vector>
#include "vectorPlus.hpp"
#include "raiseException.hpp"

/*********************************************************************************
*	Interface de funções exportadas pelo módulo
*********************************************************************************/
template <typename Type> class matrix;

/*********************************************************************************
*	Função:
*		Operador <<: ostream << matrix
*	Descrição:
*		Permite a impressão da matriz A por uma classe ostream (cout, cerr).
*		Para que a função funcione, deve-se haver a sobrecarga de << para vetores.
*********************************************************************************/
template <typename Type> std::ostream& operator<<(std::ostream& out, const matrix<Type>& A);

/*********************************************************************************
*	Função:
*		Operador *: const * matrix
*	Descrição:
*		Permite a multiplicação de uma constante alpha por uma matriz A. alpha deve
*		ter o mesmo tipo dos elementos de A. Essa função é uma sobrecarga do método
*		Operador * para matrizes e constantes.
*********************************************************************************/
template <typename Type> matrix<Type> operator*(const Type alpha, matrix<Type> A);

/*********************************************************************************
*	Definição da classe matriz
*********************************************************************************/
template <typename Type>
class matrix {
private:
	/*********************************************************************************
	*	Variáveis privadas
	*********************************************************************************/
	std::vector<std::vector<Type>> _buffer;
		/* Vetor de linhas: cada linha é um vetor que guarda dados da matriz */
	 int _m, _n;
		/* Quantidade de linhas e colunas da matriz, respectivamente */
	 bool _initialized;
		/* Se a matriz já foi inicializada ou não */
	 raiseException _error;
		/* Objeto que imprimirá excessão, caso necessário */

	/*********************************************************************************
	*	Métodos privados
	*********************************************************************************/
	/*********************************************************************************
	*	Método:
	*		Assertar inicialização da matriz
	*	Descrição:
	*		Assertiva para garantir que matriz está inicializada. Chama uma excessão
	*		para o caso dela não estar inicializada.
	*	Excessões:
	*		MAT_NAO_INICIALIZADO	-	caso a matriz ainda não tenha sido inicializada
	*********************************************************************************/
	 void AssertarInicializacao();
public:
	/*********************************************************************************
	*	Construtores
	*********************************************************************************/

	/*********************************************************************************
	*	Construtor:
	*		Construtor padrão, de dimensões
	*	Descrição:
	*		Cria uma matriz de m linhas e n colunas não inicializada (por padrão 0).
	*		Ela não poderá ser utilizada até ser inicializada, como pelo método Assign
	*		ou outro método que permita alterar o valor de um de seus elementos.
	*	Excessões:
	*		MAT_VAL_INVALIDO	-	caso valor de m ou n seja negativo
	*********************************************************************************/
	matrix(int m = 0, int n = 0);

	/*********************************************************************************
	*	Construtor:
	*		Construtor de vetor
	*	Descrição:
	*		Cria uma matriz coluna a partir de um vetor (A matriz terá m linhas, onde
	*		m é a dimensão do vetor).
	*********************************************************************************/
	matrix(std::vector<Type> v);

	/*********************************************************************************
	*	Métodos públicos
	*********************************************************************************/
	/*********************************************************************************
	*	Método:
	*		Atribuir
	*	Descrição:
	*		Recebe as dimensões x/y de número de linhas/colunas da matriz e uma nova
	*		matriz padrão do C com tais dimensões. Inicializa o objeto matriz com o número
	*		de linhas/colunas passado e com os valores da matriz padrão do C. Essa
	*		operação sobrescreve o tamanho e valores anteriores do objeto matriz, 
	*		inicializando também o objeto mariz que não havia sido inicializado. O objeto
	*		inicializado já poderá realizar outros métodos e operações.
	*	Excessões:
	*		MAT_VAL_INVALIDO	-	caso valor de m ou n seja não positivo
	*		MAT_TAM_INVALIDO	-	caso o número de colunas da matriz passada seja
	*								diferente de n passado
	*		MAT_INCONSISTENCIA	-	caso uma inconsistência ocorra no código do programa
	*********************************************************************************/
	template <unsigned COL> void Assign(int m, int n, Type mat[][COL]);

	/*********************************************************************************
	*	Método:
	*		Obter m
	*	Descrição:
	*		Retorna o número de linhas da matriz
	*********************************************************************************/
	int GetM();

	/*********************************************************************************
	*	Método:
	*		Obter n
	*	Descrição:
	*		Retorna o número de linhas da matriz
	*********************************************************************************/
	int GetN();

	/*********************************************************************************
	*	Método:
	*		Obter linha
	*	Descrição:
	*		Retorna a linha i da matriz como vetor (iniciando em 0). i deve ser uma linha
	*		válida.A matriz deve estar inicializada.
	*	Excessões:
	*		MAT_VAL_INVALIDO	-	caso valor de i seja negativo ou maior ou igual à
	*								quantidade de linhas da matriz
	*********************************************************************************/
	std::vector<Type> GetLine(int i);

	/*********************************************************************************
	*	Método:
	*		Converter para vetor
	*	Descrição:
	*		Retorna o vetor correspondente à matriz coluna. O vetor terá tamanho igual
	*		ao número de linhas da matriz. A matriz deve estar inicializada e possuir
	*		apenas uma coluna.
	*	Excessões:
	*		MAT_NAO_INICIALIZADO	-	caso a matriz ainda não tenha sido inicializada
	*		MAT_TAM_INCONSISTENTE	-	caso a matriz não seja matriz coluna
	*********************************************************************************/
	std::vector<Type> CastToVec();

	/*********************************************************************************
	*	Método:
	*		Transpor
	*	Descrição:
	*		Retorna a matriz transposta. A matriz deve estar inicializada.
	*	Excessões:
	*		MAT_NAO_INICIALIZADO	-	caso a matriz ainda não tenha sido inicializada
	*********************************************************************************/
	matrix<Type> Transpose();

	//matrix<Type> Invert();

	/*********************************************************************************
	*	Operadores públicos
	*********************************************************************************/

	/*********************************************************************************
	*	Método:
	*		Operador []: matrix []
	*	Descrição:
	*		Retorna uma referência da linha i (iniciando em 0) da matriz, como vetor.
	*		i deve ser uma linha válida. Se a matriz não estiver inicializada, essa
	*		operação a inicializa, pois a referência pode ser usada para alterar os
	*		valores da linha.
	*	Excessões:
	*		MAT_VAL_INVALIDO	-	caso valor de i seja negativo ou maior ou igual à
	*								quantidade de linhas da matriz
	*********************************************************************************/
	std::vector<Type>& operator[](int i);

	/*********************************************************************************
	*	Método:
	*		Operador +: matrix + matrix
	*	Descrição:
	*		Retorna a soma de duas matrizes. Ambas devem ter tamanhos compatíveis e estar
	*		inicializadas.
	*	Excessões:
	*		MAT_NAO_INICIALIZADO	-	caso uma das matrizes ainda não tenha sido inicializada
	*		MAT_TAM_INCONSISTENTE	-	caso as matrizes não tenham dimensões compatíveis
	*********************************************************************************/
	matrix<Type> operator+(matrix<Type>& B);

	/*********************************************************************************
	*	Método:
	*		Operador -: - matrix
	*	Descrição:
	*		Retorna a matrizes com sinal inverso. A matriz deve estar inicializada.
	*	Excessões:
	*		MAT_NAO_INICIALIZADO	-	caso a matriz ainda não tenha sido inicializada
	*********************************************************************************/
	matrix<Type> operator-();

	/*********************************************************************************
	*	Método:
	*		Operador -: matrix - matrix
	*	Descrição:
	*		Retorna a subtração de duas matrizes. Ambas devem ter tamanhos compatíveis
	*		e estar inicializadas.
	*	Excessões:
	*		MAT_NAO_INICIALIZADO	-	caso uma das matrizes ainda não tenha sido inicializada
	*		MAT_TAM_INCONSISTENTE	-	caso as matrizes não tenham dimensões compatíveis
	*********************************************************************************/
	matrix<Type> operator-(matrix<Type>& B);

	/*********************************************************************************
	*	Método:
	*		Operador *: matrix * const
	*	Descrição:
	*		Retorna a multiplicação da matriz por uma constante. A matriz deve estar
	*		inicializada.
	*	Excessões:
	*		MAT_NAO_INICIALIZADO	-	caso a matriz ainda não tenha sido inicializada
	*********************************************************************************/
	matrix<Type> operator*(const Type alpha);

	/*********************************************************************************
	*	Método:
	*		Operador *: matrix * matrix
	*	Descrição:
	*		Retorna a multiplicação de duas matrizes (a ordem importa). Ambas devem ter
	*		tamanhos compatíveis para multiplicação (A*B => A.n = B.n) e estar inicializadas.
	*	Excessões:
	*		MAT_NAO_INICIALIZADO	-	caso uma das matrizes ainda não tenha sido inicializada
	*		MAT_TAM_INCONSISTENTE	-	caso as matrizes não tenham dimensões compatíveis
	*									para multiplicação
	*********************************************************************************/
	matrix<Type> operator*(matrix<Type>& B);

	/*********************************************************************************
	*	Declarações de funções amigas
	*********************************************************************************/
	friend std::ostream& operator<< <>(std::ostream& out, const matrix<Type>& A);
};	/* Fim da classe matrix */

/*********************************************************************************
*	Inclusão do arquivo de definições de funções/métodos template ou inline
*********************************************************************************/
#ifndef MATRIX_OWN
	/* Se MATRIX_OWN está definido, então o arquivo atual está sendo incluido no
	próprio matrix.cpp e não deve incluí-lo */
#include "matrix.cpp"
#endif