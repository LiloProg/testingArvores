enum coloracao { Vermelho, Preto };
typedef enum coloracao Cor;

typedef struct no {
  struct no* pai;
  struct no* esquerda;
  struct no* direita;
  Cor cor;
  int valor;
} No;

typedef struct arvore {
  struct no* raiz;
  struct no* nulo; 
} RedBlack;

extern unsigned long int contInsercaoRb;
extern unsigned long int contRemocaoRb;

RedBlack* criaArvoreRb();
No* addArvoreRb(RedBlack* arvore, int valor);
void removeArvoreRb(RedBlack* arvore, int valor);
unsigned long int getContInvercaoRb();
unsigned long int getContRemocaoRb();