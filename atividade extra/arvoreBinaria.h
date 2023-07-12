#ifndef arvoreBinaria_h
#define arvoreBinaria_h

typedef struct arvore *Arvore;

Arvore inicializarArvore();

int verificarSeExiste(Arvore a, int x);

void *retornarElemento(Arvore a, int x, void *info, int *tipo);

int calcularAltura(Arvore a);

void imprimirLargura(Arvore a, int noDesejado);

void imprimirArvore(Arvore a);

Arvore inserir(Arvore a, int chave, int chavePai, char direcao, void *info, int tipo);

Arvore liberarArvore(Arvore a);

#endif