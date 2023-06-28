// Trabalho de Estrutura de Dados
// Tipo Abstrato de Dados
// 20/06/2023
// Arthur Peixoto - github.com/ArthurPxto
// Emanuel Bravo - github.com/bravomanel

#include <stdlib.h>
#include <stdio.h>
#include "fila.h"

void limpaTela()
{
    fflush(stdin);
    printf("\n aperte um enter para continuar...");
    getchar();
    system("cls");
}

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

int main()
{
    int opc;

    Fila f = criarFila();

    while (1)
    {
        opc = menu(opc);

        switch (opc)
        {
        case 1:
            f = inserirFila(f);
            limpaTela();
            break;
        case 2:
            f = removerFila(f);
            limpaTela();
            break;
        case 3:
            imprimirFila(f);
            limpaTela();
            break;
        case 4:
            liberarFila(f);
            printf("Saindo...\n");
            return 0;
            break;
        default:
            printf("Opcao invalida\n");
            break;
        }
    }
}