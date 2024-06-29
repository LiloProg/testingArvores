#include <stdio.h>
#include <stdlib.h>
#include "arvoreAvl.h"

NoAvl * noNovo(int valor);
int fatorBalanceamento(NoAvl *no);
int altura(NoAvl *no);
int max(int a, int b);
NoAvl *rse(NoAvl *no, ArvoreAvl * arvore);
NoAvl *rsd(NoAvl *no, ArvoreAvl * arvore);
NoAvl* rde(NoAvl* no, ArvoreAvl * arvore);
NoAvl* rdd(NoAvl* no, ArvoreAvl * arvore);

unsigned long int getContInvercaoAvl() {
    return contInsercaoAvl;
}

unsigned long int getContRemocaoAvl() {
    return contRemocaoAvl;
}

ArvoreAvl* criaArvoreAvl() {
    ArvoreAvl* arvore = (ArvoreAvl*) malloc(sizeof(ArvoreAvl));
    arvore->raiz = NULL;
    return arvore;
}

NoAvl *addArvoreAvlRecursivo(ArvoreAvl * arvore, NoAvl * no , int valor) {
    
    contInsercaoAvl++; //CONT INSERTION
    if (no == NULL) {
        no = noNovo(valor);
        contInsercaoAvl++; //CONT INSERTION
        if(arvore->raiz == NULL) arvore->raiz = no;
        return no;
    } 
  
    if (valor < no->valor) {
        contInsercaoAvl++; //CONT INSERTION
        no->esquerda  = addArvoreAvlRecursivo(arvore, no->esquerda, valor); 
        no->esquerda->pai = no;
    }
    else if (valor > no->valor) {
        contInsercaoAvl += 2; //CONT INSERTION
        no->direita = addArvoreAvlRecursivo(arvore, no->direita, valor);
        no->direita->pai = no;
    }
    else {
        contInsercaoAvl += 2; //CONT INSERTION
        return no;
    }
  
    no->altura = 1 + max(altura(no->esquerda), altura(no->direita)); 
  
    int fb = fatorBalanceamento(no);
  
    contInsercaoAvl++; //CONT INSERTION
    if (fb > 1 && valor < no->esquerda->valor) 
        return rsd(no, arvore); 

    contInsercaoAvl++; //CONT INSERTION
    if (fb < -1 && valor > no->direita->valor) 
        return rse(no, arvore); 
  
    contInsercaoAvl++; //CONT INSERTION
    if (fb > 1 && valor > no->esquerda->valor) 
        return rdd(no, arvore);
    
    contInsercaoAvl++; //CONT INSERTION
    if (fb < -1 && valor < no->direita->valor) 
        return rde(no, arvore);
  
    return no; 
}

NoAvl *addArvoreAvl(ArvoreAvl * arvore, int valor) { 
    contInsercaoAvl = 0;
    return addArvoreAvlRecursivo(arvore, arvore->raiz, valor);
}

NoAvl * minValueNode(NoAvl* no) 
{ 
    NoAvl* current = no; 
 
    while (current->esquerda != NULL) {
        contRemocaoAvl++; //CONT REMOVAL
        current = current->esquerda;
    } 
    contRemocaoAvl++; //CONT REMOVAL

    return current; 
} 

NoAvl* removeArvoreAvlRecursivo(ArvoreAvl * arvore , NoAvl* no, int valor) 
{ 
    contRemocaoAvl++; //CONT REMOVAL
    if (no == NULL) 
        return no; 
 
    if ( valor < no->valor ) {
        contRemocaoAvl++; //CONT REMOVAL
        no->esquerda = removeArvoreAvlRecursivo(arvore, no->esquerda, valor);
    }  
    else if( valor > no->valor ) {
        contRemocaoAvl += 2; //CONT REMOVAL
        no->direita = removeArvoreAvlRecursivo(arvore, no->direita, valor);    
    }
    else
    { 
        contRemocaoAvl += 2; //CONT REMOVAL

        contRemocaoAvl++; //CONT REMOVAL
        if( (no->esquerda == NULL) ||
            (no->direita == NULL) ) 
        { 
            contRemocaoAvl++; //CONT REMOVAL
            NoAvl *noDeletar = no->esquerda ? 
                         no->esquerda : 
                         no->direita; 

            contRemocaoAvl++; //CONT REMOVAL
            if (noDeletar == NULL) 
            { 
                noDeletar = no; 
                no = NULL; 
            } 
            else 
            {
                NoAvl * temp = no;
                no = noDeletar;
                noDeletar = temp;
            }

            contRemocaoAvl++; //CONT REMOVAL
            if(noDeletar == arvore->raiz) arvore->raiz = no;
            free(noDeletar); 
        } 
        else
        { 
            NoAvl* temp = minValueNode(no->direita); 
 
            no->valor = temp->valor; 
 
            no->direita = removeArvoreAvlRecursivo(arvore, no->direita, temp->valor); 
        } 
    } 
  
    contRemocaoAvl++; //CONT REMOVAL
    if (no == NULL) return no; 
  
    no->altura = 1 + max(altura(no->esquerda), altura(no->direita)); 
 
    int fb = fatorBalanceamento(no); 
 
    contRemocaoAvl++; //CONT REMOVAL
    if (fb > 1 && fatorBalanceamento(no->esquerda) >= 0) 
        return rsd(no, arvore); 
 
    contRemocaoAvl++; //CONT REMOVAL
    if (fb > 1 && fatorBalanceamento(no->esquerda) < 0) 
        return rdd(no, arvore); 
 
    contRemocaoAvl++; //CONT REMOVAL
    if (fb < -1 && fatorBalanceamento(no->direita) <= 0) 
        return rse(no, arvore); 
 
    contRemocaoAvl++; //CONT REMOVAL
    if (fb < -1 && fatorBalanceamento(no->direita) > 0) 
        return rde(no, arvore);
 
    return no; 
}

