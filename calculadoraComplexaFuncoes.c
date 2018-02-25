#include <stdio.h>
#include <stdlib.h>
#include "calculadoraComplexa.h"
#include <math.h>
#include <string.h>


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

/********************************************************
                     formataEntrada
/********************************************************/
void formataEntrada(Complexo *ComplexoUm, Complexo *ComplexoDois, char *expressao, char *operacao){

    char *string_auxiliar1;
    char *string_auxiliar2;
    string_auxiliar1 = malloc(sizeof(char)*20);
    string_auxiliar2 = malloc(sizeof(char)*20);

    *(expressao) = NULL;
    sprintf(string_auxiliar1,"%.2f", (*ComplexoUm).operando1);
    sprintf(string_auxiliar2,"%.2f", (*ComplexoUm).operando2);
    strcat(expressao, string_auxiliar1);
    strcat(expressao, " ");
    if((*ComplexoUm).operando2 >= 0) //Se for positivo
        strcat(expressao, "+");
    strcat(expressao, string_auxiliar2);
    if((*ComplexoUm).tipo == 'i'){
        strcat(expressao, "i");
    }
    else{
        strcat(expressao, "p");
    }
    strcat(expressao, " ");

    *string_auxiliar1 = operacao;

    switch(*operacao){
    case '+':
        strcat(expressao, "+");
        break;

    case '-':
        strcat(expressao, "-");
        break;

    case '*':
        strcat(expressao, "*");
        break;

    case '/':
        strcat(expressao, "/");
        break;

    case '=':
        strcat(expressao, " =");
        return;
        break;
    }

    strcat(expressao, " ");
    sprintf(string_auxiliar1,"%.2f", (*ComplexoDois).operando1);
    sprintf(string_auxiliar2,"%.2f", (*ComplexoDois).operando2);
    strcat(expressao, string_auxiliar1);
    strcat(expressao, " ");
    if((*ComplexoDois).operando2 >= 0) //Se for positivo
        strcat(expressao, "+");
    strcat(expressao, string_auxiliar2);
    if((*ComplexoDois).tipo == 'i'){
        strcat(expressao, "i");
    }
    else{
        strcat(expressao, "p");
    }
    strcat(expressao, " =");
}

/********************************************************
                      leComplexo
/********************************************************/
int leComplexo(char expressao[], Complexo **complexo, int *loop, Formato **formatoOperacao){

    int sinal1, sinal2;

    //Busca pela parte real do ComplexoUM
    switch(*(expressao+*(loop))){
        case '-':
            sinal1 = -1;
            *loop = *(loop)+1;
            break;
        case '+':
            sinal1 = 1;
            *loop = *(loop)+1;
            break;
        default:
            if((*(expressao+(*(loop))) >= 48) && (*(expressao+(*(loop))) <= 57)){ //verifica se é um número
                sinal1 = 1;
            }
            else{
                **formatoOperacao = erro;
                return 1; //Se não for + ou -, erro
            }
    }

    if(!((*(expressao+(*(loop))) >= 48) && (*(expressao+(*(loop))) <= 57))){ //verifica se segunda digito da expressão não é um número
        **formatoOperacao = erro;
        return 1; //Se não for número, erro
    }
    else{
        (**complexo).operando1 = (procuraNum(expressao, &loop))*sinal1;
        //printf("\nComplexo: %.1f", (**complexo).operando1);
    }
    *loop = *(loop)+1;

    //Busca pela parte imaginária do ComplexoUM
    switch(*(expressao+*(loop))){
        case '-':
            sinal2 = -1;
            *loop = *(loop)+1;
            break;
        case '+':
            sinal2 = 1;
            *loop = *(loop)+1;
            break;
        default:
            if((*(expressao+(*(loop))) >= 48) && (*(expressao+(*(loop))) <= 57)){ //verifica se é um número
                sinal2 = 1;
            }
            else{
                **formatoOperacao = erro;
                return 1; //Se não for + ou -, erro
            }
    }
    if(!((*(expressao+*(loop)) >= 48) && (*(expressao+*(loop)) <= 57))){ //verifica se segunda digito da expressão não é um número
        **formatoOperacao = erro;
        return 1; //Se não for número, erro
    }
    else{
        (**complexo).operando2 = (procuraNum(expressao, &loop))*sinal2;
    }
    *loop = *(loop)+1;

    //Procura pelo tipo do ComplexoUM
    switch(*(expressao+*(loop))){
        case 'i':
            (**complexo).tipo = 'i';
            break;
        case 'p':
            (**complexo).tipo = 'p';
            break;
        default:
            **formatoOperacao = erro;
            return 1;
    }
    return 0; //Número lido sem erros encontrados
}

