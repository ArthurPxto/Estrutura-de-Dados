#include <stdlib.h>
#include <stdio.h>  
#include "fila.h"

int main()
{
    int opc, *vet;

    while(1)
    {
        opc = menu(opc);

        switch(opc)
        {
            case 1:
                vet = inserirFila(vet);
                break;
            case 2:
                vet = removerFila(vet);
                break;
            case 3:
                imprimirFila(vet);
                break;
            case 4:
                printf("Saindo...\n");
                return 0;
                break;
            default:
                printf("Opcao invalida\n");
                break;
        }
    }
}