NoAvl* removeArvoreAvl(ArvoreAvl * arvore, int valor) 
{
    contRemocaoAvl = 0;
    return removeArvoreAvlRecursivo(arvore, arvore->raiz, valor);
}

NoAvl * noNovo(int valor) 
{ 
    NoAvl *no = (NoAvl*)malloc(sizeof(NoAvl));
    no->pai = NULL;
    no->esquerda = NULL;
    no->direita = NULL;
    no->valor = valor; 
    no->altura = 1; //intancia um novo no como folha
    return no;
}

int altura(NoAvl *no)
{
    contRemocaoAvl++; //CONT REMOVAL
    contInsercaoAvl++; //CONT INSERTION
    if(no == NULL) return 0;
    return no->altura;
}

int max(int a, int b) 
{ 
    contRemocaoAvl++; //CONT REMOVAL
    contInsercaoAvl++; //CONT INSERTION
    return (a > b)? a : b; 
} 

int fatorBalanceamento(NoAvl *no)
{
    contRemocaoAvl++; //CONT REMOVAL
    contInsercaoAvl++; //CONT INSERTION
    if (no == NULL) 
        return 0; 
    return altura(no->esquerda) - altura(no->direita); 
}

NoAvl *rse(NoAvl *no, ArvoreAvl * arvore)
{
    NoAvl *pai = no->pai;
    NoAvl *direita = no->direita;

    no->direita = direita->esquerda;
    contInsercaoAvl++; //CONT INSERTION
    contRemocaoAvl++; //CONT REMOVAL
    if(no->direita != NULL) no->direita->pai = no;

    no->pai = direita;
    direita->esquerda = no;
    direita->pai = pai;

    contInsercaoAvl++; //CONT INSERTION
    contRemocaoAvl++; //CONT REMOVAL
    if(arvore->raiz == no) arvore->raiz = direita;

    no->altura = max(altura(no->esquerda), 
                    altura(no->direita)) + 1; 
    direita->altura = max(altura(direita->esquerda), 
                    altura(direita->direita)) + 1; 

    return direita;
}

NoAvl *rsd(NoAvl *no, ArvoreAvl * arvore)
{
    NoAvl *pai = no->pai;
    NoAvl *esquerda = no->esquerda;

    no->esquerda = esquerda->direita;
    contInsercaoAvl++; //CONT INSERTION
    contRemocaoAvl++; //CONT REMOVAL
    if(no->esquerda != NULL) no->esquerda->pai = no;

    no->pai = esquerda;
    esquerda->direita = no;
    esquerda->pai = pai;

    contInsercaoAvl++; //CONT INSERTION
    contRemocaoAvl++; //CONT REMOVAL
    if(arvore->raiz == no) arvore->raiz = esquerda;

    no->altura = max(altura(no->esquerda), 
                    altura(no->direita)) + 1; 
    esquerda->altura = max(altura(esquerda->esquerda), 
                    altura(esquerda->direita)) + 1;

    return esquerda;
}

NoAvl* rde(NoAvl* no, ArvoreAvl * arvore) {
    no->direita = rsd(no->direita, arvore);
    return rse(no, arvore);
}

NoAvl* rdd(NoAvl* no, ArvoreAvl * arvore) {
    no->esquerda = rse(no->esquerda, arvore);
    return rsd(no, arvore);
}
