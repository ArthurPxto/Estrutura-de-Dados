#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// alunos: Arthur Peixoto / Emanuel Bravo;

typedef struct arvore {
  int info;
  struct arvore *esq;
  struct arvore *dir;
} arvore;

arvore *LerArvore(FILE *arq) {
  arvore *a;
  char c;
  int num;

  if (fscanf(arq, "%c", &c) == EOF || c != '(') {
    printf("Erro: arquivo mal formatado. Falta um parenteses abrindo.\n");
    return NULL;
  }

  if (fscanf(arq, "%d", &num) == EOF) {
    printf("Erro: arquivo mal formatado. Falta o valor do nó.\n");
    return NULL;
  }

  if (num == -1) {
    if (fscanf(arq, "%c", &c) == EOF || c != ')') {
      printf("Erro: arquivo mal formatado. Falta um parenteses fechando.\n");
      return NULL;
    }
    return NULL;
  } else {
    a = (arvore *)malloc(sizeof(arvore));

    a->info = num;
    a->esq = LerArvore(arq);
    a->dir = LerArvore(arq);

    if (fscanf(arq, "%c", &c) == EOF || c != ')') {
      printf("Erro: arquivo mal formatado. Falta um parenteses fechando.\n");
      return NULL;
    }
    return a;
  }
}

void ImprimirPreOrdem(arvore *a) {
  if (a != NULL) {
    printf("%d ", a->info);
    ImprimirPreOrdem(a->esq);
    ImprimirPreOrdem(a->dir);
  }
}

void ImprimirOrdem(arvore *a) {
  if (a != NULL) {
    ImprimirOrdem(a->esq);
    printf("%d ", a->info);
    ImprimirOrdem(a->dir);
  }
}

void ImprimirPosOrdem(arvore *a) {

  if (a != NULL) {
    ImprimirPosOrdem(a->esq);
    ImprimirPosOrdem(a->dir);
    printf("%d ", a->info);
  }
}

int menu() {

  int opc;

  printf("\n------- Menu ------- \n");
  printf("1) Ler uma arvore \n");
  printf("2) Imprimir a arvore \n");
  printf("3) Buscar um elemento na arvore \n");
  printf("4) Contar o numero de elementos na arvore \n");
  printf("5) Imprimir as folhas das arvore \n");
  printf("6) Verificar se uma arvore esta balanceada \n");
  printf("7) Verificar se uma arvore e cheia \n");
  printf("8) Imprimir o nivel de um no \n");
  printf("9) Sair \n");
  printf("-------------------- \n");

  printf("\n Digite a opcao desejada: ");
  scanf("%d", &opc);

  return opc;
}

int Busca(arvore *a, int x) {
  if (a == NULL)
    return 0;
  else {
    if (a->info == x)
      return 1;
    else if (Busca(a->esq, x) == 1)
      return 1;
    else
      return Busca(a->dir, x);
  }
}

int ContarElementos(arvore *a, int *n) {

  if (a != NULL) {

    ContarElementos(a->esq, n);
    *n = *n + 1;
    ContarElementos(a->dir, n);
  }

  return *n;
}

void ImprimirNosFolhas(arvore *a) {
  // verifica se o nó atual é nulo
  if (a != NULL) {
    // verifica se a->esq e a-> direita e nulo
    // se forem nulos ele printa
    if (a->esq == NULL && a->dir == NULL) {
      printf(" [%d]", a->info);
    } else {
      ImprimirNosFolhas(a->esq);
      ImprimirNosFolhas(a->dir);
    }
  }
}

int altura(arvore *a) {

  int hd, he;

  if (a == NULL)
    return 0;
  else {
    he = altura(a->esq);
    hd = altura(a->dir);
    if (he > hd)
      return he + 1;
    else
      return hd + 1;
  }
}

