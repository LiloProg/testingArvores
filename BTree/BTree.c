#include "BTree.h"

unsigned long int contInsercaoB = 0;
unsigned long int contRemocaoB = 0;

//Criar nó
No_B *criaNo(ArvoreB *arvore) {
  int max = arvore->ordem * 2;
  No_B *no = malloc(sizeof(No_B));

  no->pai = NULL;

  no->chaves = malloc(sizeof(int) * (max + 1));
  no->filhos = malloc(sizeof(No_B) * (max + 2));
  no->total = 0;

  for (int i = 0; i < max + 2; i++) {
    contInsercaoB++; //CONT INSERTION
    
    no->filhos[i] = NULL;
  }
  contInsercaoB++; //CONT INSERTION

  return no;
}

ArvoreB *criarArvoreBTree(int ordem) {
  ArvoreB *a = malloc(sizeof(ArvoreB));
  a->ordem = ordem;
  a->raiz = criaNo(a);

  return a;
}

int pesquisaBinaria(No_B *no, int chave) {
  int inicio = 0, fim = no->total - 1, meio;

  while (inicio <= fim) {
    contInsercaoB++; //CONT INSERTION
    contRemocaoB++; //CONT REMOVAL

    meio = (inicio + fim) /2;

    if (no->chaves[meio] == chave) {
      contInsercaoB++; //CONT INSERTION
      contRemocaoB++; //CONT REMOVAL

      return meio;
    } else if (no->chaves[meio] > chave) {
      contInsercaoB += 2; //CONT INSERTION
      contRemocaoB += 2; //CONT REMOVAL
      
      fim = meio - 1;
    } else {
      contInsercaoB += 2; //CONT INSERTION
      contRemocaoB += 2; //CONT REMOVAL

      inicio = meio + 1;
    }
  }
  contInsercaoB++; //CONT INSERTION
  contRemocaoB++; //CONT REMOVAL
  
  return inicio;
}

No_B *localizaNo(ArvoreB *arvore, int chave) {
  No_B *no = arvore->raiz;
  
  while (no != NULL) {
    contInsercaoB++; //CONT INSERTION
    contRemocaoB++; //CONT REMOVAL
    
    int i = pesquisaBinaria(no, chave);

    contInsercaoB++; //CONT INSERTION
    contRemocaoB++; //CONT REMOVAL
    if (no->filhos[i] == NULL) {
      return no;
    } else {
      no = no->filhos[i];
    }
  }
  contInsercaoB++; //CONT INSERTION
  contRemocaoB++; //CONT REMOVAL

  return NULL;
}

void addChaveNo(No_B *no, No_B *novo, int chave) {
  int i = pesquisaBinaria(no, chave);

  for (int j = no->total - 1; j >= i; j--) {
    contInsercaoB++; //CONT INSERTION
    
    no->chaves[j + 1] = no->chaves[j];
    no->filhos[j + 2] = no->filhos[j + 1];
  }
  contInsercaoB++; //CONT INSERTION

  no->chaves[i] = chave;
  no->filhos[i + 1] = novo;

  no->total++;
}

int transbordo(ArvoreB *arvore, No_B *no) {
  contInsercaoB++; //CONT INSERTION
  
  return no->total > arvore->ordem * 2;
}

No_B *divideNo(ArvoreB *arvore, No_B *no) {
  int meio = no->total /2;
  No_B *novo = criaNo(arvore);
  novo->pai = no->pai;

  for (int i = meio + 1; i < no->total; i++) {
    contInsercaoB++; //CONT INSERTION

    novo->filhos[novo->total] = no->filhos[i];
    novo->chaves[novo->total] = no->chaves[i];

    contInsercaoB++; //CONT INSERTION
    if (novo->filhos[novo->total] != NULL) {
      novo->filhos[novo->total]->pai = novo;
    }

    novo->total++;
  }
  contInsercaoB++; //CONT INSERTION

  novo->filhos[novo->total] = no->filhos[no->total];
  
  contInsercaoB++; //CONT INSERTION
  if (novo->filhos[novo->total] != NULL) {
    novo->filhos[novo->total]->pai = novo;
  }
  
  no->total = meio;
  
  return novo;
}

void addChaveBTreeRecursivo(ArvoreB *arvore, No_B *no, No_B *novo, int chave) {
  addChaveNo(no, novo, chave);

  contInsercaoB++; //CONT INSERTION
  if (transbordo(arvore, no)) {
    int promovido = no->chaves[arvore->ordem];
    No_B *novo = divideNo(arvore, no);

    contInsercaoB++; //CONT INSERTION
    if (no->pai == NULL) {
      No_B *pai = criaNo(arvore);
      pai->filhos[0] = no;
      addChaveNo(pai, novo, promovido);

      no->pai = pai;
      novo->pai = pai;
      arvore->raiz = pai;
    } else {
      addChaveBTreeRecursivo(arvore, no->pai, novo, promovido);
    }
  }
}