/********************************************************
                     executaOperacao
/********************************************************/
void executaOperacao(Complexo *ComplexoUm, Complexo *ComplexoDois, Complexo *ComplexoResultado, char *operacao, char *resultado){

    char *string_auxiliar1;
    char *string_auxiliar2;
    char *string_auxiliar3;
    char *string_auxiliar4;
    char tipo = 'd';
    string_auxiliar1 = malloc(sizeof(char)*40);
    string_auxiliar2 = malloc(sizeof(char)*40);
    string_auxiliar3 = malloc(sizeof(char)*40);
    string_auxiliar4 = malloc(sizeof(char)*40);

    if((*ComplexoUm).tipo == (*ComplexoDois).tipo)
        tipo = (*ComplexoDois).tipo;

    switch(*operacao){
        case '/':
            conversaoComplexo(&ComplexoUm, 'p');
            conversaoComplexo(&ComplexoDois, 'p');
            divComplexo(&ComplexoUm, &ComplexoDois, &ComplexoResultado);
            sprintf(string_auxiliar3,"%.2f", (*ComplexoResultado).operando1);
            sprintf(string_auxiliar4,"%.2f", (*ComplexoResultado).operando2);
            conversaoComplexo(&ComplexoResultado, 'i');
            break;
        case '*':
            conversaoComplexo(&ComplexoUm, 'p');
            conversaoComplexo(&ComplexoDois, 'p');
            multPolar(&ComplexoUm, &ComplexoDois, &ComplexoResultado);
            sprintf(string_auxiliar3,"%.2f", (*ComplexoResultado).operando1);
            sprintf(string_auxiliar4,"%.2f", (*ComplexoResultado).operando2);
            conversaoComplexo(&ComplexoResultado, 'i');
            break;
        case '-':
            conversaoComplexo(&ComplexoUm, 'i');
            conversaoComplexo(&ComplexoDois, 'i');
            subtracaoComplexo(&ComplexoUm, &ComplexoDois, &ComplexoResultado);
            break;
        case '+':
            conversaoComplexo(&ComplexoUm, 'i');
            conversaoComplexo(&ComplexoDois, 'i');
            somaComplexo(&ComplexoUm, &ComplexoDois, &ComplexoResultado);
            break;

        case '=':
            if((*ComplexoUm).tipo == 'i'){
                conversaoComplexo(&ComplexoUm, 'p');
                (*ComplexoResultado).operando1 = (*ComplexoUm).operando1;
                (*ComplexoResultado).operando2 = (*ComplexoUm).operando2;
                (*ComplexoResultado).tipo = (*ComplexoUm).tipo;
                tipo = 'p';
            }
            else{
                conversaoComplexo(&ComplexoUm, 'i');
                (*ComplexoResultado).operando1 = (*ComplexoUm).operando1;
                (*ComplexoResultado).operando2 = (*ComplexoUm).operando2;
                (*ComplexoResultado).tipo = (*ComplexoUm).tipo;
                tipo = 'i';
            }
        default:
            break;
    }

    switch(tipo){
        case 'i':
                sprintf(string_auxiliar1,"%.2f", (*ComplexoResultado).operando1);
                sprintf(string_auxiliar2,"%.2f", (*ComplexoResultado).operando2);
                strcat(resultado, string_auxiliar1);
                strcat(resultado, " ");
                if((*ComplexoResultado).operando2 >= 0) //Se for positivo
                    strcat(resultado, "+");
                strcat(resultado, string_auxiliar2);
                strcat(resultado, "i");
            break;

        case 'p':
                conversaoComplexo(&ComplexoResultado, 'p');
                sprintf(string_auxiliar1,"%.2f", (*ComplexoResultado).operando1);
                sprintf(string_auxiliar2,"%.2f", (*ComplexoResultado).operando2);
                strcat(resultado, string_auxiliar1);
                strcat(resultado, " ");
                if((*ComplexoResultado).operando2 >= 0) //Se for positivo
                    strcat(resultado, "+");
                strcat(resultado, string_auxiliar2);
                strcat(resultado, "p");
            break;

        case 'd':
            if(*operacao == '/' || *operacao == '*'){
                sprintf(string_auxiliar1,"%.2f", (*ComplexoResultado).operando1);
                sprintf(string_auxiliar2,"%.2f", (*ComplexoResultado).operando2);
                strcat(resultado, string_auxiliar1);
                strcat(resultado, " ");
                if((*ComplexoResultado).operando2 >= 0) //Se for positivo
                    strcat(resultado, "+");
                strcat(resultado, string_auxiliar2);
                strcat(resultado, "i");
                strcat(resultado, " ");
                strcat(resultado, "ou");
                strcat(resultado, " ");

                strcat(resultado, string_auxiliar3);
                strcat(resultado, " ");
                if((*ComplexoResultado).operando2 >= 0) //Se for positivo
                    strcat(resultado, "+");
                strcat(resultado, string_auxiliar4);
                strcat(resultado, "p");
            }
            else{
                sprintf(string_auxiliar1,"%.2f", (*ComplexoResultado).operando1);
                sprintf(string_auxiliar2,"%.2f", (*ComplexoResultado).operando2);
                strcat(resultado, string_auxiliar1);
                strcat(resultado, " ");
                if((*ComplexoResultado).operando2 >= 0) //Se for positivo
                    strcat(resultado, "+");
                strcat(resultado, string_auxiliar2);
                strcat(resultado, "i");
                strcat(resultado, " ");
                strcat(resultado, "ou");
                strcat(resultado, " ");

                conversaoComplexo(&ComplexoResultado, 'p');
                sprintf(string_auxiliar1,"%.2f", (*ComplexoResultado).operando1);
                sprintf(string_auxiliar2,"%.2f", (*ComplexoResultado).operando2);
                strcat(resultado, string_auxiliar1);
                strcat(resultado, " ");
                if((*ComplexoResultado).operando2 >= 0) //Se for positivo
                    strcat(resultado, "+");
                strcat(resultado, string_auxiliar2);
                strcat(resultado, "p");
        }
        break;

    default:
        break;

    }
    free(string_auxiliar1);
    free(string_auxiliar2);
    free(string_auxiliar3);
    free(string_auxiliar4);
}

