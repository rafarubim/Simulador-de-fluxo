/*********************************************************************************
*	M�dulo de Defini��o:
*		Matriz
*	Letras identificadoras:
*		MAT
*	Nome do arquivo de defini��o:
*		matrix.cpp
*	Arquivo de interface:
*		matrix.hpp
*	Projeto:
*		Simulador de fluxo experimental PUC-Rio
*	Desenvolvedores:
*		rrc	-	Rafael Rubim Cabral
*	Hist�rico de desenvolvimento:
*		Vers�o	-	Data		-	Coment�rios
*		1		-	23/05/17	-	Desenvolvimento de v�rios m�todos b�sicos de
*									opera��es em matriz e arruma��o de templates em
*									declara��es/defini��es e documenta��o
*********************************************************************************/

/*********************************************************************************
*	Inclus�o do arquivo de interface
*/
#define MATRIX_OWN
	/* O arquivo atual (matrix.cpp) define fun��es template/inline que deveriam ser
	definidas em um header file. Portanto, � inclu�do em seu arquivo de interface
	correspondente. A defini��o de MATRIX_OWN garante que a interface n�o incluir�
	este arquivo na seguinte inclus�o. */
#include "matrix.hpp"
#undef MATRIX_OWN

/*********************************************************************************
*	ATEN��O	-	N�O DEFINIR FUN��ES QUE N�O S�O TEMPLATE OU INLINE AQUI,
*				POIS ISSO PODE GERAR ERROS DE LINKER (DEFINI��O M�LTIPLA). SE UMA
*				FUN��O DIFERENTE DESSAS CUJA DECLARA��O EST� NO ARQUIVO DE INTERFACE
*				(.H, .HPP RELACIONADO A ESTE ARQUIVO DE IMPLEMENTA��O) PRECISAR SER
*				DEFINIDA, CRIAR UM ARQUIVO DE IMPLEMENTA��O SECUND�RIO. ESSE AQUIVO
*				SECUND�RIO PODER� INCLUIR SUA INTERFACE NORMALMENTE (N�O PRECISA
*				DEFINIR O MACRO _OWN) E AO FINAL DO ARQUIVO DE INTERFACE N�O
*				HAVER� INCLUS�O DELE (TAL COMO ESTE ARQUIVO � INCLU�DO ENTRE DIRETIVAS
*				#IFNDEF)
*********************************************************************************/

/*********************************************************************************
*	ATEN��O	-	OS DADOS/FUN��ES ENCAPSULADOS NESSE M�DULO N�O EST�O DE FATO
*				ENCAPSULADOS! TRATAR COMO SE ESTIVESSEM NO HEADER, POIS ESTE ARQUIVO
*				� INCLU�DO L�.
*********************************************************************************/

/*********************************************************************************
*	Inclus�es de bibliotecas utilizadas
*********************************************************************************/

#include <string>
#include "raiseException.hpp"
using namespace std;

/*********************************************************************************
*	Dados encapsulados no m�dulo
*********************************************************************************/

/*********************************************************************************
*	Tipo de dados:	Tipo Excess�o de matriz
*/
typedef enum enExcessaoMatrix {
	MAT_VAL_INVALIDO = 1,
		/* Fun��o/m�todo recebeu valor inv�lido */

	MAT_TAM_INVALIDO,
		/* Matriz recebida em template n�o possui dimens�es consistentes com valores
		de m/n especificados */

	MAT_NAO_INICIALIZADO,
		/* Matriz n�o foi inicializada, n�o pode chamar o m�todo/fun��o */

	MAT_TAM_INCONSISTENTE,
		/* Matriz objeto n�o possui dimens�es adequadas para o m�todo/fun��o chamado */

	MAT_INCONSISTENCIA
		/* Erro de inconsist�ncia em algum c�digo */
} tpExcessaoMatrix;	/* fim tipo de dados Excess�o de matriz */

/*********************************************************************************
*	Interfaces de fun��es encapsuladas
*********************************************************************************/

static string ObterMsgErroMatrix(int excessao);

/*********************************************************************************
*	Defini��es de m�todos privados
*********************************************************************************/

/*********************************************************************************
*	M�todo:	Assertar inicializa��o da matriz
*/
template <typename Type>
void matrix<Type>::AssertarInicializacao() {
	if (_initialized == false) {
		_error.CallException(MAT_NAO_INICIALIZADO);
	}	/* if */
}	/* fim m�todo Assertar inicializa��o da matriz */

