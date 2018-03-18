/*********************************************************************************
*	Módulo de Definição:
*		Matriz
*	Letras identificadoras:
*		MAT
*	Nome do arquivo de definição:
*		matrix.cpp
*	Arquivo de interface:
*		matrix.hpp
*	Projeto:
*		Simulador de fluxo experimental PUC-Rio
*	Desenvolvedores:
*		rrc	-	Rafael Rubim Cabral
*	Histórico de desenvolvimento:
*		Versão	-	Data		-	Comentários
*		1		-	23/05/17	-	Desenvolvimento de vários métodos básicos de
*									operações em matriz e arrumação de templates em
*									declarações/definições e documentação
*********************************************************************************/

/*********************************************************************************
*	Inclusão do arquivo de interface
*/
#define MATRIX_OWN
	/* O arquivo atual (matrix.cpp) define funções template/inline que deveriam ser
	definidas em um header file. Portanto, é incluído em seu arquivo de interface
	correspondente. A definição de MATRIX_OWN garante que a interface não incluirá
	este arquivo na seguinte inclusão. */
#include "matrix.hpp"
#undef MATRIX_OWN

/*********************************************************************************
*	ATENÇÃO	-	NÃO DEFINIR FUNÇÕES QUE NÃO SÃO TEMPLATE OU INLINE AQUI,
*				POIS ISSO PODE GERAR ERROS DE LINKER (DEFINIÇÃO MÚLTIPLA). SE UMA
*				FUNÇÃO DIFERENTE DESSAS CUJA DECLARAÇÃO ESTÁ NO ARQUIVO DE INTERFACE
*				(.H, .HPP RELACIONADO A ESTE ARQUIVO DE IMPLEMENTAÇÃO) PRECISAR SER
*				DEFINIDA, CRIAR UM ARQUIVO DE IMPLEMENTAÇÃO SECUNDÁRIO. ESSE AQUIVO
*				SECUNDÁRIO PODERÁ INCLUIR SUA INTERFACE NORMALMENTE (NÃO PRECISA
*				DEFINIR O MACRO _OWN) E AO FINAL DO ARQUIVO DE INTERFACE NÃO
*				HAVERÁ INCLUSÃO DELE (TAL COMO ESTE ARQUIVO É INCLUÍDO ENTRE DIRETIVAS
*				#IFNDEF)
*********************************************************************************/

/*********************************************************************************
*	ATENÇÃO	-	OS DADOS/FUNÇÕES ENCAPSULADOS NESSE MÓDULO NÃO ESTÃO DE FATO
*				ENCAPSULADOS! TRATAR COMO SE ESTIVESSEM NO HEADER, POIS ESTE ARQUIVO
*				É INCLUÍDO LÁ.
*********************************************************************************/

/*********************************************************************************
*	Inclusões de bibliotecas utilizadas
*********************************************************************************/

#include <string>
#include "raiseException.hpp"
using namespace std;

/*********************************************************************************
*	Dados encapsulados no módulo
*********************************************************************************/

/*********************************************************************************
*	Tipo de dados:	Tipo Excessão de matriz
*/
typedef enum enExcessaoMatrix {
	MAT_VAL_INVALIDO = 1,
		/* Função/método recebeu valor inválido */

	MAT_TAM_INVALIDO,
		/* Matriz recebida em template não possui dimensões consistentes com valores
		de m/n especificados */

	MAT_NAO_INICIALIZADO,
		/* Matriz não foi inicializada, não pode chamar o método/função */

	MAT_TAM_INCONSISTENTE,
		/* Matriz objeto não possui dimensões adequadas para o método/função chamado */

	MAT_INCONSISTENCIA
		/* Erro de inconsistência em algum código */
} tpExcessaoMatrix;	/* fim tipo de dados Excessão de matriz */

/*********************************************************************************
*	Interfaces de funções encapsuladas
*********************************************************************************/

