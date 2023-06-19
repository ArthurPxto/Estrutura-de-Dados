// Trabalho de Estrutura de Dados
// Minheap
// 08/06/2023
// Arthur Peixoto - github.com/ArthurPxto
// Emanuel Bravo - github.com/bravomanel

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int totalElementos;


int indiceFilhoEsquerdo(int elemento) {
    int indice = 2 * elemento + 1;
    if (indice >= totalElementos) {
        return -1;
    } else {
      return indice;
    }
}

int indiceFilhoDireito(int elemento) {
    int indice = 2 * elemento + 2;
    if (indice >= totalElementos) {
        return -1;
    } else {
      return indice;
    }
}

int indicePai(int elemento) {
    int indice = (int) floor(elemento - 1) / 2;
    if (elemento <= 0 || elemento >= totalElementos) {
        return -1;
    } else {
      return indice;
    }
}

void ajustarSubindo(int *heap, int pos) {
   if (pos != -1) {
      int  pai = indicePai(pos);
      if (pai != -1) {
         if (heap[pai] > heap[pos]) {
            int aux = heap[pai];
            heap[pai] = heap[pos];
            heap[pos] = aux;
            ajustarSubindo(heap, pai);
         }
      }
   }
}

void inserirHeap(int *heap, int elemento) {
   heap[totalElementos] = elemento;
   totalElementos++;

   ajustarSubindo(heap, totalElementos-1);
}

void ajustarDescendo(int *heap, int pos) {
   if (totalElementos == 0) {
      return;
   } else {
      int esq = indiceFilhoEsquerdo(pos);
      int dir = indiceFilhoDireito(pos);
      if (esq == -1) {
         return;
      } else {
         int indiceMenorfilho = esq;
         if (dir != -1 && heap[dir] < heap[esq]) {
            indiceMenorfilho = dir;
         }
         if (heap[indiceMenorfilho] < heap[pos]) {
            int aux = heap[pos];
            heap[pos] = heap[indiceMenorfilho];
            heap[indiceMenorfilho] = aux;
            ajustarDescendo(heap, indiceMenorfilho);
         }
      }
   }
}

int removerHeap(int *heap) {
   if (totalElementos == 0) {
      return -1;
   } else {
      int aux = heap[0];
      heap[0] = heap[totalElementos - 1];
      totalElementos--;
      ajustarDescendo(heap, 0);
      return aux;
   }

}

void imprimirHeap(int *heap) {
   printf("\n");

   for (int i = 0; i < totalElementos; i++) {
      printf("%d ", i);
   }

   printf("\n");
   for (int i = 0; i < totalElementos; i++) {
      printf("%d ", heap[i]);
   }
}

int Menu()
{
    int opc;

    printf("\n\n");
    printf("1 - Inserir elemento\n");
    printf("2 - Remover elemento\n");
    printf("3 - Imprimir heap\n");

    printf("4 - Sair\n");
    printf("Digite a opcao desejada: ");
    scanf("%d", &opc);

    return opc;
}

int main()
{

   int n;

   printf("\nDigite o tamanho máximo da minheap: ");
   scanf("%d", &n);

   int heap[n];
   totalElementos = 0;

    while (1)
    {    
        switch (Menu())
        {
        case 1 : 
        {
            int elemento = 0;

            printf("Digite o elemento: ");
            scanf("%d", &elemento);

            inserirHeap(heap, elemento);

            break;
        }
        case 2:
        {   
           int elementoRemovido = removerHeap(heap);

           printf("\nElemento removido: %d", elementoRemovido);
            break;
        }
        case 3:
        {
            imprimirHeap(heap);
            break;
        }

        case 4:
        {
            exit(0);
            break;
        }
        default:
            printf("Opcao invalida!\n");
            break;
        }
    }

    return 0;
}