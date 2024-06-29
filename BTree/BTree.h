#include <stdio.h>
#include <stdlib.h>

typedef struct No_B {
  int total;
  int *chaves;
  struct No_B **filhos;
  struct No_B *pai;
} No_B;

typedef struct ArvoreB {
  No_B *raiz;
  int ordem;
} ArvoreB;

extern unsigned long int contagem_insercao_b;
extern unsigned long int contagem_remocao_b;

ArvoreB *criarArvoreBTree(int ordem);
void addChaveArvoreBTree(ArvoreB *, int);
void removeChaveArvoreBTree(ArvoreB *arvore, int chave);
void printar_arvore_b(No_B *no);
unsigned long int getContInsercaoBTree();
unsigned long int getContRemocaoBTree();