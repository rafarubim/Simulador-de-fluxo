/*********************************************************************************
*	Módulo de definição:
*		Adicionais de vetor
*	Letras identificadoras:
*		VECP
*	Nome do arquivo de definição:
*		vectorPlus.cpp
*	Arquivo de interface:
*		vectorPlus.hpp
*	Projeto:
*		Simulador de fluxo experimental PUC-Rio
*	Desenvolvedores:
*		rrc	-	Rafael Rubim Cabral
*	Histórico de desenvolvimento:
*		Versão	-	Data		-	Comentários
*		1		-	24/05/17	-	Desenvolvimento de várias operações básicas
*									de sobrecarga e impressão por iostream.
*********************************************************************************/

/*********************************************************************************
*	Inclusão do arquivo de interface
*/

#define VECTORPLUS_OWN
/* O arquivo atual (vectorPlus.cpp) define funções template/inline que deveriam ser
definidas em um header file. Portanto, é incluído em seu arquivo de interface
correspondente. A definição de VECTORPLUS_OWN garante que a interface não incluirá
este arquivo na seguinte inclusão. */
#include "vectorPlus.hpp"
#undef VECTORPLUS_OWN

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

#include <vector>
#include <string>
#include "raiseException.hpp"
using namespace std;

/*********************************************************************************
*	Dados encapsulados no módulo
*********************************************************************************/

/*********************************************************************************
*	Tipo de dados:	Tipo Excessão de adicionais de vetor
*/
typedef enum enExcessaoVectorPlus {
	VECP_TAM_INCONSISTENTE = 1
	/* Vetor não possui dimensões adequadas para função chamada */
} tpExcessaoVectorPlus;	/* fim tipo de dados Excessão de adicionais de vetor */

/*********************************************************************************
*	Interfaces de funções encapsuladas
*********************************************************************************/

static string ObterMsgErroVectorPlus(int excessao);
static raiseException _error();

/*********************************************************************************
*	Definições de funções exportadas pelo módulo
*********************************************************************************/

/*********************************************************************************
*	Função:	Operador <<: ostream << vector
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
}	/* fim função Operador <<: ostream << vector */

/*********************************************************************************
*	Função:	Operador +: vector + vector
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
}	/* fim função Operador +: vector + vector */

/*********************************************************************************
*	Função:	Operador -: - vector
*/
template <typename Type>
std::vector<Type> operator-(std::vector<Type> a) {
	int n = a.size();
	vector<Type> b(n);
	for (int i = 0; i < n; i++) {
		b[i] = -a[i];
	}	/* for */
	return b;
}	/* fim função Operador -: - vector */

/*********************************************************************************
*	Função:	Operador -: vector - vector
*/
template <typename Type>
std::vector<Type> operator-(std::vector<Type> a, std::vector<Type> b) {
	vector<Type> c;
	c = a + (-b);
	return c;
}	/* fim função Operador -: vector - vector */

/*********************************************************************************
*	Função:	Operador *: const * vector
*/
template <typename Type>
std::vector<Type> operator*(const Type alpha, std::vector<Type> a) {
	int n = a.size();
	vector<Type> b(n);
	for (int i = 0; i < n; i++) {
		b[i] = alpha * a[i];
	}	/* for */
	return b;
}	/* fim função Operador *: const * vector */

/*********************************************************************************
*	Função:	Operador *: vector * const
*/
template <typename Type>
std::vector<Type> operator*(std::vector<Type> a, const Type alpha) {
	return alpha * a;
}	/* fim função Operador *: vector * const */

/*********************************************************************************
*	Definições de funções encapsuladas
*********************************************************************************/

/*********************************************************************************
*	Função:
*		Obter mensagem de erro em adicionais de vetor
*	Descrição:
*		Recebe um inteiro que representa uma excessão do tipo tpExcessão e retorna
*		uma string que descreve uma mensagem de erro relativa a essa excessão.
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
}	/* fim função Obter mensagem erro em adicionais de vetor */

/*********************************************************************************
*	Função:
*		_error
*	Descrição:
*		Retorna um objeto raiseException já inicializado conforme necessário neste
*		módulo.
*********************************************************************************/
static raiseException _error() {
	return raiseException(ObterMsgErroVectorPlus);
}	/* fim função _error */