/*********************************************************************************
*	M�dulo Interface:
*		Matriz
*	Letras identificadoras:
*		MAT
*	Nome do arquivo de inclus�o:
*		matrix.hpp
*	Arquivos de defini��o:
*		matrix.cpp
*	Projeto:
*		Simulador de fluxo experimental PUC-Rio
*	Desenvolvedores:
*		rrc	-	Rafael Rubim Cabral
*	Hist�rico de desenvolvimento:
*		Vers�o	-	Data		-	Coment�rios
*		1		-	23/05/17	-	Desenvolvimento de v�rios m�todos b�sicos de
*									opera��es em matriz e arruma��o de templates em
*									declara��es/defini��es e documenta��o
*	Descri��o do m�dulo:
*		Implementa matrizes (2D) e opera��es sobre elas. Este m�dulo inclui o m�dulo
*			"vector", permitindo convers�es/contru��es matriz/vetor. Acessar uma linha
*			de uma matriz tamb�m equivale a acessar um vetor que representa essa linha.
*		Possibilita tamb�m impress�o de vetor/matriz pela classe ostream.
*		Um objeto matriz � representado pela class template matrix. O tipo do template
*			representa o tipo de cada entrada da matriz. O m�dulo implementa m�todos, 
*			fun��es e operadores sobre o uso de matrizes.
*		As opera��es em geral definidas sobre a matriz assumem que a matriz � uma
*			matriz de um tipo num�rico. Se n�o for, v�rias opera��es sobre a matriz
*			funcionar�o apenas se os elementos da matriz puderem ser operados atrav�s
*			de sobrecarga das opera��es individuais necess�rias para os elementos.
*			S�o opera��es abstratamente conhecidas. Exemplo: para que a multiplica��o
*			de matrizes seja v�lida, � necess�rio ser poss�vel somar e multiplicar seus
*			elementos individualmente.
*		Uma matriz s� pode ser operada ap�s ser inicializada atrav�s de algum de seus
*			m�todos que permite alterar o valor de pelo menos um de seus elementos.
*		Se uma exce��o ocorrer atrav�s do uso de uma matriz, o m�dulo faz uma chamada
*			I/O para imprimir na sa�da de erro padr�o (stderr) uma mensagem com o
*			problema encontrado e a linha/arquivo onde o erro ocorreu.
*********************************************************************************/
#pragma once

/*********************************************************************************
*	Inclus�es de bibliotecas utilizadas
*********************************************************************************/

#include <vector>
#include "vectorPlus.hpp"
#include "raiseException.hpp"

/*********************************************************************************
*	Interface de fun��es exportadas pelo m�dulo
*********************************************************************************/
template <typename Type> class matrix;

/*********************************************************************************
*	Fun��o:
*		Operador <<: ostream << matrix
*	Descri��o:
*		Permite a impress�o da matriz A por uma classe ostream (cout, cerr).
*		Para que a fun��o funcione, deve-se haver a sobrecarga de << para vetores.
*********************************************************************************/
template <typename Type> std::ostream& operator<<(std::ostream& out, const matrix<Type>& A);

/*********************************************************************************
*	Fun��o:
*		Operador *: const * matrix
*	Descri��o:
*		Permite a multiplica��o de uma constante alpha por uma matriz A. alpha deve
*		ter o mesmo tipo dos elementos de A. Essa fun��o � uma sobrecarga do m�todo
*		Operador * para matrizes e constantes.
*********************************************************************************/
template <typename Type> matrix<Type> operator*(const Type alpha, matrix<Type> A);

/*********************************************************************************
*	Defini��o da classe matriz
*********************************************************************************/
template <typename Type>
class matrix {
private:
	/*********************************************************************************
	*	Vari�veis privadas
	*********************************************************************************/
	std::vector<std::vector<Type>> _buffer;
		/* Vetor de linhas: cada linha � um vetor que guarda dados da matriz */
	 int _m, _n;
		/* Quantidade de linhas e colunas da matriz, respectivamente */
	 bool _initialized;
		/* Se a matriz j� foi inicializada ou n�o */
	 raiseException _error;
		/* Objeto que imprimir� excess�o, caso necess�rio */