/********************************************************
                      validaExpressao
/********************************************************/
void validaExpressao(Formato *formatoOperacao, char *expressao, char *operacao, Complexo *ComplexoUm, Complexo *ComplexoDois){

    unsigned int indice1 = 0, indice2 = 0;
    int loop;
    int numero = strlen(expressao);
    *(expressao+strlen(expressao)-1) = '\n';

    //                    Formata a expressão

    //Retira todos os espaços em branco da string do usuário:
    for(indice1=0 ; *(expressao+indice1) != '\0' ; indice1++){
        if(*(expressao+indice1) == 32){
            for(indice2 = indice1; *(expressao+indice2) != '\0' ; indice2++)
                *(expressao+indice2) = *(expressao+indice2+1);
            indice1--;
        }
    }
    //Encontra o caractere '=' e elimina o restante da função a partir dali
    for(indice1=0 ; *(expressao+indice1) != '\0' ; indice1++){
        if(*(expressao+indice1) == 61){
            *(expressao+indice1+1) = '\0';
            
            break;
        }
    }

    //            Identifica caracteres estranhos

    //Valida se os caracteres digitados condizem com os modelos de entrada
    for(loop = 0; *(expressao+loop) != '\0'; loop++){
        if(!(*(expressao+loop) == '+' ||
             *(expressao+loop) == '-' ||
             *(expressao+loop) == '/' ||
             *(expressao+loop) == '*' ||
             *(expressao+loop) == '^' ||
             *(expressao+loop) == '=' ||
             *(expressao+loop) == 'p' ||
             *(expressao+loop) == 'i' ||
            (*(expressao+loop) >= 48 && *(expressao+loop) <= 57))){
            *formatoOperacao = erro;   //Operacao invalida
            return;
            }
    }

    //                      Lê complexo1

    loop = 0;
    if(leComplexo(expressao, &ComplexoUm, &loop, &formatoOperacao)){
        *formatoOperacao = erro;
        return;
    }

    loop++;

    //                Identifica tipo de operação

    switch(*(expressao+loop)){
        case '/':
            *formatoOperacao = entrecomplexos;
            break;
        case '*':
            *formatoOperacao = entrecomplexos;
            break;
        case '-':
            *formatoOperacao = entrecomplexos;
            break;
        case '+':
            *formatoOperacao = entrecomplexos;
            break;
        case '^':
            *formatoOperacao = exponenciacao;
            *operacao = *(expressao+loop);
            
            return;
            break;
        case '=':
            *formatoOperacao = conversao;
            *operacao = *(expressao+loop);
            return;
        default:
            *formatoOperacao = erro;
            return;
    }
    *operacao = *(expressao+loop);

    //                    Lê complexo 2
    loop++;

    if(leComplexo(expressao, &ComplexoDois, &loop, &formatoOperacao)){
        *formatoOperacao = erro;
        return;
    }

    //                    Lê sinal de =

    loop++;
    if(!(*(expressao+loop) == '=')){
        *formatoOperacao = erro;
        return;
    }
    else{
        return;
    }
}

