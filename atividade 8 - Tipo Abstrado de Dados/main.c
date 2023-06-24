// Trabalho de Estrutura de Dados
// Tipo Abstrato de Dados
// 20/06/2023
// Arthur Peixoto - github.com/ArthurPxto
// Emanuel Bravo - github.com/bravomanel

#include <stdlib.h>
#include <stdio.h>  
#include "fila.h"


int main()
{
    int opc;

    Fila f = criarFila();

    while(1)
    {
        opc = menu(opc);

        switch(opc)
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