static string ObterMsgErroMatrix(int excessao);

/*********************************************************************************
*	Definições de métodos privados
*********************************************************************************/

/*********************************************************************************
*	Método:	Assertar inicialização da matriz
*/
template <typename Type>
void matrix<Type>::AssertarInicializacao() {
	if (_initialized == false) {
		_error.CallException(MAT_NAO_INICIALIZADO);
	}	/* if */
}	/* fim método Assertar inicialização da matriz */

/*********************************************************************************
*	Definições de construtores
*********************************************************************************/

/*********************************************************************************
*	Construtor:	Construtor padrão, de dimensões
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
}	/* fim Construtor padrão, de dimensões */

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
*	Definições de métodos públicos
*********************************************************************************/

/*********************************************************************************
*	Método:	Atribuir
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
}	/* fim método Atribuir */


/*********************************************************************************
*	Método:	Obter m
*/
template <typename Type>
int matrix<Type>::GetM() {
	return _m;
}	/* fim método Obter m */

/*********************************************************************************
*	Método:	Obter n
*/
template <typename Type>
int matrix<Type>::GetN() {
	return _n;
}	/* fim método Obter n */

/*********************************************************************************
*	Método:	Obter linha
*/
template <typename Type>
vector<Type> matrix<Type>::GetLine(int i) {
	if (i < 0 || i >= _m) {
		_error.CallException(MAT_VAL_INVALIDO);
	}	/* if */
	AssertarInicializacao();
	return _buffer[i];
}	/* fim método Obter linha */

/*********************************************************************************
*	Método:	Converter para vetor
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
}	/* fim método Converter para vetor */

/*********************************************************************************
*	Método:	Transpor
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
}	/* fim método Transpor */

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
*	Definições de operadores públicos
*********************************************************************************/

/*********************************************************************************
*	Método:	Operador []: matrix []
*/
template <typename Type>
vector<Type>& matrix<Type>::operator[](int i) {
	if (i < 0 || i >= _m) {
		_error.CallException(MAT_VAL_INVALIDO);
	}	/* if */
	_initialized = true;
	return _buffer[i];
}	/* fim método Operador []: matrix [] */

/*********************************************************************************
*	Método:	Operador +: matrix + matrix
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
}	/* fim método Operador +: matrix + matrix */

/*********************************************************************************
*	Método:	Operador -: - matrix
*/
template <typename Type>
matrix<Type> matrix<Type>::operator-() {
	AssertarInicializacao();
	matrix<Type> C(_m, _n);
	for (int i = 0; i < _m; i++) {
		C[i] = -operator[](i);
	}	/* for */
	return C;
}	/* fim método Operador -: - matrix */

/*********************************************************************************
*	Método:	Operador -: matrix - matrix
*/
template <typename Type>
matrix<Type> matrix<Type>::operator-(matrix<Type>& B) {
	return operator+(-B);
}	/* fim método Operador -: matrix - matrix */

/*********************************************************************************
*	Método:	Operador *: matrix * const
*/
template <typename Type>
matrix<Type> matrix<Type>::operator*(const Type alpha) {
	AssertarInicializacao();
	matrix<Type> B(_m, _n);
	for (int i = 0; i < _m; i++) {
		B[i] = alpha * operator[](i);
	}	/* for */
	return B;
}	/* fim método Operador *: matrix * const */

/*********************************************************************************
*	Método:	Operador *: matrix * matrix
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
}	/* fim método Operador *: matrix * matrix */

/*********************************************************************************
*	Definições de funções exportadas pelo módulo
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
*	Definições de funções encapsuladas
*********************************************************************************/

/*********************************************************************************
*	Função:
*		Obter mensagem de erro em matriz
*	Descrição:
*		Recebe um inteiro que representa uma excessão do tipo tpExcessão e retorna
*		uma string que descreve uma mensagem de erro relativa a essa excessão.
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
}	/* fim função Obter mensagem erro em matriz */