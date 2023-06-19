#include <stdlib.h>
#include <stdio.h>
#include "fila.h"

int top = 0;

int menu(int opc)
{
    printf("\n\n menu \n\n");
    printf("1 - Inserir\n");
    printf("2 - Remover\n");
    printf("3 - Printar\n");
    printf("4 - Sair\n");
    printf("Opcao: ");
    scanf("%d", &opc);

    return opc;
}

void imprimirFila(int *vet)
{
    printf("Fila:\n");
    for(int i = 0; i < top; i++)
    {
        printf("[%d]", vet[i]);
    }
}

int *inserirFila(int *vet)
{
    int x;

    printf("Digite o valor a ser inserido: ");
    scanf("%d", &x);

    vet[top] = x;
    top++;

    return vet;
}

int *removerFila(int *vet)
{
    int x, verificador = 0;

    printf("Digite o valor a ser removido: ");
    scanf("%d", &x);

    for(int i = 0; i < top; i++)
    {
        if(vet[i] == x)
        {
            printf("elemento %d removido\n", x);
            verificador = 1;
            for(int j = i; j < top; j++)
            {
                vet[j] = vet[j + 1];
            }
        }
    }

    if(verificador == 0)
        printf("elemento %d nao encontrado\n", x);
    else
        top--;
    
    return vet;
}