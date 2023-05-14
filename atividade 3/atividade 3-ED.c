#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// alunos: Arthur Peixoto / Emanuel Bravo;

typedef struct arvore {
  int info;
  int fb;
  struct arvore *esq;
  struct arvore *dir;
} arvore;

int altura (arvore *a) {
   if (a == NULL) {
      return -1;
   } else {
      int he = altura(a->esq);
      int hd = altura(a->dir);
      if (he < hd) {
         return hd + 1;
      } else {
         return he + 1;
      }
   }
}

void ajustarFB (arvore *a) {
   if (a != NULL) {
      a->fb = altura(a->dir) - altura(a->esq);
      printf("\nFB: %d", a->fb);
      ajustarFB(a->esq);
      ajustarFB(a->dir);
   }
}


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
    ajustarFB(a);
    return a;
  }
}

arvore *rotacaoSimplesDireita(arvore *a) {
   printf("\n  --  %d  --  Rodando para direita", a->info);
   if (a->esq == NULL) {
      printf("\na esq = NULL");
   } else if (a->dir == NULL) {
      printf("\na dir = NULL");
   } else {
      printf("\n  %d  --  %d  Rodando para direita", a->esq->info, a->dir->info);
   }
   arvore *b = a->esq;
   if (b == NULL) {
      return a;
   }
   a->esq = b->dir;
   b->dir = a;
   a->fb = altura(a->dir) - altura(a->esq);
   b->fb = altura(b->dir) - altura(b->esq);
   return b;
}

arvore *rotacaoSimplesEsquerda(arvore *a) {
   printf("\n  --  %d  --  Rodando para esquerda", a->info);
   if (a->esq == NULL) {
      printf("\na esq = NULL");
   } else if (a->dir == NULL) {
      printf("\na dir = NULL");
   } else {
      printf("\n  %d  --  %d  Rodando para esquerda", a->esq->info, a->dir->info);
   }
   arvore *b = a->dir;
   if (b == NULL) {
      return a;
   }
   a->dir = b->esq;
   b->esq = a;
   a->fb = altura(a->dir) - altura(a->esq);
   b->fb = altura(b->dir) - altura(b->esq);
   return b;
}

arvore *balanceiaArvore(arvore *a) {
   if (a != NULL) {
      if (a->fb == -2) {
         if (a->esq->fb == 1) {
            a = rotacaoSimplesEsquerda(a); // Rotação Dupla
         }
         a = rotacaoSimplesDireita(a);
         a->fb = altura(a->dir) - altura(a->esq);
      } else if (a->fb == 2) {
         if (a->dir->fb == -1) {
            a = rotacaoSimplesDireita(a); // Rotação Dupla
         }
         a = rotacaoSimplesEsquerda(a);
         a->fb = altura(a->dir) - altura(a->esq);
      }
      return a;
   } else {
      return NULL;
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

//Implementada busca em arvore binaria de busca
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

void ImprimirNosFolhasMenoresQueX(arvore *a, int valor) {
  // Verifica se o nó atual é nulo
  if (a != NULL) {
    // Verifica se a->esq e a-> direita e nulo
    // Se forem nulos ele printa
    if (a->esq == NULL && a->dir == NULL) {
      if (a->info < valor) {
         printf(" [%d]", a->info);
      }
    } else if (a->info >= valor) { // Se o valor do nó atual for maior que o valor passado ele vai para a esquerda
      ImprimirNosFolhasMenoresQueX(a->esq, valor);
    } else {
      ImprimirNosFolhasMenoresQueX(a->esq, valor);
      ImprimirNosFolhasMenoresQueX(a->dir, valor);
    }
  }
}

//Implementada em arvore binaria de busca
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

//Implementada inserir em arvore binaria de busca
arvore *InserirNo(arvore *a, int x) {

  if (a == NULL) {
    a = (arvore *)malloc(sizeof(arvore));
    a->info = x;
    a->esq = NULL;
    a->dir = NULL;
  } else {
    if (x < a->info) {
      a->esq = InserirNo(a->esq, x);
      a->fb = altura(a->dir) - altura(a->esq);
      a = balanceiaArvore(a);
    }
    else {
      a->dir = InserirNo(a->dir, x);
      a->fb = altura(a->dir) - altura(a->esq);
      a = balanceiaArvore(a);
    }
  }
  return a;
}

//Implementada remover em arvore binaria de busca
arvore *RemoverNo(arvore* a, int x){
  if(a != NULL){
    if(x < a->info)
      a->esq = RemoverNo(a->esq, x);
    else if(x > a->info)
      a->dir = RemoverNo(a->dir, x);
    else{
      //Se for folha
      if(a->esq == NULL && a->dir == NULL){
        free(a);
        a = NULL;
        return a;
      }
      //Se tiver um filho para a direita
      else if(a->esq == NULL){
        arvore *aux = a;
        a = a->dir;
        free(aux);
        return a;
      }
      //Se tiver um filho para a esquerda
      else if(a->dir == NULL){
        arvore *aux = a;
        a = a->esq;
        free(aux);
        return a;
      }
      //Se tiver dois filhos
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
    return a;
  }
   else{
      return NULL;
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
  printf("5) Imprimir as folhas menores que um valor X \n");
  printf("6) Inserir um no na arvore \n");
  printf("7) Remover um no da arvore \n");
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
        printf("\n !! Erro ao abrir o arquivo entrada.txt !! \n");
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

      //   printf("Digite o nivel desejado:	");
      //   scanf("%d", &noDesejado);

      for (int i = 0; i <= altura(a); i++) {
        printf("\nH = %d", i);
        ImprimirLargura(a, i);
      }

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
    case 5: //Imprimir folhas menores que X

      printf("Digite o valor: ");
      scanf("%d", &valor);

      ImprimirNosFolhasMenoresQueX(a, valor);

      break;
    case 6: // Inserir no

      printf("\nQual valor deseja inserir? ");
      scanf("%d", &valor);

      printf("\n Inserindo o no %d na arvore:\n", valor);
      ImprimirOrdem(a);

      a = InserirNo(a, valor);

      printf("\n Arvore apos insercao: \n");
      ImprimirOrdem(a);

      break;
    case 7: //Remover no

      printf("Qual valor deseja remover? ");
      scanf("%d", &valor);

      printf("\n Removendo o no %d na arvore:\n", valor);
      ImprimirOrdem(a);

      a = RemoverNo(a, valor);

      printf("\n Arvore apos remocao: \n");
      ImprimirOrdem(a);

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
