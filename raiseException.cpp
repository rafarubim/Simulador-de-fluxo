/*********************************************************************************
*	M�dulo de defini��o:
*		Levantar Excess�o
*	Nome do arquivo de defini��o:
*		raiseException.cpp
*	Arquivo de interface:
*		raiseException.hpp
*	Projeto:
*		Simulador de fluxo experimental PUC-Rio
*	Desenvolvedores:
*		rrc	-	Rafael Rubim Cabral
*	Hist�rico de desenvolvimento:
*		Vers�o	-	Data		-	Coment�rios
*		1		-	23/05/17	-	Desenvolvimento completo do m�dulo
*********************************************************************************/

/*********************************************************************************
*	Inclus�o do arquivo de interface
*********************************************************************************/

#include "raiseException.hpp"

/*********************************************************************************
*	Inclus�es de bibliotecas utilizadas
*********************************************************************************/

#include <string>
#include <iostream>
using namespace std;

/*********************************************************************************
*	Interfaces de fun��es encapsuladas
*********************************************************************************/

static string msgPadrao(int);

/*********************************************************************************
*	Defini��es de construtores
*********************************************************************************/

/*********************************************************************************
*	Construtor:	Construtor padr�o, de mensagens
*/
raiseException::raiseException(std::string(*GetExceptionMsg)(int)) {
	if (GetExceptionMsg != NULL) {
		_GetExceptionMsg = GetExceptionMsg;
	}
	else {
		_GetExceptionMsg = msgPadrao;
	}	/* if */
}	/* fim construtor padr�o, de mensagens */

/*********************************************************************************
*	Defini��es de m�todos p�blicos
*********************************************************************************/

/*********************************************************************************
*	M�todo:	Imprimir excess�o
*/
void raiseException::PrintException(int exceptionNum, int line, const char* file) {
	string errorMsg;
	errorMsg = _GetExceptionMsg(exceptionNum);
	cerr << "Excessao encontrada!\nArquivo: " << file << "\nLinha: " << line;
	cerr << "\nMensagem: " << errorMsg << endl;
	exit(exceptionNum);
}	/* fim m�todo imprimir excess�o */

/*********************************************************************************
*	Defini��es de fun��es encapsuladas
*********************************************************************************/

/*********************************************************************************
*	Fun��o:
*		Mensagem padr�o
*	Descri��o:
*		Independente do que receber, retorna sempre a string "EXCESSAO_DESCONHECIDA"
*********************************************************************************/
static string msgPadrao(int) {
	return string("EXCESSAO_DESCONHECIDA");
}	/* fim fun��o mensagem padr�o */