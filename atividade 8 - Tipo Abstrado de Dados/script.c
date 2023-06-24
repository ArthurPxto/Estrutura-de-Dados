// Trabalho de Estrutura de Dados
// Tipo Abstrato de Dados
// 20/06/2023
// Arthur Peixoto - github.com/ArthurPxto
// Emanuel Bravo - github.com/bravomanel

#include <stdlib.h>
#include <stdio.h>
#include "fila.h"

// capacidade maxima da fila
#define N 5

// declarando a fila
struct fila
{
    int vet[N];
    int top;
};

// limpa a tela
void limpaTela()
{
    fflush(stdin);
    printf("\n aperte um enter para continuar...");
    getchar();
    system("cls");
}

// libera a fila e retorna NULL
void liberarFila(Fila f)
{
    free(f);
}

// cria a fila com o tamanho do vetor inserido pelo usuario
Fila criarFila()
{
    Fila f = (Fila)malloc(sizeof(struct fila));

    f->top = 0;

    return f;
}

// mostra o menu
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

// imprime a fila na tela
void imprimirFila(Fila f)
{
    printf("Fila:\n");
    for (int i = 0; i < f->top; i++)
    {
        printf("[%d]", f->vet[i]);
    }
    printf("\n");
}

// insere um numero e retorna a fila modificada
Fila inserirFila(Fila f)
{
    if (f->top == N)
    {
        printf("Fila cheia\n");
        return f;
    }

    int x;

    printf("Digite o valor a ser inserido: ");
    scanf("%d", &x);

    f->vet[f->top] = x;
    f->top++;

    printf("elemento %d inserido com sucesso!\n", x);

    return f;
}

// remove um numero e retorna a fila modificada
Fila removerFila(Fila f)
{
    if (f->top == 0)
    {
        printf("Fila vazia\n");
        return f;
    }

    int x, verificador = 0;

    x = f->vet[0];

    printf("elemento %d removido com sucesso\n", x);
    verificador = 1;
    for (int j = 0; j < f->top; j++)
    {
        f->vet[j] = f->vet[j + 1];
    }

    if (verificador == 0)
        printf("elemento %d nao encontrado\n", x);
    else
        f->top--;

    return f;
}