/********************************************************
                    procuraNum
/********************************************************/
float procuraNum(char expressao[], int **indice){

    int ind = **indice;
    int indiceII, qtd = 0;
    float resultado = 0;

    for(ind = **indice ;; ind++){
        if((*(expressao+ind) >= 48) && (*(expressao+ind) <= 57)){
            qtd++;
        }
        else{   //Coloca na variável
            for(indiceII = (ind - qtd) ; qtd != 0 ; indiceII++, qtd--){
                resultado = resultado + ((charparafloat(*(expressao+indiceII))*(pow(10, (qtd-1)))));
            }
            break;
        }
    }
    **indice = indiceII-1;
    return resultado;
}

/********************************************************
                    charparafloat
/********************************************************/
float charparafloat(char valor){
    float retorno = valor - 48;
    return retorno;
}

/********************************************************
                      somaComplexo
/********************************************************/
void somaComplexo(Complexo **ComplexoUm, Complexo **ComplexoDois, Complexo **ComplexoResultado){

    float real, imaginario;
    //*resultado = itoa((*ComplexoUm).operando1,*resultado,2);
    real = (**ComplexoUm).operando1 + (**ComplexoDois).operando1;
    imaginario = (**ComplexoUm).operando2 + (**ComplexoDois).operando2;
    (**ComplexoResultado).operando1 = real;
    (**ComplexoResultado).operando2 = imaginario;
    (**ComplexoResultado).tipo = 'i';
}

/********************************************************
                   subtracaoComplexo
/********************************************************/
void subtracaoComplexo(Complexo **ComplexoUm, Complexo **ComplexoDois, Complexo **ComplexoResultado){

    float real, imaginario;
    real = (**ComplexoUm).operando1 - (**ComplexoDois).operando1;
    imaginario = (**ComplexoUm).operando2 - (**ComplexoDois).operando2;
    (**ComplexoResultado).operando1 = real;
    (**ComplexoResultado).operando2 = imaginario;
    (**ComplexoResultado).tipo = 'i';
}

