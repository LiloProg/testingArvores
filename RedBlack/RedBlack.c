#include <stdlib.h>
#include <stdio.h>
#include "RedBlack.h"

int vazia(RedBlack* arvore);
No* criarNo(RedBlack* arvore, No* pai, int valor);
No* adicionarNo(RedBlack* arvore, No* no, int valor);
No* localizar(RedBlack* arvore, int valor);
No* sucessor(RedBlack* arvore, No* no);
void balancearRemocao(RedBlack* arvore, No* no);
void balancear(RedBlack* arvore, No* no);
void rotacionarEsquerda(RedBlack* arvore, No* no, unsigned long int* contagem);
void rotacionarDireita(RedBlack* arvore, No* no, unsigned long int* contagem);
void removeArvoreRbRecursivo(RedBlack* arvore, int valor);
No* addArvoreRbRecursivo(RedBlack* arvore, int valor);

unsigned long int contInsercaoRb;
unsigned long int contRemocaoRb;

unsigned long int getContInvercaoRb() {
  return contInsercaoRb;
}

unsigned long int getContRemocaoRb() {
  return contRemocaoRb;
}

RedBlack* criaArvoreRb() {
  RedBlack *arvore = malloc(sizeof(RedBlack));
  arvore->nulo = NULL;
  arvore->raiz = NULL;

  arvore->nulo = criarNo(arvore, NULL, 0);
  arvore->nulo->cor = Preto;

  return arvore;
}

int vazia(RedBlack* arvore) {
  return arvore->raiz == NULL;
}

No* addArvoreRb(RedBlack* arvore, int valor){
  contInsercaoRb = 0;
  return addArvoreRbRecursivo(arvore, valor);
}
void removeArvoreRb(RedBlack* arvore, int valor){
  contRemocaoRb = 0;
  return removeArvoreRbRecursivo(arvore, valor);
}

No* criarNo(RedBlack* arvore, No* pai, int valor) {
  No* no = malloc(sizeof(No));

  no->pai = pai;    
  no->valor = valor;
  no->direita = arvore->nulo;
  no->esquerda = arvore->nulo;

  return no;
}

No* adicionarNo(RedBlack* arvore, No* no, int valor) {
  contInsercaoRb++;
  if (valor > no->valor) {
    contInsercaoRb++;
    if (no->direita == arvore->nulo) {
      no->direita = criarNo(arvore, no, valor);     
      no->direita->cor = Vermelho;       
      
      return no->direita;
    } else {
      return adicionarNo(arvore, no->direita, valor);
    }
  } else {
    contInsercaoRb++;
    if (no->esquerda == arvore->nulo) {
      no->esquerda = criarNo(arvore, no, valor);
      no->esquerda->cor = Vermelho;
      
      return no->esquerda;
    } else {
      return adicionarNo(arvore, no->esquerda, valor);
    }
  }
}

No* addArvoreRbRecursivo(RedBlack* arvore, int valor) {
  contInsercaoRb++;
  if (vazia(arvore)) {
    arvore->raiz = criarNo(arvore, arvore->nulo, valor);
    arvore->raiz->cor = Preto;
      
    return arvore->raiz;
  } else {
    No* no = adicionarNo(arvore, arvore->raiz, valor);
    balancear(arvore, no);
    
    return no;
  }
}

No* localizar(RedBlack* arvore, int valor) {
  contRemocaoRb++;
  if (!vazia(arvore)) {
    No* no = arvore->raiz;

    while (no != arvore->nulo) {
      contRemocaoRb+=2;
      if (no->valor == valor) {
        return no;
      } else {
        no = valor < no->valor ? no->esquerda : no->direita;
      }
    }
    contRemocaoRb++;
  }

  return NULL;
}

void balancear(RedBlack* arvore, No* no) {
  while (no->pai->cor == Vermelho) {
    contInsercaoRb+=2;
    if (no->pai == no->pai->pai->esquerda) {
      No *tio = no->pai->pai->direita;
      
      contInsercaoRb++;
      if (tio->cor == Vermelho) {
        tio->cor = Preto; //Caso 1
        no->pai->cor = Preto; 

        no->pai->pai->cor = Vermelho; //Caso 1
        no = no->pai->pai; //Caso 1
      } else {
        contInsercaoRb++;
        if (no == no->pai->direita) {
          no = no->pai; //Caso 2
          rotacionarEsquerda(arvore, no, &contInsercaoRb); //Caso 2
        } else {
          no->pai->cor = Preto; 
          no->pai->pai->cor = Vermelho; //Caso 3
          rotacionarDireita(arvore, no->pai->pai, &contInsercaoRb); //Caso 3
        }
      }
    } else {
      No *tio = no->pai->pai->esquerda;
      
      contInsercaoRb++;
      if (tio->cor == Vermelho) {
        tio->cor = Preto; //Caso 1
        no->pai->cor = Preto; 

        no->pai->pai->cor = Vermelho; //Caso 1
        no = no->pai->pai; //Caso 1
      } else {
        contInsercaoRb++;
        if (no == no->pai->esquerda) {
          no = no->pai; //Caso 2
          rotacionarDireita(arvore, no, &contInsercaoRb); //Caso 2
        } else {
          no->pai->cor = Preto; 
          no->pai->pai->cor = Vermelho; //Caso 3
          rotacionarEsquerda(arvore, no->pai->pai, &contInsercaoRb); //Caso 3
        }
      }
    }
  }
  contInsercaoRb++;
  arvore->raiz->cor = Preto;
}

