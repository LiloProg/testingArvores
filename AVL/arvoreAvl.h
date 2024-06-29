typedef struct no_avl
{
    struct no_avl *pai;
    struct no_avl *esquerda;
    struct no_avl *direita;
    int altura;
    int valor;
} NoAvl;

typedef struct arvore_avl
{
    struct no_avl *raiz;
} ArvoreAvl;

unsigned long int contInsercaoAvl;
unsigned long int contRemocaoAvl;

unsigned long int getContInvercaoAvl();

unsigned long int getContRemocaoAvl();

ArvoreAvl* criaArvoreAvl();

NoAvl *addArvoreAvl(ArvoreAvl * arvore, int valor);

NoAvl* removeArvoreAvl(ArvoreAvl * arvore, int valor);