void removeChaveRecursivo(ArvoreB *arvore, No_B *no, int chave) {
  int index = pesquisaBinaria(no, chave);

  contRemocaoB++; //CONT REMOVAL
  if (index < no->total && no->chaves[index] == chave) {
    //Caso 1: A chave está no nó folha
    
    contRemocaoB++; //CONT REMOVAL
    if (no->filhos[0] == NULL) {

      for (int i = index; i < no->total - 1; i++) {
        contRemocaoB++; //CONT REMOVAL
        no->chaves[i] = no->chaves[i + 1];
      }
      contRemocaoB++; //CONT REMOVAL
      
      no->total--;
    } else {
      int index = pesquisaBinaria(no, chave);

      No_B *predecessor = no->filhos[index];
      
      while (predecessor->filhos[predecessor->total] != NULL) {
        contRemocaoB++; //CONT REMOVAL

        predecessor = predecessor->filhos[predecessor->total];
      }
      contRemocaoB++; //CONT REMOVAL
      
      int predecessorChave = predecessor->chaves[predecessor->total - 1];

      no->chaves[index] = predecessorChave;

      removeChaveRecursivo(arvore, predecessor, predecessorChave);
    }
  } else {
    int index = pesquisaBinaria(no, chave);
    No_B *filho = no->filhos[index];

    //Verificar se o filho tem chaves suficientes para realizar a remoção

    contRemocaoB++; //CONT REMOVAL
    if (filho != NULL && filho->total > arvore->ordem) {
      removeChaveRecursivo(arvore, filho, chave);
    } else {

      if (index < no->total && no->filhos[index + 1] != NULL && no->filhos[index + 1]->total > arvore->ordem) {
        contRemocaoB++; //CONT REMOVAL

        No_B *irmaoDireita = no->filhos[index + 1];

        //Mover uma chave do nó pai para o nó filho
        filho->chaves[filho->total] = no->chaves[index];
        filho->total++;

        //Transferir todas as chaves e filhos do irmão à direita para o nó filho
        for (int i = 0; i < irmaoDireita->total; i++) {
          contRemocaoB++; //CONT REMOVAL

          filho->chaves[filho->total] = irmaoDireita->chaves[i];
          filho->filhos[filho->total] = irmaoDireita->filhos[i];

          contRemocaoB++; //CONT REMOVAL
          if (filho->filhos[filho->total] != NULL) {
            filho->filhos[filho->total]->pai = filho;
          }
          
          filho->total++;
        }
        contRemocaoB++; //CONT REMOVAL

        for (int i = index; i < no->total - 1; i++) {
          contRemocaoB++; //CONT REMOVAL

          no->chaves[i] = no->chaves[i + 1];
          no->filhos[i + 1] = no->filhos[i + 2];
        }
        contRemocaoB++; //CONT REMOVAL

        no->total--;

        free(irmaoDireita);
      } else if (index > 0 && no->filhos[index - 1] != NULL && no->filhos[index - 1]->total > arvore->ordem) {
        contRemocaoB += 2; //CONT REMOVAL

        No_B *irmaoEsquerda = no->filhos[index - 1];

        //Mover uma chave do nó pai para o nó filho
        filho->chaves[0] = no->chaves[index - 1];
        filho->total++;

        for (int i = 0; i < irmaoEsquerda->total; i++) {
          contRemocaoB++; //CONT REMOVAL

          filho->chaves[filho->total] = irmaoEsquerda->chaves[i];
          filho->filhos[filho->total] = irmaoEsquerda->filhos[i];

          contRemocaoB++; //CONT REMOVAL
          if (filho->filhos[filho->total] != NULL) {
            filho->filhos[filho->total]->pai = filho;
          }
          
          filho->total++;
        }
        contRemocaoB++; //CONT REMOVAL

        for (int i = index - 1; i < no->total - 1; i++) {
          contRemocaoB++; //CONT REMOVAL
          no->chaves[i] = no->chaves[i + 1];
          no->filhos[i + 1] = no->filhos[i + 2];
        }
        contRemocaoB++; //CONT REMOVAL

        no->total--;


        free(irmaoEsquerda);
      } else {
        contRemocaoB += 2; //CONT REMOVAL

        No_B *irmaoDireita = no->filhos[index + 1];

        //Move chave do nó pai para filho
        contRemocaoB++; //CONT REMOVAL
        if (filho != NULL) {
          filho->chaves[filho->total] = no->chaves[index];
          filho->total++;

          for (int i = 0; i < irmaoDireita->total; i++) {
            contRemocaoB++; //CONT REMOVAL

            filho->chaves[filho->total] = irmaoDireita->chaves[i];
            filho->filhos[filho->total] = irmaoDireita->filhos[i];

            contRemocaoB++; //CONT REMOVAL
            if (filho->filhos[filho->total] != NULL) {
              filho->filhos[filho->total]->pai = filho;
            }
            
            filho->total++;
          }
          contRemocaoB++; //CONT REMOVAL

          //Att nó pai
          for (int i = index; i < no->total - 1; i++) {
            contRemocaoB++; //CONT REMOVAL
            no->chaves[i] = no->chaves[i + 1];
            no->filhos[i + 1] = no->filhos[i + 2];
          }
          contRemocaoB++; //CONT REMOVAL

          no->total--;

          free(irmaoDireita); 
        }
      }
    }
  }
}

//Adicionar chave em árvore B
void addChaveArvoreBTree(ArvoreB *arvore, int chave) {
  contInsercaoB = 0;

  No_B *no = localizaNo(arvore, chave);

  addChaveBTreeRecursivo(arvore, no, NULL, chave);
}

void removeChaveArvoreBTree(ArvoreB *arvore, int chave) {
  contRemocaoB = 0;

  No_B *no = localizaNo(arvore, chave);
  
  removeChaveRecursivo(arvore, no, chave);
}

unsigned long int getContInsercaoBTree() {
  return contInsercaoB;
}

unsigned long int getContRemocaoBTree() {
  return contRemocaoB;
}