void removeArvoreRbRecursivo(RedBlack* arvore, int valor) {
  No* no = localizar(arvore, valor);
  
  contRemocaoRb++;
  if (no != NULL) {
    No* substituto;

    contRemocaoRb++;
    if (no->esquerda == arvore->nulo || no->direita == arvore->nulo) {
      substituto = no;
    } else {

      substituto = sucessor(arvore, no);
    }

    No* filhoSubstituto;
    contRemocaoRb++;
    if (substituto->esquerda != arvore->nulo) {
      filhoSubstituto = substituto->esquerda;
    } else {
      filhoSubstituto = substituto->direita;
    }

    filhoSubstituto->pai = substituto->pai;

    if (substituto->pai == arvore->nulo) {
      contRemocaoRb++;
      arvore->raiz = filhoSubstituto;
    } else if (substituto == substituto->pai->esquerda) {
      contRemocaoRb+=2;
      substituto->pai->esquerda = filhoSubstituto;
    } else {
      contRemocaoRb+=2;
      substituto->pai->direita = filhoSubstituto;
    }

    contRemocaoRb++;
    if (substituto != no) {
      no->valor = substituto->valor;
    }

    contRemocaoRb++;
    if (substituto->cor == Preto) {
      balancearRemocao(arvore, filhoSubstituto);
    }

    free(substituto);
  }
}

void rotacionarDireita(RedBlack* arvore, No* no, unsigned long int* contagem) {
  No* esquerda = no->esquerda;
  no->esquerda = esquerda->direita;
  
  contagem++;
  if (esquerda->direita != arvore->nulo) {
    esquerda->direita->pai = no;
  }
  
  esquerda->pai = no->pai;
  
  if (no->pai == arvore->nulo) {
    contagem++;
    arvore->raiz = esquerda;
  } else if (no == no->pai->esquerda) {
    contagem+=2;
    no->pai->esquerda = esquerda;
  } else {
    contagem+=2;
    no->pai->direita = esquerda;
  }
  
  esquerda->direita = no;
  no->pai = esquerda;
}

void rotacionarEsquerda(RedBlack* arvore, No* no, unsigned long int* contagem) {
  No* direita = no->direita;
  no->direita = direita->esquerda; 

  contagem++;
  if (direita->esquerda != arvore->nulo) {
    direita->esquerda->pai = no;
  }

  direita->pai = no->pai;
  
  if (no->pai == arvore->nulo) {
    contagem++;
    arvore->raiz = direita;
  } else if (no == no->pai->esquerda) {
    contagem+=2;
    no->pai->esquerda = direita;
  } else {
    contagem+=2;
    no->pai->direita = direita;
  }

  direita->esquerda = no;
  no->pai = direita;
}

void balancearRemocao(RedBlack* arvore, No* no) {
  while (no != arvore->raiz && no->cor == Preto) {
    contRemocaoRb+=2;
    if (no == no->pai->esquerda) {
      No* irmao = no->pai->direita;

      contRemocaoRb++;
      if (irmao->cor == Vermelho) {
        irmao->cor = Preto;  //Caso 1
        no->pai->cor = Vermelho; //Caso 1
        rotacionarEsquerda(arvore, no->pai, &contRemocaoRb); //Caso 1
        irmao = no->pai->direita; //Caso 1
      }

      contRemocaoRb++;
      if (irmao->esquerda->cor == Preto && irmao->direita->cor == Preto) {
        irmao->cor = Vermelho; //Caso 2
        no = no->pai; //Caso 2
      } else {
        contRemocaoRb++;
        if (irmao->direita->cor == Preto) {
          irmao->esquerda->cor = Preto; //Caso 3
          irmao->cor = Vermelho; //Caso 3
          rotacionarDireita(arvore, irmao, &contRemocaoRb); //Caso 3
          irmao = no->pai->direita; //Caso 3
        }

        irmao->cor = no->pai->cor; //Caso 4
        no->pai->cor = Preto; //Caso 4
        irmao->direita->cor = Preto; //Caso 4
        rotacionarEsquerda(arvore, no->pai, &contRemocaoRb); //Caso 4
        no = arvore->raiz; //Caso 4
      }
    } else {
      No* irmao = no->pai->esquerda;

      contRemocaoRb++;
      if (irmao->cor == Vermelho) {
        irmao->cor = Preto;  //Caso 1
        no->pai->cor = Vermelho; //Caso 1
        rotacionarDireita(arvore, no->pai, &contRemocaoRb); //Caso 1
        irmao = no->pai->esquerda; //Caso 1
      }

      contRemocaoRb++;
      if (irmao->direita->cor == Preto && irmao->esquerda->cor == Preto) {
        irmao->cor = Vermelho; //Caso 2
        no = no->pai; //Caso 2
      } else {
        contRemocaoRb++;
        if (irmao->esquerda->cor == Preto) {
        irmao->direita->cor = Preto; //Caso 3
        irmao->cor = Vermelho; //Caso 3
        rotacionarEsquerda(arvore, irmao, &contRemocaoRb); //Caso 3
        irmao = no->pai->esquerda; //Caso 3
        }

        irmao->cor = no->pai->cor; //Caso 4
        no->pai->cor = Preto; //Caso 4
        irmao->esquerda->cor = Preto; //Caso 4
        rotacionarDireita(arvore, no->pai, &contRemocaoRb); //Caso 4
        no = arvore->raiz; //Caso 4
      }
    }
  }

  no->cor = Preto;
}

No* sucessor(RedBlack* arvore, No* no) {
  no = no->direita;

  while (no->esquerda != arvore->nulo) {
    contRemocaoRb++;
    no = no->esquerda;
  }
  contRemocaoRb++;

  return no;
}


