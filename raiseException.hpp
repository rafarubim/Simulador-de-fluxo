/*********************************************************************************
*	M�dulo Interface:
*		Levantar Excess�o
*	Nome do arquivo de inclus�o:
*		raiseException.hpp
*	Arquivos de defini��o:
*		raiseException.cpp
*	Projeto:
*		Simulador de fluxo experimental PUC-Rio
*	Desenvolvedores:
*		rrc	-	Rafael Rubim Cabral
*	Hist�rico de desenvolvimento:
*		Vers�o	-	Data		-	Coment�rios
*		1		-	23/05/17	-	Desenvolvimento completo do m�dulo
*	Descri��o do m�dulo:
*		Implementa a classe raiseException.
*		Essa classe disponibiliza um m�todo que faz uma chamada I/O para imprimir
*			na sa�da de erro padr�o (stderr) uma mensagem descrevendo um problema
*			ou excess�o que ocorreu no m�dulo cliente e a linha/arquivo onde tal
*			erro ocorreu.
*		Para utilizar a classe raiseException, o m�dulo cliente deve definir suas
*			pr�prias excess�es num tipo enumerado (ou um tipo convert�vel para
*			inteiro). O m�dulo cliente deve tamb�m definir uma fun��o que recebe
*			um inteiro representando uma excess�o e retorna uma string com a mensagem
*			relativa �quela excess�o que se deseja imprimir.
*********************************************************************************/
#pragma once

/*********************************************************************************
*	Inclus�es de bibliotecas utilizadas
*********************************************************************************/

#include <string>

/*********************************************************************************
*	M�todo:
*		CallException
*	Descri��o:
*		O macro CallException deve ser tratado como um m�todo da classe raiseException.
*		Ele recebe um n�mero inteiro representando uma excess�o do m�dulo cliente e
*			chama o m�todo PrintException, automaticamente passando como par�metro
*			a linha e arquivo de onde est� sendo chamado.
*	Exemplo de uso no m�dulo cliente:
*		{
*			raiseExeption excessao(MensagensExcessao);
*			[...]
*			if (EXCESSAO_DETECTADA) {
*				excessao.CallException(NUMERO_DA_EXCESSAO);
*			}
*			[...]
*		}
*********************************************************************************/
#define CallException(exception) PrintException((int) exception, __LINE__, __FILE__)

/*********************************************************************************
*	Defini��o de classe levantar excess�o
*********************************************************************************/
class raiseException {
private:
	/*********************************************************************************
	*	Vari�veis privadas
	*********************************************************************************/
	std::string(*_GetExceptionMsg)(int);
		/* Fun��o implementada pelo usu�rio cliente que serve como "tabela" entre cada
		n�mero de excess�o e sua mensagem correspondente*/
public:
	/*********************************************************************************
	*	Construtores
	*********************************************************************************/

	/*********************************************************************************
	*	Construtor:
	*		Construtor padr�o, de mensagens
	*	Descri��o:
	*		Cria um objeto da classe raiseException. Esse objeto, em especial, conhecer�
	*			as mensagens que dever� imprimir dependendo de qual n�mero de excess�o
	*			receber. Esse "conhecimento" depende da fun��o GetExceptionMsg, que �
	*			passada pelo cliente ao construtor. Essa fun��o � implementada pelo cliente
	*			e deve, para cada n�mero de excess�o (tamb�m definido pelo cliente), retornar
	*			uma mensagem de erro relativa � tal instru��o. Por padr�o, se nenhuma
	*			fun��o for passada ao construtor, uma chamada ao macro/m�todo CallException
	*			sempre imprimir� EXCESSAO_DESCONHECIDA como mensagem.
	*********************************************************************************/
	raiseException(std::string(*GetExceptionMsg)(int) = NULL);

	/*********************************************************************************
	*	M�todos p�blicos
	*********************************************************************************/

	/* O macro CallException deve ser tratado como um m�todo da classe. Sua documenta��o
	est� acima da declara��o do macro. */

	/*********************************************************************************
	*	M�todo:
	*		PrintException
	*	Descri��o:
	*		Recebe um n�mero inteiro representando uma excess�o do m�dulo cliente, a
	*		linha e o arquivo onde ocorrem essa excess�o. Esse m�todo imprime o arquivo,
	*		a linha e uma mensagem de erro correspondente ao n�mero de excess�o recebido,
	*		conforme especificada pelo usu�rio. As mensagens de erro s�o especificadas
	*		pelo cliente no construtor do objeto, atrav�s do par�metro GetExceptionMsg.
	*		Apesar deste m�todo ser p�blico, ele n�o deve ser diretamente chamado, mas
	*		chamado atrav�s do macro CallException, como se o nome do m�todo fosse
	*		o macro em si e s� o primeiro par�metro existisse.
	*********************************************************************************/
	void PrintException(int exceptionNum, int line, const char* file);
};