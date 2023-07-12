#include <stdlib.h>
#include <stdio.h>
#include "arvoreBinaria.h"

typedef struct Motocicleta
{
    int placa, ano, cilindrada;
    char modelo[40];
    char marca[40];
} moto;

typedef struct Carro
{
    int placa, ano, nPortas;
    char modelo[40];
    char marca[40];

} carro;

int menu()
{
    int op;
    printf("\n1 - Inserir\n");
    printf("2 - Verificar se existe\n");
    printf("3 - Retornar elemento\n");
    printf("4 - Calcular altura\n");
    printf("5 - Imprimir largura\n");
    printf("6 - Imprimir arvore inteira\n");
    printf("7 - Sair\n");
    printf("Digite a opcao desejada: ");
    scanf("%d", &op);
    return op;
}

void *veiculo(int *chave)
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
        scanf("%d", chave);
        c->placa = *chave;
        printf("Digite o ano: ");
        scanf("%d", &c->ano);
        printf("Digite a marca: ");
        scanf("%s", c->marca);
        printf("Digite o modelo: ");
        scanf("%s", c->modelo);
        printf("Digite o numero de portas: ");
        scanf("%d", &c->nPortas);

        info = (carro *)c;

        return info;
    };
    
    case 2:
    {
        moto *m = (moto *)malloc(sizeof(moto));
        printf("Digite a placa: ");
        scanf("%d", chave);
        m->placa = *chave;
        printf("Digite o ano: ");
        scanf("%d", &m->ano);
        printf("Digite a marca: ");
        scanf("%s", m->marca);
        printf("Digite o modelo: ");
        scanf("%s", m->modelo);
        printf("Digite a cilindrada do motor: ");
        scanf("%d", &m->cilindrada);

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
            int chavePai;
            char direcao;
            void *info;
            int chave;

            printf("Digite a chave do no Pai de onde deseja salvar: ");
            scanf("%d", &chavePai);
            printf("Digite a direcao: ");
            scanf(" %c", &direcao);

            info = veiculo(&chave);

            a = inserir(a, chave, chavePai, direcao, info);

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
        case 3:
        {
            int chave;
            printf("Digite a chave: ");
            scanf("%d", &chave);
            void *info = retornarElemento(a, chave, info);
            if (info != NULL)
            {
                carro *c = (carro *)info;
                printf("Placa: %d\n", c->placa);
                printf("Ano: %d\n", c->ano);
                printf("Modelo: %s\n", c->modelo);
                printf("Marca: %s\n", c->marca);
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
        case 5:
        {
            int alturaDesejada;
            printf("Digite a altura desejada: ");
            scanf("%d", &alturaDesejada);
            imprimirLargura(a, alturaDesejada);
            break;
        }
        case 6:
        {
            imprimirArvore(a);
            break;
        }
        case 7:
          {
            a = liberarArvore(a);
            exit(0);
            break;
          }
        default:
            break;
        }
    }

    return 0;
}