/********************************************************
                  multiplicacaoComplexo
/********************************************************/
void multPolar(Complexo **ComplexoUm, Complexo **ComplexoDois, Complexo **ComplexoResultado){

    float real, imaginario;

    real = ((**ComplexoUm).operando1*(**ComplexoDois).operando1);
    imaginario = ((**ComplexoUm).operando2+(**ComplexoDois).operando2);
    (**ComplexoResultado).operando1 = real;
    (**ComplexoResultado).operando2 = imaginario;
    (**ComplexoResultado).tipo = 'p';
}

void multiplicacaoComplexo(Complexo **ComplexoUm, Complexo **ComplexoDois, Complexo **ComplexoResultado){

    float real, imaginario;
    real = ((**ComplexoUm).operando1*(**ComplexoDois).operando1)-((**ComplexoUm).operando2*(**ComplexoDois).operando2);
    imaginario = ((**ComplexoUm).operando1*(**ComplexoDois).operando2)+((**ComplexoDois).operando1*(**ComplexoUm).operando2);
    (**ComplexoResultado).operando1 = real;
    (**ComplexoResultado).operando2 = imaginario;
    (**ComplexoResultado).tipo = 'i';
}

/********************************************************
                    divisaoComplexo
/********************************************************/
void divComplexo(Complexo **ComplexoUm, Complexo **ComplexoDois, Complexo **ComplexoResultado){

    float real, imaginario;
    real = ((**ComplexoUm).operando1/(**ComplexoDois).operando1);
    imaginario = ((**ComplexoUm).operando2-(**ComplexoDois).operando2);
    (**ComplexoResultado).operando1 = real;
    (**ComplexoResultado).operando2 = imaginario;
    (**ComplexoResultado).tipo = 'p';

}
void divisaoComplexo(Complexo **ComplexoUm, Complexo **ComplexoDois, Complexo **ComplexoResultado){

    float d1, d2, d3, real, imaginario;
    d1 = ((**ComplexoUm).operando1*(**ComplexoDois).operando1)+((**ComplexoUm).operando2*(**ComplexoDois).operando2);
    d2 = ((pow((**ComplexoDois).operando1, 2))+(pow((**ComplexoDois).operando2, 2)));
    d3 = ((**ComplexoUm).operando2*(**ComplexoDois).operando1)-((**ComplexoUm).operando1*(**ComplexoDois).operando2);
    real = d1/d2;
    imaginario = d3/d2;
    (**ComplexoResultado).operando1 = real;
    (**ComplexoResultado).operando2 = imaginario;
    (**ComplexoResultado).tipo = 'i';
}

/********************************************************
                   conversaoComplexo
/********************************************************/
void conversaoComplexo(Complexo **Complexo, char tipo){

    float primarg, segarg;

    if((**Complexo).tipo != tipo){ //Verifica se já não é do tipo desejado
        if(tipo == 'i'){  //Se não for, converte para retangular
            primarg = (**Complexo).operando1*cos((**Complexo).operando2*M_PI/180);
            segarg = (**Complexo).operando1*sin((**Complexo).operando2*M_PI/180);
            (**Complexo).operando1 = primarg;
            (**Complexo).operando2 = segarg;
            (**Complexo).tipo = 'i';
        }else if(tipo == 'p'){  //Se não for, converte para polar
            primarg = sqrt(pow((**Complexo).operando1,2) + pow((**Complexo).operando2,2));
            
            segarg = (atan2((**Complexo).operando2,(**Complexo).operando1))*180/M_PI;
            (**Complexo).operando1 = primarg;
            (**Complexo).operando2 = segarg;
            (**Complexo).tipo = 'p';
        }
    }
}
