/*********************************************************************************
*	Módulo Interface:
*		Levantar Excessão
*	Nome do arquivo de inclusão:
*		raiseException.hpp
*	Arquivos de definição:
*		raiseException.cpp
*	Projeto:
*		Simulador de fluxo experimental PUC-Rio
*	Desenvolvedores:
*		rrc	-	Rafael Rubim Cabral
*	Histórico de desenvolvimento:
*		Versão	-	Data		-	Comentários
*		1		-	23/05/17	-	Desenvolvimento completo do módulo
*	Descrição do módulo:
*		Implementa a classe raiseException.
*		Essa classe disponibiliza um método que faz uma chamada I/O para imprimir
*			na saída de erro padrão (stderr) uma mensagem descrevendo um problema
*			ou excessão que ocorreu no módulo cliente e a linha/arquivo onde tal
*			erro ocorreu.
*		Para utilizar a classe raiseException, o módulo cliente deve definir suas
*			próprias excessões num tipo enumerado (ou um tipo convertível para
*			inteiro). O módulo cliente deve também definir uma função que recebe
*			um inteiro representando uma excessão e retorna uma string com a mensagem
*			relativa àquela excessão que se deseja imprimir.
*********************************************************************************/
#pragma once

/*********************************************************************************
*	Inclusões de bibliotecas utilizadas
*********************************************************************************/

#include <string>

/*********************************************************************************
*	Método:
*		CallException
*	Descrição:
*		O macro CallException deve ser tratado como um método da classe raiseException.
*		Ele recebe um número inteiro representando uma excessão do módulo cliente e
*			chama o método PrintException, automaticamente passando como parâmetro
*			a linha e arquivo de onde está sendo chamado.
*	Exemplo de uso no módulo cliente:
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
*	Definição de classe levantar excessão
*********************************************************************************/
class raiseException {
private:
	/*********************************************************************************
	*	Variáveis privadas
	*********************************************************************************/
	std::string(*_GetExceptionMsg)(int);
		/* Função implementada pelo usuário cliente que serve como "tabela" entre cada
		número de excessão e sua mensagem correspondente*/
public:
	/*********************************************************************************
	*	Construtores
	*********************************************************************************/

	/*********************************************************************************
	*	Construtor:
	*		Construtor padrão, de mensagens
	*	Descrição:
	*		Cria um objeto da classe raiseException. Esse objeto, em especial, conhecerá
	*			as mensagens que deverá imprimir dependendo de qual número de excessão
	*			receber. Esse "conhecimento" depende da função GetExceptionMsg, que é
	*			passada pelo cliente ao construtor. Essa função é implementada pelo cliente
	*			e deve, para cada número de excessão (também definido pelo cliente), retornar
	*			uma mensagem de erro relativa à tal instrução. Por padrão, se nenhuma
	*			função for passada ao construtor, uma chamada ao macro/método CallException
	*			sempre imprimirá EXCESSAO_DESCONHECIDA como mensagem.
	*********************************************************************************/
	raiseException(std::string(*GetExceptionMsg)(int) = NULL);

	/*********************************************************************************
	*	Métodos públicos
	*********************************************************************************/

	/* O macro CallException deve ser tratado como um método da classe. Sua documentação
	está acima da declaração do macro. */

	/*********************************************************************************
	*	Método:
	*		PrintException
	*	Descrição:
	*		Recebe um número inteiro representando uma excessão do módulo cliente, a
	*		linha e o arquivo onde ocorrem essa excessão. Esse método imprime o arquivo,
	*		a linha e uma mensagem de erro correspondente ao número de excessão recebido,
	*		conforme especificada pelo usuário. As mensagens de erro são especificadas
	*		pelo cliente no construtor do objeto, através do parâmetro GetExceptionMsg.
	*		Apesar deste método ser público, ele não deve ser diretamente chamado, mas
	*		chamado através do macro CallException, como se o nome do método fosse
	*		o macro em si e só o primeiro parâmetro existisse.
	*********************************************************************************/
	void PrintException(int exceptionNum, int line, const char* file);
};