void ImprimirLargura(arvore *a, int noDesejado) {
  if (a != NULL) {
    if (noDesejado == 0) {
      printf("[%d]", a->info);
    } else {
      ImprimirLargura(a->esq, noDesejado - 1);
      ImprimirLargura(a->dir, noDesejado - 1);
    }
  }
}
// revisar função
int ArvoreBalaceada(arvore *a) {
  if (a != NULL) {
    int heightDireita, heightEsquerda;
    heightDireita = altura(a->dir);
    heightEsquerda = altura(a->esq);
    if (heightDireita - heightEsquerda > 1 ||heightEsquerda - heightDireita > 1) {
      return 1;
    }
    else {
      ArvoreBalaceada(a->esq);
      ArvoreBalaceada(a->dir);
    }
  } 
  else
   return 0;
}

int ArvoreCheia(arvore *a, int *n) {

   int h = altura(a);

   *n = ContarElementos(a, n);

   printf("\n altura[%d] \n \n", h);
   printf("\n elementos[%d] \n \n", *n);

   if(*n == pow(2, h) - 1)
     return 1;
   else
      return 0;

}

void ImprimirNivelNo(arvore *a, int x,int nivel){

    if(a != NULL){
      if(a->info == x){
        printf("\n nivel[%d]", nivel);
      }
      else{

        ImprimirNivelNo(a->esq, x, nivel + 1);
        ImprimirNivelNo(a->dir, x, nivel + 1);

      }
    }
  

}

arvore *Libera(arvore *a) {
  if (a != NULL) {
    Libera(a->esq);
    Libera(a->dir);
    free(a);
  }
  return NULL;
}

int main() {

  int opc, ordem, info, n = 0, *p, noDesejado;

  p = &n;

  arvore *a = NULL;

  FILE *arq;

  while (1) {

    switch (opc = menu()) {

    case 1:

      arq = fopen("entrada.txt", "r");

      if (arq == NULL) {
        printf("\n !! Erro ao abrri o arquivo entrada.txt !! \n");
        return 1;
      }

      a = LerArvore(arq);

      fclose(arq);

      printf("\nSucesso: Arquivo lido! \n");

      break;
    case 2:
      printf("1) Pre-ordem \n");
      printf("2) Ordem \n");
      printf("3) Pos-ordem \n");
      printf("4) Largura \n");
      printf("Selecione a ordem da arvore: ");
      scanf("%d", &ordem);

      switch (ordem) {
      case 1:

        ImprimirPreOrdem(a);

        break;
      case 2:

        ImprimirOrdem(a);

        break;
      case 3:

        ImprimirPosOrdem(a);

        break;
      case 4:

        printf("Digite o nivel desejado:	");
        scanf("%d", &noDesejado);
        ImprimirLargura(a, noDesejado);

        break;
      default:
        printf("opcao invalida! \n");
        break;
      }

      break;
    case 3:

      printf(" \n Qual elemento deseja buscar? ");
      scanf("%d", &info);

      if (Busca(a, info) == 1) {
        printf("\n Elemento encontrado! \n");
      } else {
        printf("\n O elemento nao esta na arvore! \n ");
      }

      break;
    case 4:


      n = ContarElementos(a, p);

      printf("Existem %d elementos nessa arvore", n);

      break;
    case 5:

      ImprimirNosFolhas(a);

      break;
    case 6:

      if (ArvoreBalaceada(a) == 1) {
        printf("A arvore nao esta balanceada! \n");
      } else {
        printf("A arvore esta balanceada! \n");
      }

      break;
    case 7:

      if (ArvoreCheia(a, p) == 1) {
        printf("A arvore esta cheia! \n");
      } else {
        printf("A arvore nao esta cheia! \n");
      }

      break;
    case 8:

      n = 0;

      printf("Digite o o elemento desejado: ");
      scanf("%d", &noDesejado);

      ImprimirNivelNo(a , noDesejado, n);

      break;
    case 9:

      Libera(a);

      return 0;

      break;

    default:
      printf("Opcao nao encontrada, tente novamente!\n ");
      break;
    }
  }
}
