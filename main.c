#include <stdio.h>
#include <stdlib.h>
#include "calculadoraComplexa.h"
#include <conio.h>

/*****************************************************
TRABALHO PRÁTICO 2 - CALCULADORA COMPLEXA REFATORADA
ALUNO: ALAN CÉSAR DE OLIVEIRA
TURMA: TF

DESCRIÇÃO: O trabalho prático 2 reformula a calculadora
complexa do TP1 com o código mais eficiente fazendo uso
de estruturas de dados, passagens de variáveis por
referência com o uso de ponteiros e modulzarização
de funções.
O trabalho prático 2 realiza a leitura das expressões
de complexos através de um arquivo texto e grava
as resposta em um arquivo texto de saída.
*****************************************************/

/*****************************************************
Função: Main
Entrada: void
Saída: void
Descrição: Faz a leitura do arquivo com as expressões
a serem executadas e armazena os resultados em um arquivo
de saída.
*****************************************************/
main()
{
	char *expressao, *resultado, *pergunta;
	char operacao;
	FILE *arquivoEntrada;
	FILE *arquivoSaida;
	Formato formatoOperacao = entrecomplexos;
	Complexo ComplexoUm;
	Complexo ComplexoDois;
	Complexo ComplexoResultado;

	arquivoEntrada = fopen(CAMINHOENTRADA, "r");
	if(arquivoEntrada == NULL){
		printf("Erro, nao foi possivel abrir o arquivo\nSecao abortada...");
		return;
	}


	arquivoSaida = fopen(CAMINHOSAIDA, "w");
	if(arquivoSaida == NULL){
		printf("Erro, nao foi possivel criar o arquivo\nSecao abortada...");
		return;
	}

	expressao = malloc(sizeof(char)*30);
	pergunta = malloc(sizeof(char)*30);

	//Loop de leitura
	while(fgets(expressao,30,arquivoEntrada) != NULL) //Lê a próxima expressão do arquivo se houver
	{
		validaExpressao(&formatoOperacao, expressao, &operacao, &ComplexoUm, &ComplexoDois);

		if(formatoOperacao != 3)
		{
			//Executa a operação referente à expressão
			resultado = malloc(sizeof(char)*40);  //Aloco memória para o resultado
			*(resultado+0) = NULL;
			*(resultado+1) = NULL;
			formataEntrada(&ComplexoUm, &ComplexoDois, pergunta, &operacao);
			executaOperacao(&ComplexoUm, &ComplexoDois, &ComplexoResultado, &operacao, resultado);

			//Escreve a pergunta na linha corrente e a resposta na frente
			fputs(pergunta, arquivoSaida);
			fputs(" ", arquivoSaida);
			fputs(resultado, arquivoSaida);
			fputc('\n', arquivoSaida);
		}
		else
		{
			fputs("ERRO!", arquivoSaida);
			fputc('\n', arquivoSaida);
		}
	}

	fclose(arquivoSaida);
	fclose(arquivoEntrada);

	free(expressao);
	free(resultado);
	free(pergunta);
}