	/*********************************************************************************
	*	M�todos privados
	*********************************************************************************/
	/*********************************************************************************
	*	M�todo:
	*		Assertar inicializa��o da matriz
	*	Descri��o:
	*		Assertiva para garantir que matriz est� inicializada. Chama uma excess�o
	*		para o caso dela n�o estar inicializada.
	*	Excess�es:
	*		MAT_NAO_INICIALIZADO	-	caso a matriz ainda n�o tenha sido inicializada
	*********************************************************************************/
	 void AssertarInicializacao();
public:
	/*********************************************************************************
	*	Construtores
	*********************************************************************************/

	/*********************************************************************************
	*	Construtor:
	*		Construtor padr�o, de dimens�es
	*	Descri��o:
	*		Cria uma matriz de m linhas e n colunas n�o inicializada (por padr�o 0).
	*		Ela n�o poder� ser utilizada at� ser inicializada, como pelo m�todo Assign
	*		ou outro m�todo que permita alterar o valor de um de seus elementos.
	*	Excess�es:
	*		MAT_VAL_INVALIDO	-	caso valor de m ou n seja negativo
	*********************************************************************************/
	matrix(int m = 0, int n = 0);

	/*********************************************************************************
	*	Construtor:
	*		Construtor de vetor
	*	Descri��o:
	*		Cria uma matriz coluna a partir de um vetor (A matriz ter� m linhas, onde
	*		m � a dimens�o do vetor).
	*********************************************************************************/
	matrix(std::vector<Type> v);

	/*********************************************************************************
	*	M�todos p�blicos
	*********************************************************************************/
	/*********************************************************************************
	*	M�todo:
	*		Atribuir
	*	Descri��o:
	*		Recebe as dimens�es x/y de n�mero de linhas/colunas da matriz e uma nova
	*		matriz padr�o do C com tais dimens�es. Inicializa o objeto matriz com o n�mero
	*		de linhas/colunas passado e com os valores da matriz padr�o do C. Essa
	*		opera��o sobrescreve o tamanho e valores anteriores do objeto matriz, 
	*		inicializando tamb�m o objeto mariz que n�o havia sido inicializado. O objeto
	*		inicializado j� poder� realizar outros m�todos e opera��es.
	*	Excess�es:
	*		MAT_VAL_INVALIDO	-	caso valor de m ou n seja n�o positivo
	*		MAT_TAM_INVALIDO	-	caso o n�mero de colunas da matriz passada seja
	*								diferente de n passado
	*		MAT_INCONSISTENCIA	-	caso uma inconsist�ncia ocorra no c�digo do programa
	*********************************************************************************/
	template <unsigned COL> void Assign(int m, int n, Type mat[][COL]);

	/*********************************************************************************
	*	M�todo:
	*		Obter m
	*	Descri��o:
	*		Retorna o n�mero de linhas da matriz
	*********************************************************************************/
	int GetM();

	/*********************************************************************************
	*	M�todo:
	*		Obter n
	*	Descri��o:
	*		Retorna o n�mero de linhas da matriz
	*********************************************************************************/
	int GetN();

	/*********************************************************************************
	*	M�todo:
	*		Obter linha
	*	Descri��o:
	*		Retorna a linha i da matriz como vetor (iniciando em 0). i deve ser uma linha
	*		v�lida.A matriz deve estar inicializada.
	*	Excess�es:
	*		MAT_VAL_INVALIDO	-	caso valor de i seja negativo ou maior ou igual �
	*								quantidade de linhas da matriz
	*********************************************************************************/
	std::vector<Type> GetLine(int i);

	/*********************************************************************************
	*	M�todo:
	*		Converter para vetor
	*	Descri��o:
	*		Retorna o vetor correspondente � matriz coluna. O vetor ter� tamanho igual
	*		ao n�mero de linhas da matriz. A matriz deve estar inicializada e possuir
	*		apenas uma coluna.
	*	Excess�es:
	*		MAT_NAO_INICIALIZADO	-	caso a matriz ainda n�o tenha sido inicializada
	*		MAT_TAM_INCONSISTENTE	-	caso a matriz n�o seja matriz coluna
	*********************************************************************************/
	std::vector<Type> CastToVec();

