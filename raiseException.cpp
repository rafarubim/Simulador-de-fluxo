/*********************************************************************************
*	Módulo de definição:
*		Levantar Excessão
*	Nome do arquivo de definição:
*		raiseException.cpp
*	Arquivo de interface:
*		raiseException.hpp
*	Projeto:
*		Simulador de fluxo experimental PUC-Rio
*	Desenvolvedores:
*		rrc	-	Rafael Rubim Cabral
*	Histórico de desenvolvimento:
*		Versão	-	Data		-	Comentários
*		1		-	23/05/17	-	Desenvolvimento completo do módulo
*********************************************************************************/

/*********************************************************************************
*	Inclusão do arquivo de interface
*********************************************************************************/

#include "raiseException.hpp"

/*********************************************************************************
*	Inclusões de bibliotecas utilizadas
*********************************************************************************/

#include <string>
#include <iostream>
using namespace std;

/*********************************************************************************
*	Interfaces de funções encapsuladas
*********************************************************************************/

static string msgPadrao(int);

/*********************************************************************************
*	Definições de construtores
*********************************************************************************/

/*********************************************************************************
*	Construtor:	Construtor padrão, de mensagens
*/
raiseException::raiseException(std::string(*GetExceptionMsg)(int)) {
	if (GetExceptionMsg != NULL) {
		_GetExceptionMsg = GetExceptionMsg;
	}
	else {
		_GetExceptionMsg = msgPadrao;
	}	/* if */
}	/* fim construtor padrão, de mensagens */

/*********************************************************************************
*	Definições de métodos públicos
*********************************************************************************/

/*********************************************************************************
*	Método:	Imprimir excessão
*/
void raiseException::PrintException(int exceptionNum, int line, const char* file) {
	string errorMsg;
	errorMsg = _GetExceptionMsg(exceptionNum);
	cerr << "Excessao encontrada!\nArquivo: " << file << "\nLinha: " << line;
	cerr << "\nMensagem: " << errorMsg << endl;
	exit(exceptionNum);
}	/* fim método imprimir excessão */

/*********************************************************************************
*	Definições de funções encapsuladas
*********************************************************************************/

/*********************************************************************************
*	Função:
*		Mensagem padrão
*	Descrição:
*		Independente do que receber, retorna sempre a string "EXCESSAO_DESCONHECIDA"
*********************************************************************************/
static string msgPadrao(int) {
	return string("EXCESSAO_DESCONHECIDA");
}	/* fim função mensagem padrão */