/*********************************************************************************
*	Defini��es de construtores
*********************************************************************************/

/*********************************************************************************
*	Construtor:	Construtor padr�o, de dimens�es
*/
template <typename Type>
matrix<Type>::matrix(int m, int n) : _error(ObterMsgErroMatrix) {
	_initialized = false;
	if (m < 0 || n < 0) {
		_error.CallException(MAT_VAL_INVALIDO);
	}	/* if */
	_m = m;
	_n = n;
	for (int i = 0; i < m; i++) {
		vector<Type> row(n);
		_buffer.push_back(row);
	}	/* for */
}	/* fim Construtor padr�o, de dimens�es */

/*********************************************************************************
*	Construtor:	Construtor de vetor
*/
template <typename Type>
matrix<Type>::matrix(vector<Type> v) : _error(ObterMsgErroMatrix) {
	_m = v.size();
	_n = 1;
	for (int i = 0; i < _m; i++) {
		vector<Type> row(1);
		row.assign(1, v[i]);
		_buffer.push_back(row);
	}	/* for */
	_initialized = true;
}	/* fim Construtor de vetor */

/*********************************************************************************
*	Defini��es de m�todos p�blicos
*********************************************************************************/

/*********************************************************************************
*	M�todo:	Atribuir
*/
template <typename Type>
template <unsigned COL>
void matrix<Type>::Assign(int m, int n, Type mat[][COL]) {
	if (n != COL) {
		_error.CallException(MAT_TAM_INVALIDO);
	}	/* if */
	if (m <= 0 || n <= 0) {
		_error.CallException(MAT_VAL_INVALIDO);
	}	/* if */
	*this = matrix<Type>(m, n);
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			operator[](i)[j] = mat[i][j];
		}	/* for */
	}	/* for */
	_initialized = true;
}	/* fim m�todo Atribuir */


/*********************************************************************************
*	M�todo:	Obter m
*/
template <typename Type>
int matrix<Type>::GetM() {
	return _m;
}	/* fim m�todo Obter m */

/*********************************************************************************
*	M�todo:	Obter n
*/
template <typename Type>
int matrix<Type>::GetN() {
	return _n;
}	/* fim m�todo Obter n */

/*********************************************************************************
*	M�todo:	Obter linha
*/
template <typename Type>
vector<Type> matrix<Type>::GetLine(int i) {
	if (i < 0 || i >= _m) {
		_error.CallException(MAT_VAL_INVALIDO);
	}	/* if */
	AssertarInicializacao();
	return _buffer[i];
}	/* fim m�todo Obter linha */

/*********************************************************************************
*	M�todo:	Converter para vetor
*/
template <typename Type>
vector<Type> matrix<Type>::CastToVec() {
	AssertarInicializacao();
	if (_n != 1) {
		_error.CallException(MAT_TAM_INCONSISTENTE);
	}
	vector<Type> vec;
	for (int i = 0; i < _m; i++) {
		vec.push_back(operator[](i)[0]);
	}	/* for */
	return vec;
}	/* fim m�todo Converter para vetor */

/*********************************************************************************
*	M�todo:	Transpor
*/
template <typename Type>
matrix<Type> matrix<Type>::Transpose() {
	AssertarInicializacao();
	matrix<Type> B(_n, _m);
	for (int i = 0; i < _n; i++) {
		for (int j = 0; j < _m; j++) {
			B[i][j] = operator[](j)[i];
		}	/* for */
	}	/* for */
	return B;
}	/* fim m�todo Transpor */

//template <typename Type>
//matrix<Type> matrix<Type>::Invert() {
//	matrix<float> A;
//	operator[](i)[j];
//	for (int i = 0; i < A.m(); i++) {
//		for (int j = i + 1; j < A.m(); j++) {
//			float fator = * operator[](j)[i] / operator[](i)[i];
//
//		}
//	}
//}

/*********************************************************************************
*	Defini��es de operadores p�blicos
*********************************************************************************/

/*********************************************************************************
*	M�todo:	Operador []: matrix []
*/
template <typename Type>
vector<Type>& matrix<Type>::operator[](int i) {
	if (i < 0 || i >= _m) {
		_error.CallException(MAT_VAL_INVALIDO);
	}	/* if */
	_initialized = true;
	return _buffer[i];
}	/* fim m�todo Operador []: matrix [] */