	/*********************************************************************************
	*	M�todo:
	*		Transpor
	*	Descri��o:
	*		Retorna a matriz transposta. A matriz deve estar inicializada.
	*	Excess�es:
	*		MAT_NAO_INICIALIZADO	-	caso a matriz ainda n�o tenha sido inicializada
	*********************************************************************************/
	matrix<Type> Transpose();

	//matrix<Type> Invert();

	/*********************************************************************************
	*	Operadores p�blicos
	*********************************************************************************/

	/*********************************************************************************
	*	M�todo:
	*		Operador []: matrix []
	*	Descri��o:
	*		Retorna uma refer�ncia da linha i (iniciando em 0) da matriz, como vetor.
	*		i deve ser uma linha v�lida. Se a matriz n�o estiver inicializada, essa
	*		opera��o a inicializa, pois a refer�ncia pode ser usada para alterar os
	*		valores da linha.
	*	Excess�es:
	*		MAT_VAL_INVALIDO	-	caso valor de i seja negativo ou maior ou igual �
	*								quantidade de linhas da matriz
	*********************************************************************************/
	std::vector<Type>& operator[](int i);

	/*********************************************************************************
	*	M�todo:
	*		Operador +: matrix + matrix
	*	Descri��o:
	*		Retorna a soma de duas matrizes. Ambas devem ter tamanhos compat�veis e estar
	*		inicializadas.
	*	Excess�es:
	*		MAT_NAO_INICIALIZADO	-	caso uma das matrizes ainda n�o tenha sido inicializada
	*		MAT_TAM_INCONSISTENTE	-	caso as matrizes n�o tenham dimens�es compat�veis
	*********************************************************************************/
	matrix<Type> operator+(matrix<Type>& B);

	/*********************************************************************************
	*	M�todo:
	*		Operador -: - matrix
	*	Descri��o:
	*		Retorna a matrizes com sinal inverso. A matriz deve estar inicializada.
	*	Excess�es:
	*		MAT_NAO_INICIALIZADO	-	caso a matriz ainda n�o tenha sido inicializada
	*********************************************************************************/
	matrix<Type> operator-();

	/*********************************************************************************
	*	M�todo:
	*		Operador -: matrix - matrix
	*	Descri��o:
	*		Retorna a subtra��o de duas matrizes. Ambas devem ter tamanhos compat�veis
	*		e estar inicializadas.
	*	Excess�es:
	*		MAT_NAO_INICIALIZADO	-	caso uma das matrizes ainda n�o tenha sido inicializada
	*		MAT_TAM_INCONSISTENTE	-	caso as matrizes n�o tenham dimens�es compat�veis
	*********************************************************************************/
	matrix<Type> operator-(matrix<Type>& B);

	/*********************************************************************************
	*	M�todo:
	*		Operador *: matrix * const
	*	Descri��o:
	*		Retorna a multiplica��o da matriz por uma constante. A matriz deve estar
	*		inicializada.
	*	Excess�es:
	*		MAT_NAO_INICIALIZADO	-	caso a matriz ainda n�o tenha sido inicializada
	*********************************************************************************/
	matrix<Type> operator*(const Type alpha);

	/*********************************************************************************
	*	M�todo:
	*		Operador *: matrix * matrix
	*	Descri��o:
	*		Retorna a multiplica��o de duas matrizes (a ordem importa). Ambas devem ter
	*		tamanhos compat�veis para multiplica��o (A*B => A.n = B.n) e estar inicializadas.
	*	Excess�es:
	*		MAT_NAO_INICIALIZADO	-	caso uma das matrizes ainda n�o tenha sido inicializada
	*		MAT_TAM_INCONSISTENTE	-	caso as matrizes n�o tenham dimens�es compat�veis
	*									para multiplica��o
	*********************************************************************************/
	matrix<Type> operator*(matrix<Type>& B);

	/*********************************************************************************
	*	Declara��es de fun��es amigas
	*********************************************************************************/
	friend std::ostream& operator<< <>(std::ostream& out, const matrix<Type>& A);
};	/* Fim da classe matrix */

/*********************************************************************************
*	Inclus�o do arquivo de defini��es de fun��es/m�todos template ou inline
*********************************************************************************/
#ifndef MATRIX_OWN
	/* Se MATRIX_OWN est� definido, ent�o o arquivo atual est� sendo incluido no
	pr�prio matrix.cpp e n�o deve inclu�-lo */
#include "matrix.cpp"
#endif