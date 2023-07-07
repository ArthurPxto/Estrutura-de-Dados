#include <stdio.h>
#include <stdlib.h>
#include "arvoreBinaria.h"
#include <math.h>

struct arvore
{
    int chave;
    void *info;
    struct arvore *esq;
    struct arvore *dir;
};

Arvore inserir(Arvore a, int chave, char direção, void *info)
{
    if(a->chave == -1){
        a->chave = chave;
        a->info = info;
        return a;
    }
    if (a == NULL)
    {
        a = (Arvore)malloc(sizeof(Arvore));
        a->chave = chave;
        a->info = info;
        a->esq = NULL;
        a->dir = NULL;
    }
    else
    {
        if (direção == 'e')
        {
            a->esq = inserir(a->esq, chave, direção, info);
        }
        else
        {
            a->dir = inserir(a->dir, chave, direção, info);
        }
    }
    return a;
}

Arvore inicializarArvore()
{
    Arvore a = (Arvore)malloc(sizeof(struct arvore));
    a->esq = NULL;
    a->dir = NULL;
    a->chave = -1;
    return a;
}

int calcularAltura(Arvore a)
{

    int hd, he;

    if (a == NULL)
        return 0;
    else
    {
        he = altura(a->esq);
        hd = altura(a->dir);
        if (he > hd)
            return he + 1;
        else
            return hd + 1;
    }
}

void imprimirLargura(Arvore a, int noDesejado)
{
    if (a != NULL)
    {
        if (noDesejado == 0)
        {
            printf("[%d]", a->info);
        }
        else
        {
            ImprimirLargura(a->esq, noDesejado - 1);
            ImprimirLargura(a->dir, noDesejado - 1);
        }
    }
}

Arvore liberarArvore(Arvore a)
{
  if (a != NULL) {
    Libera(a->esq);
    Libera(a->dir);
    free(a);
  }
  return NULL;
}

int verificarSeExiste(Arvore a, int x)
{
    if (a == NULL)
    {
        return 0;
    }
    else
    {
        if (a->chave == x)
        {
            return 1;
        }
        else
        {
            return verificarSeExiste(a->esq, x) || verificarSeExiste(a->dir, x);
        }
    }
}

void *retornarElemento(Arvore a, int x, void *info)
{
    if(verificarSeExiste(a,x))
    {
        Arvore aux = buscarElemento(a,x);
        printf("O elemento é: %d", aux->chave);
        void *retorno = aux->info;
        return retorno;
    }

}

Arvore buscarElemento(Arvore a, int x)
{
    if (a == NULL)
    {
        return NULL;
    }
    else
    {
        if (a->chave == x)
        {
            return a;
        }
        else
        {
            return buscarElemento(a->esq, x) || buscarElemento(a->dir, x);
        }
    }
}