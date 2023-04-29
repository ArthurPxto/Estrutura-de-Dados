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

//implementada busca em arvore binaria de busca
int Busca(arvore *a, int x) {
  if (a == NULL)
    return 0;
  else {
    if (a->info == x)
      return 1;
    else if (x < a->info)
      if(Busca(a->esq, x) == 1) 
      return 1;
    else
      return Busca(a->dir, x);
  }
}

// int ContarElementos(arvore *a, int *n) {
//   if (a != NULL) {
//     ContarElementos(a->esq, n);
//     *n = *n + 1;
//     ContarElementos(a->dir, n);
//   }
//   return *n;
// }

void ImprimirNosFolhas(arvore *a) {

  if (a != NULL) {
    if (a->esq == NULL && a->dir == NULL) {
      printf(" [%d]", a->info);
    } else {
      ImprimirNosFolhas(a->esq);
      ImprimirNosFolhas(a->dir);
    }
  }
}

//implementada em arvore binaria de busca
void ImprimirNivelNo(arvore *a, int x,int nivel){

    if(a != NULL){
      if(a->info == x){
        printf("\n nivel[%d]", nivel);
      }
      else{
        if(x < a->info)
        ImprimirNivelNo(a->esq, x, nivel + 1);
        else
        ImprimirNivelNo(a->dir, x, nivel + 1);

      }
    }
  

}

//implementada inserir em arvore binaria de busca
arvore *InserirNo(arvore *a, int x) {

  if (a == NULL) {
    a = (arvore *)malloc(sizeof(arvore));
    a->info = x;
    a->esq = NULL;
    a->dir = NULL;
  } else {
    if (x < a->info)
      a->esq = InserirNo(a->esq, x);
    else
      a->dir = InserirNo(a->dir, x);
  }
  return a;
}

arvore *RemoverNo(arvore* a, int x){
  
}

arvore *Libera(arvore *a) {
  if (a != NULL) {
    Libera(a->esq);
    Libera(a->dir);
    free(a);
  }
  return NULL;
}

int menu() {

  int opc;

  printf("\n------- Menu ------- \n");
  printf("1) Ler uma arvore \n");
  printf("2) Imprimir a arvore \n");
  printf("3) Buscar um elemento na arvore \n");
  printf("4) Imprimir o nivel de um no \n");
  printf("5) Imprimir as folhas menores que um valor x \n");
  printf("6) inserir um nó na arvore \n");
  printf("7) remover um nó da arvore \n");
  printf("8) Sair \n");
  printf("-------------------- \n");

  printf("\n Digite a opcao desejada: ");
  scanf("%d", &opc);

  return opc;
}

int main() {

  int opc, n = 0, *p;

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

      int ordem;

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

        int noDesejado;

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

      int info;

      printf(" \n Qual elemento deseja buscar? ");
      scanf("%d", &info);

      if (Busca(a, info) == 1) {
        printf("\n Elemento encontrado! \n");
      } else {
        printf("\n O elemento nao esta na arvore! \n ");
      }

      break;
    case 4:
      
      int n = 0, noDesejado;

      printf("Digite o o elemento desejado: ");
      scanf("%d", &noDesejado);

      ImprimirNivelNo(a , noDesejado, n);

      break;
    case 5://imprimir folhas menores que x

      ImprimirNosFolhas(a);

      break;
    case 6:// inserir no

      int valor;

      printf("qual valor deseja inserir? ");
      scanf("%d", &valor);

      a = InserirNo(a, valor);

      break;
    case 7://remover no


      break;
    case 8:

      Libera(a);

      return 0;

      break;

    default:
      printf("Opcao nao encontrada, tente novamente!\n ");
      break;
    }
  }
}
