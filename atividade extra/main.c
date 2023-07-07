#include <stdlib.h>
#include <stdio.h>
#include "arvoreBinaria.h"

typedef struct Motocicleta
{
    int placa, ano;
    char modelo[20];
    char marca[20];
} moto;

typedef struct Carro
{
    int placa, ano;
    char modelo[20];
    char marca[20];

} carro;

int menu()
{
    int op;
    printf("1 - Inserir\n");
    printf("2 - Verificar se existe\n");
    printf("3 - Retornar elemento\n");
    printf("4 - Calcular altura\n");
    printf("5 - Imprimir largura\n");
    printf("6 - Sair\n");
    printf("Digite a opcao desejada: ");
    scanf("%d", &op);
    return op;
}

void *veiculo()
{
    int op;
    void *info;
    printf("1 - Carro\n");
    printf("2 - Moto\n");
    printf("Digite a opcao desejada: ");
    scanf("%d", &op);
    switch (op)
    {
    case 1:
    {
        carro *c = (carro *)malloc(sizeof(carro));

        printf("Digite a placa: ");
        scanf("%d", &c->placa);
        printf("Digite o ano: ");
        scanf("%d", &c->ano);
        printf("Digite o modelo: ");
        scanf("%s", c->modelo);
        printf("Digite a marca: ");
        scanf("%s", c->marca);

        info = (carro *)c;

        return info;
    };
    
    case 2:
    {
        moto *m = (moto *)malloc(sizeof(moto));
        printf("Digite a placa: ");
        scanf("%d", &m->placa);
        printf("Digite o ano: ");
        scanf("%d", &m->ano);
        printf("Digite o modelo: ");
        scanf("%s", m->modelo);
        printf("Digite a marca: ");
        scanf("%s", m->marca);

        info = (moto *)m;

        return info;
    };

    default:
        break;
    }
}

int main()
{

    Arvore a = inicializarArvore();
    while (1)
    {
        switch (menu())
        {
        case 1:
        {
            int chave;
            char direcao;
            void *info;
            printf("Digite a chave: ");
            scanf("%d", &chave);
            printf("Digite a direcao: ");
            scanf(" %c", &direcao);

            info = veiculo();

            a = inserir(a, chave, direcao, info);

            break;
        }
        case 2:
        {
            int chave;
            printf("Digite a chave: ");
            scanf("%d", &chave);
            if (verificarSeExiste(a, chave))
            {
                printf("Existe\n");
            }
            else
            {
                printf("Nao existe\n");
            }
            break;
        }
        case 4:
        {
            printf("Altura: %d\n", calcularAltura(a));
            break;
        }
        default:
            break;
        }
    }

    return 0;
}