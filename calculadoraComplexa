#ifndef CALCULADORACOMPLEXA_H_INCLUDED
#define CALCULADORACOMPLEXA_H_INCLUDED

#define PI 3.1428
#define CAMINHOENTRADA "entrada.txt"
#define CAMINHOSAIDA "saida.txt"

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
Tipo Complexo
Estrutura que armazena as informações de um número
complexo na forma:
'operador1' 'operando1' 'operador2' 'operando2' 'tipo'
que corresponde, por exemplo, a: '2' '+' '4' 'i'
*****************************************************/
typedef struct {
        float operando1;
        float operando2;
        char tipo;
    }Complexo;

/*****************************************************
Enumeração Formato
Agrupa os formatos que podem ter as expressões matemáticas
entre números complexos:
        conversao;
        exponenciacao;
        entrecomplexos;
        erro.
*****************************************************/
typedef enum {conversao,
            exponenciacao,
            entrecomplexos,
            erro}Formato;

/*****************************************************
Função: void formataEntrada(Complexo *,Complexo *, char *, char *)
Entrada: Complexo *,Complexo *, Complexo *, char *, char *
ComplexoUm -> Número complexo 1 a ser armazenado da expressão
ComplexoDois -> Número complexo 2 a ser armazenado da expressão
char *expressao -> ponteiro para a expressao a ser validada.
char operacao -> armazena a operação pedida na expressao:
                +,-,/,*,^,c. Sendo que 'c' é de conversão.
Saída: void
Descrição: Formata os dados da entrada para que saiam
na forma definida na descrição do trabalho.
*****************************************************/
void formataEntrada(Complexo *ComplexoUm, Complexo *ComplexoDois, char *expressao, char *operacao);

/*****************************************************
Função: void validaExpressao(Formato,char expressao[], char operacao)
Entrada: Formato, char *expressao, char.
Formato -> variável para retorno do formato da expressão:
            {conversao,
            exponenciacao,
            entrecomplexos,
            erro};
char *expressao -> ponteiro para a expressao a ser validada.
char operacao -> armazena a operação pedida na expressao:
                +,-,/,*,^,c. Sendo que 'c' é de conversão.
Saída: void
Descrição: Formata os dados da expressão que representa
a operação matemática de números complexos. Retira os
espaços em branco; define o último caractere como o
sinal de igualdade; identifica se a expressão é uma
operação de um número complexo (conversão ou exponenciação)
de dois números complexos (+,-,*,/) ou se a expressão
contém um erro; identifica qual é a operação da expressão.
*****************************************************/
void validaExpressao(Formato *, char *, char *, Complexo*, Complexo*);

/*****************************************************
Função: void executaOperacao(Complexo *,Complexo *, Complexo *, char *, char *)
Entrada: Complexo *,Complexo *, Complexo *, char *, char *
ComplexoUm -> Número complexo 1 a ser armazenado da expressão
ComplexoDois -> Número complexo 2 a ser armazenado da expressão
ComplexoResultado -> Número complexo 2 a ser armazenado da expressão
char *expressao -> ponteiro para a expressao a ser validada.
char operacao -> armazena a operação pedida na expressao:
                +,-,/,*,^,c. Sendo que 'c' é de conversão.
Saída: void
Descrição: Executa a chamada da operação definida na
expressão de entrada do arquivo.
*****************************************************/
void executaOperacao(Complexo*, Complexo*, Complexo*, char *, char *);

/*****************************************************
Função: void leComplexo(char expressao[], Complexo complexo, int loop, Formato formatoOperacao)
Entrada: -char [] - String
        Operação de entrada já formatada.
         -Complexo complexo
        Número complexo onde será armazenado o valor
         -int loop
        Número do índice onde a expressão de entrada está sendo lida.
         -Formato formatoOperacao
        variável para retorno do formato da expressão:
            {conversao,
            exponenciacao,
            entrecomplexos,
            erro};
Saída: int - 1 caso a operação encontre erros. 0 caso o número seja lido com sucesso.
Descrição: Faz a leitura de um número complexo em uma expressão numérica e registra
        os valores dentro de uma estrutura de um número complexo.
*****************************************************/
int leComplexo(char [], Complexo**, int*, Formato**);

/*****************************************************
Função: void procuraNum(char expressao[], int indice)
Entrada: char expressao[] - String
        Expressão de entrada já formatada.
         int indice - Índice na expressao de entrada a começar a ser lido.
Saída: float - Valor do número encontrado em tipo float.
Descrição: Converte número dentro de string de char até certo ponto.
*****************************************************/
float procuraNum(char [], int**);

/*****************************************************
Função: float charparafloat(char)
Entrada: char
Saída: float
Descrição: Converte um char para um float
*****************************************************/
float charparafloat(char);

/*****************************************************
Função: somaComplexo
Entrada: Complexo **, Complexo **, Complexo **
Complexo ** -> Primeiro número complexo
Complexo ** -> Segundo número complexo
Complexo ** -> Número complexo a ser armazenado o resultado
da operação.
Saída: void
Descrição: Calcula a soma de dois numeros complexos
*****************************************************/
void somaComplexo(Complexo **, Complexo **, Complexo **);

/*****************************************************
Função: subtracaoComplexo
Entrada: Complexo **, Complexo **, Complexo **
Complexo ** -> Primeiro número complexo
Complexo ** -> Segundo número complexo
Complexo ** -> Número complexo a ser armazenado o resultado
da operação.
Saída: void
Descrição: Calcula a subtração de dois numeros complexos
*****************************************************/
void subtracaoComplexo(Complexo **, Complexo **, Complexo **);

/*****************************************************
Função: multiplicacaoComplexo
Entrada: Complexo **, Complexo **, Complexo **
Complexo ** -> Primeiro número complexo
Complexo ** -> Segundo número complexo
Complexo ** -> Número complexo a ser armazenado o resultado
da operação.
Saída: void
Descrição: Calcula a multiplicação de dois numeros complexos
*****************************************************/
void multiplicacaoComplexo(Complexo **, Complexo **, Complexo **);

/*****************************************************
Função: divisaoComplexo
Entrada: Complexo **, Complexo **, Complexo **
Complexo ** -> Primeiro número complexo
Complexo ** -> Segundo número complexo
Complexo ** -> Número complexo a ser armazenado o resultado
da operação.
Saída: void
Descrição: Calcula a divisão de dois numeros complexos
*****************************************************/
void divisaoComplexo(Complexo **, Complexo **, Complexo **);

/*****************************************************
Função: divisaoComplexo
Entrada: Complexo **, char
Complexo -> Número a ser convertido.
char -> Tipo para o qual deverá ser convertido o número ('i' / 'p')
Saída: void
Descrição: Faz a conversão de um número complexo
do tipo polar para retangular ou vice versa.
*****************************************************/
void conversaoComplexo(Complexo **, char);

#endif // CALCULADORACOMPLEXA_H_INCLUDED
