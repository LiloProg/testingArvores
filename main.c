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
        execOperacoesArvore("AVL", avl, "Insercao", addArvoreAvl, valores, getContInvercaoAvl, i+1, resultado);
        execOperacoesArvore("AVL", avl, "Remocao", removeArvoreAvl, valores, getContRemocaoAvl, i+1, resultado);
        free(avl);
        
        RedBlack * rb = criaArvoreRb();
        execOperacoesArvore("RedBlack", rb, "Insercao", addArvoreRb, valores, getContInvercaoRb, i+1, resultado);
        execOperacoesArvore("RedBlack", rb, "Remocao", removeArvoreRb, valores, getContRemocaoRb, i+1, resultado);
        free(rb);
        
        ArvoreB *bTreeOrdem1 = criarArvoreBTree(1);
        execOperacoesArvore("B-Tree ordem 1", bTreeOrdem1, "Insercao", addChaveArvoreBTree, valores, getContInsercaoBTree, i+1, resultado);
        execOperacoesArvore("B-Tree ordem 1", bTreeOrdem1, "Remocao", removeChaveArvoreBTree, valores, getContRemocaoBTree, i+1, resultado);
        free(bTreeOrdem1);
        
        ArvoreB *bTreeOrdem2 = criarArvoreBTree(5);
        execOperacoesArvore("B-Tree ordem 5", bTreeOrdem2, "Insercao", addChaveArvoreBTree, valores, getContInsercaoBTree, i+1, resultado);
        execOperacoesArvore("B-Tree ordem 5", bTreeOrdem2, "Remocao", removeChaveArvoreBTree, valores, getContRemocaoBTree, i+1, resultado);
        free(bTreeOrdem2);

        ArvoreB *bTreeOrdem3 = criarArvoreBTree(10);
        execOperacoesArvore("B-Tree ordem 10", bTreeOrdem3, "Insercao", addChaveArvoreBTree, valores, getContInsercaoBTree, i+1, resultado);
        execOperacoesArvore("B-Tree ordem 10", bTreeOrdem3, "Remocao", removeChaveArvoreBTree, valores, getContRemocaoBTree, i+1, resultado);
        free(bTreeOrdem3);   
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
