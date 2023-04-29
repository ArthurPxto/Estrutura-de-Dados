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
  if (a == NULL){
    return 0;
  }
  else {
    if (a->info == x){
      return 1;
    }
    else if(x < a->info){
      if(Busca(a->esq, x) == 1) 
      return 1;
    }
    else{
      return Busca(a->dir, x);
    }
  }
}

void ImprimirNosFolhasMenoresQueX(arvore *a, int x) {

  if (a != NULL) {
    if (a->esq == NULL && a->dir == NULL) {
      printf(" [%d]", a->info);
    } else {
      if(a->info < x){
        ImprimirNosFolhasMenoresQueX(a->dir, x);
      }
      else if(a->info > x){
        ImprimirNosFolhasMenoresQueX(a->esq, x);
      }
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

//implementada remover em arvore binaria de busca
arvore *RemoverNo(arvore* a, int x){
  if(a != NULL){
    if(x < a->info)
      a->esq = RemoverNo(a->esq, x);
    else if(x > a->info)
      a->dir = RemoverNo(a->dir, x);
    else{
      //se for folha
      if(a->esq == NULL && a->dir == NULL){
        free(a);
        a = NULL;
        return a;
      }
      //se tiver um filho para a direita
      else if(a->esq == NULL){
        arvore *aux = a;
        a = a->dir;
        free(aux);
        return a;
      }
      //se tiver um filho para a esquerda
      else if(a->dir == NULL){
        arvore *aux = a;
        a = a->esq;
        free(aux);
        return a;
      }
      //se tiver dois filhos
      else{
        arvore *aux = a->esq;
        while(aux->dir != NULL){
          aux = aux->dir;
        }
        a->info = aux->info;
        aux->info = x;
        a->esq = RemoverNo(a->esq, x);
        return a;
      }
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

  int opc, n = 0, info , valor, noDesejado , ordem;

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

      printf("Digite o o elemento desejado: ");
      scanf("%d", &noDesejado);

      ImprimirNivelNo(a , noDesejado, n);

      break;
    case 5://imprimir folhas menores que x

      printf("qual o filtro de impressao?");
      scanf("%d", &valor);

      ImprimirNosFolhasMenoresQueX(a, valor);

      break;
    case 6:// inserir no

      printf("qual valor deseja inserir? ");
      scanf("%d", &valor);

      a = InserirNo(a, valor);

      break;
    case 7://remover no

      printf("qual valor deseja remover? ");
      scanf("%d", &valor);

      a = RemoverNo(a, valor);

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
