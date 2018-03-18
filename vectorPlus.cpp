/*********************************************************************************
*	M�dulo de defini��o:
*		Adicionais de vetor
*	Letras identificadoras:
*		VECP
*	Nome do arquivo de defini��o:
*		vectorPlus.cpp
*	Arquivo de interface:
*		vectorPlus.hpp
*	Projeto:
*		Simulador de fluxo experimental PUC-Rio
*	Desenvolvedores:
*		rrc	-	Rafael Rubim Cabral
*	Hist�rico de desenvolvimento:
*		Vers�o	-	Data		-	Coment�rios
*		1		-	24/05/17	-	Desenvolvimento de v�rias opera��es b�sicas
*									de sobrecarga e impress�o por iostream.
*********************************************************************************/

/*********************************************************************************
*	Inclus�o do arquivo de interface
*/

#define VECTORPLUS_OWN
/* O arquivo atual (vectorPlus.cpp) define fun��es template/inline que deveriam ser
definidas em um header file. Portanto, � inclu�do em seu arquivo de interface
correspondente. A defini��o de VECTORPLUS_OWN garante que a interface n�o incluir�
este arquivo na seguinte inclus�o. */
#include "vectorPlus.hpp"
#undef VECTORPLUS_OWN

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

#include <vector>
#include <string>
#include "raiseException.hpp"
using namespace std;

/*********************************************************************************
*	Dados encapsulados no m�dulo
*********************************************************************************/

/*********************************************************************************
*	Tipo de dados:	Tipo Excess�o de adicionais de vetor
*/
typedef enum enExcessaoVectorPlus {
	VECP_TAM_INCONSISTENTE = 1
	/* Vetor n�o possui dimens�es adequadas para fun��o chamada */
} tpExcessaoVectorPlus;	/* fim tipo de dados Excess�o de adicionais de vetor */

/*********************************************************************************
*	Interfaces de fun��es encapsuladas
*********************************************************************************/

static string ObterMsgErroVectorPlus(int excessao);
static raiseException _error();

/*********************************************************************************
*	Defini��es de fun��es exportadas pelo m�dulo
*********************************************************************************/

/*********************************************************************************
*	Fun��o:	Operador <<: ostream << vector
*/
template <typename Type>
std::ostream& operator<<(std::ostream& out, const vector<Type> vec) {
	unsigned int n = vec.size();
	for (unsigned int i = 0; i < n; i++) {
		out << vec[i];
		if (i < n - 1) {
			out << "\t";
		}	/* if */
	}	/* for */
	return out;
}	/* fim fun��o Operador <<: ostream << vector */

/*********************************************************************************
*	Fun��o:	Operador +: vector + vector
*/
template <typename Type>
std::vector<Type> operator+(std::vector<Type> a, std::vector<Type> b) {
	int n = a.size();
	if (n != b.size()) {
		_error().CallException(VECP_TAM_INCONSISTENTE);
	}
	vector<Type> c(n);
	for (int i = 0; i < n; i++) {
		c[i] = a[i] + b[i];
	}	/* for */
	return c;
}	/* fim fun��o Operador +: vector + vector */

/*********************************************************************************
*	Fun��o:	Operador -: - vector
*/
template <typename Type>
std::vector<Type> operator-(std::vector<Type> a) {
	int n = a.size();
	vector<Type> b(n);
	for (int i = 0; i < n; i++) {
		b[i] = -a[i];
	}	/* for */
	return b;
}	/* fim fun��o Operador -: - vector */

/*********************************************************************************
*	Fun��o:	Operador -: vector - vector
*/
template <typename Type>
std::vector<Type> operator-(std::vector<Type> a, std::vector<Type> b) {
	vector<Type> c;
	c = a + (-b);
	return c;
}	/* fim fun��o Operador -: vector - vector */

/*********************************************************************************
*	Fun��o:	Operador *: const * vector
*/
template <typename Type>
std::vector<Type> operator*(const Type alpha, std::vector<Type> a) {
	int n = a.size();
	vector<Type> b(n);
	for (int i = 0; i < n; i++) {
		b[i] = alpha * a[i];
	}	/* for */
	return b;
}	/* fim fun��o Operador *: const * vector */

/*********************************************************************************
*	Fun��o:	Operador *: vector * const
*/
template <typename Type>
std::vector<Type> operator*(std::vector<Type> a, const Type alpha) {
	return alpha * a;
}	/* fim fun��o Operador *: vector * const */

/*********************************************************************************
*	Defini��es de fun��es encapsuladas
*********************************************************************************/

/*********************************************************************************
*	Fun��o:
*		Obter mensagem de erro em adicionais de vetor
*	Descri��o:
*		Recebe um inteiro que representa uma excess�o do tipo tpExcess�o e retorna
*		uma string que descreve uma mensagem de erro relativa a essa excess�o.
*********************************************************************************/
static string ObterMsgErroVectorPlus(int excessao) {
	string str;
	switch ((tpExcessaoVectorPlus)excessao) {
	case VECP_TAM_INCONSISTENTE:
		str = "O vetor nao possui dimensoes adequadas";
		break;
	default:
		str = "EXCESSAO_DESCONHECIDA";
		break;
	}	/* switch */
	return str;
}	/* fim fun��o Obter mensagem erro em adicionais de vetor */

/*********************************************************************************
*	Fun��o:
*		_error
*	Descri��o:
*		Retorna um objeto raiseException j� inicializado conforme necess�rio neste
*		m�dulo.
*********************************************************************************/
static raiseException _error() {
	return raiseException(ObterMsgErroVectorPlus);
}	/* fim fun��o _error */