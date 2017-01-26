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
main(){

    //Declaração de variáveis
    char *expressao, *resultado, *pergunta;
    char operacao;
    FILE *arquivoEntrada;
    FILE *arquivoSaida;
    Formato formatoOperacao = entrecomplexos;
    Complexo ComplexoUm;
    Complexo ComplexoDois;
    Complexo ComplexoResultado;

    //Abre arquivo a ser lido
    arquivoEntrada = fopen(CAMINHOENTRADA, "r");
	if(arquivoEntrada == NULL){
	    printf("Erro, nao foi possivel abrir o arquivo\nSecao abortada...");
	    return;
	}

    //Abre arquivo a ser gravado
	arquivoSaida = fopen(CAMINHOSAIDA, "w");
	if(arquivoSaida == NULL){
	    printf("Erro, nao foi possivel criar o arquivo\nSecao abortada...");
	    return;
	}
    //Aloca memória para o vetor que armazena a expressão
    expressao = malloc(sizeof(char)*30);
    pergunta = malloc(sizeof(char)*30);

    //Entra no loop de leitura
    while(fgets(expressao,30,arquivoEntrada) != NULL){ //Lê a próxima expressão do arquivo se houver
        //Valida a expressão corrente e converte para número (tipo float) caso não haja erro
        validaExpressao(&formatoOperacao, expressao, &operacao, &ComplexoUm, &ComplexoDois);

        if(formatoOperacao != 3){   //Se não houver erro na expressão
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
            fputc('\n', arquivoSaida);  //Coloca caractere '\n' para saltar para próxima linha
        }
        else{
            //Escreve mensagem de erro no arquivo
            fputs("ERRO!", arquivoSaida);
            fputc('\n', arquivoSaida);
        }
    }
    //Fecha os arquivos
    fclose(arquivoSaida);
    fclose(arquivoEntrada);

    //Libera os ponteiros
    free(expressao);
    free(resultado);
    free(pergunta);
}