/*********************************************************************************
*	M�todo:	Operador +: matrix + matrix
*/
template <typename Type>
matrix<Type> matrix<Type>::operator+(matrix<Type>& B) {
	AssertarInicializacao();
	B.AssertarInicializacao();
	if (_m != B._m || _n != B._n) {
		_error.CallException(MAT_TAM_INCONSISTENTE);
	}	/* if */
	matrix<Type> C(_m, _n);
	for (int i = 0; i < _m; i++) {
		C[i] = operator[](i) + B[i];
	}	/* for */
	return C;
}	/* fim m�todo Operador +: matrix + matrix */

/*********************************************************************************
*	M�todo:	Operador -: - matrix
*/
template <typename Type>
matrix<Type> matrix<Type>::operator-() {
	AssertarInicializacao();
	matrix<Type> C(_m, _n);
	for (int i = 0; i < _m; i++) {
		C[i] = -operator[](i);
	}	/* for */
	return C;
}	/* fim m�todo Operador -: - matrix */

/*********************************************************************************
*	M�todo:	Operador -: matrix - matrix
*/
template <typename Type>
matrix<Type> matrix<Type>::operator-(matrix<Type>& B) {
	return operator+(-B);
}	/* fim m�todo Operador -: matrix - matrix */

/*********************************************************************************
*	M�todo:	Operador *: matrix * const
*/
template <typename Type>
matrix<Type> matrix<Type>::operator*(const Type alpha) {
	AssertarInicializacao();
	matrix<Type> B(_m, _n);
	for (int i = 0; i < _m; i++) {
		B[i] = alpha * operator[](i);
	}	/* for */
	return B;
}	/* fim m�todo Operador *: matrix * const */

/*********************************************************************************
*	M�todo:	Operador *: matrix * matrix
*/
template <typename Type>
matrix<Type> matrix<Type>::operator*(matrix<Type>& B) {
	AssertarInicializacao();
	B.AssertarInicializacao();
	matrix<Type> C(_m, B._n);
	if (_n <= 0) {
		_error.CallException(MAT_INCONSISTENCIA);
	}
	if (_n != B._m) {
		_error.CallException(MAT_TAM_INCONSISTENTE);
	}
	for (int i = 0; i < _m; i++) {
		for (int j = 0; j < B._n; j++) {
			Type sum = operator[](i)[0] * B[0][j];
			for (int k = 1; k < _n; k++) {
				sum = sum + (operator[](i)[k] * B[k][j]);
			}	/* for */
			C[i][j] = sum;
		}	/* for */
	}	/* for */
	return C;
}	/* fim m�todo Operador *: matrix * matrix */

/*********************************************************************************
*	Defini��es de fun��es exportadas pelo m�dulo
*********************************************************************************/

template <typename Type>
std::ostream& operator<<(std::ostream& out, const matrix<Type>& A) {
	int m = A._m;
	int n = A._n;
	for (int i = 0; i < m; i++) {
		out << (A._buffer[i]);
		if (i < m - 1) {
			out << endl;
		}
	}
	return out;
}

template <typename Type>
matrix<Type> operator*(const Type alpha, matrix<Type> A) {
	return A.operator*(alpha);
}

/*********************************************************************************
*	Defini��es de fun��es encapsuladas
*********************************************************************************/

/*********************************************************************************
*	Fun��o:
*		Obter mensagem de erro em matriz
*	Descri��o:
*		Recebe um inteiro que representa uma excess�o do tipo tpExcess�o e retorna
*		uma string que descreve uma mensagem de erro relativa a essa excess�o.
*********************************************************************************/
static string ObterMsgErroMatrix(int excessao) {
	string str;
	switch ((tpExcessaoMatrix)excessao) {
	case MAT_VAL_INVALIDO:
		str = "Parametro contem valor invalido";
		break;
	case MAT_TAM_INVALIDO:
		str = "Dimensoes de matriz passada eh diferente do numero de linhas/colunas especificado";
		break;
	case MAT_NAO_INICIALIZADO:
		str = "A matriz ainda nao foi inicializada";
		break;
	case MAT_TAM_INCONSISTENTE:
		str = "A matriz nao possui dimensoes adequadas";
		break;
	case MAT_INCONSISTENCIA:
		str = "Inconsistencia encontrada em codigo do programa";
		break;
	default:
		str = "EXCESSAO_DESCONHECIDA";
		break;
	}	/* switch */
	return str;
}	/* fim fun��o Obter mensagem erro em matriz */