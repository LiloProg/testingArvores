#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "AVL/arvoreAvl.h"
#include "RedBlack/RedBlack.h"
#include "BTree/BTree.h"

void gerarValoresAletorios(int * valores);

void execOperacoesArvore(
    char * nomeArvore,
    void * arvore,
    char * nomeOperacao,
    void * (*operacao)(void *, int),
    int * valores,
    unsigned long int (*get_contagem)(),
    int numero_amostra,
    FILE *resultado
);

#define numParametros 10000
#define numAmostras 10

void *wrapper_addArvoreAvl(void *tree, int value) {
    return (void *)addArvoreAvl((ArvoreAvl *)tree, value);
}

void *wrapper_removeArvoreAvl(void *tree, int value) {
    return (void *)removeArvoreAvl((ArvoreAvl *)tree, value);
}

void *wrapper_addArvoreRb(void *tree, int value) {
    return (void *)addArvoreRb((RedBlack *)tree, value);
}

void *wrapper_removeArvoreRb(void *tree, int value) {
    removeArvoreRb((RedBlack *)tree, value);
    return NULL;
}

void *wrapper_addChaveArvoreBTree(void *tree, int value) {
    addChaveArvoreBTree((ArvoreB *)tree, value);
    return NULL;
}

void *wrapper_removeChaveArvoreBTree(void *tree, int value) {
    removeChaveArvoreBTree((ArvoreB *)tree, value);
    return NULL;
}

int main() {

    srand(time(NULL));

    //Criando csv
    FILE *resultado;
    resultado = fopen("resultado.csv", "w+");
    fprintf(resultado,"Nome Arvore, Nome operacao, Amostra, Quantidade Parametros, Valor, Custo Operacao, Custo Total\n");

    int i=0;
    for (i=0; i < numAmostras; i++)
    {
        //Colocando valores aleatórios no vetor.
        int valores[numParametros];
        gerarValoresAletorios(valores);

        //Executando operacoes para todas as arvores abaixo
        ArvoreAvl * avl = criaArvoreAvl();
        execOperacoesArvore("AVL", avl, "Insercao", wrapper_addArvoreAvl, valores, getContInvercaoAvl, i+1, resultado);
        execOperacoesArvore("AVL", avl, "Remocao", wrapper_removeArvoreAvl, valores, getContRemocaoAvl, i+1, resultado);
        free(avl);
        
        RedBlack * rb = criaArvoreRb();
        execOperacoesArvore("RedBlack", rb, "Insercao", wrapper_addArvoreRb, valores, getContInvercaoRb, i+1, resultado);
        execOperacoesArvore("RedBlack", rb, "Remocao", wrapper_removeArvoreRb, valores, getContRemocaoRb, i+1, resultado);
        free(rb);
        
        ArvoreB *bTreeOrdem1 = criarArvoreBTree(1);
        execOperacoesArvore("B-Tree ordem 1", bTreeOrdem1, "Insercao", wrapper_addChaveArvoreBTree, valores, getContInsercaoBTree, i+1, resultado);
        execOperacoesArvore("B-Tree ordem 1", bTreeOrdem1, "Remocao", wrapper_removeChaveArvoreBTree, valores, getContRemocaoBTree, i+1, resultado);
        free(bTreeOrdem1);
        
        ArvoreB *bTreeOrdem5 = criarArvoreBTree(5);
        execOperacoesArvore("B-Tree ordem 5", bTreeOrdem5, "Insercao", wrapper_addChaveArvoreBTree, valores, getContInsercaoBTree, i+1, resultado);
        execOperacoesArvore("B-Tree ordem 5", bTreeOrdem5, "Remocao", wrapper_removeChaveArvoreBTree, valores, getContRemocaoBTree, i+1, resultado);
        free(bTreeOrdem5);

        ArvoreB *bTreeOrdem10 = criarArvoreBTree(10);
        execOperacoesArvore("B-Tree ordem 10", bTreeOrdem10, "Insercao", wrapper_addChaveArvoreBTree, valores, getContInsercaoBTree, i+1, resultado);
        execOperacoesArvore("B-Tree ordem 10", bTreeOrdem10, "Remocao", wrapper_removeChaveArvoreBTree, valores, getContRemocaoBTree, i+1, resultado);
        free(bTreeOrdem10);   
        //Executando operacoes para todas as arvores acima
    }

    fclose(resultado);
}

//Funções adicionais abaixo



void execOperacoesArvore(
    char * nomeArvore,
    void * arvore,
    char * nomeOperacao,
    void * (*operacao)(void *, int),
    int * valores,
    unsigned long int (*get_contagem)(),
    int numero_amostra,
    FILE *resultado
) 
{
    unsigned long int count_operacoes_total = 0;
    int i = 0;
    for(i = 0; i < numParametros; i++) {
        operacao(arvore, valores[i]);
        count_operacoes_total += get_contagem();
        fprintf(resultado, "%s, %s, %d, %d, %d, %lu, %lu\n", nomeArvore, nomeOperacao, numero_amostra, i, valores[i], get_contagem(), count_operacoes_total);
    }
}

void gerarValoresAletorios(int * valores) {
    int i;
    for (i = 0; i < numParametros; i++) {
        int posicaoVetor = 0;
        int valor = rand();
        while (posicaoVetor <= i) {
            if (valores[posicaoVetor] == valor) {
                valor = rand();
                posicaoVetor = 0;
            } 
            else {
                posicaoVetor++;
            }
        }
        valores[i] = valor;
    }
}
//Funções adicionais acima
