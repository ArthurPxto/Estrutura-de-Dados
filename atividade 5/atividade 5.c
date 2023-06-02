#include <stdio.h>
#include <stdlib.h>

typedef struct lista{

    int vertice;
    int custo;
    struct lista *prox;

}lista;

int existe(int *visitados, int vertice, int pos)
{
    int i;

    for(i = 0; i < pos; i++)
    {
        if(visitados[i] == vertice)
        {
            return 1;
        }
    }

    return 0;
}

void Caminhos(lista **grafo, int pos, int *visitados, int destino, int **vetor, int n)
{
    if(visitados[pos-1]== destino)
    {
      printf("\n Caminho: ");
      for(int i = 0; i < pos; i++)
      {
            printf("%d ", visitados[i]);
      }        
    }
    else
    {
        lista *aux = grafo[visitados[pos-1]];

        while(aux != NULL)
        {

            if(!existe(visitados, aux->vertice, pos))
            {
                visitados[pos] = aux->vertice;
                Caminhos(grafo, pos + 1, visitados, destino, vetor, n);
            }

            aux = aux->prox;
        }
    }
}

int custoAresta (lista **grafo, int a, int b) {
   lista *aux = grafo[a];
   while (aux != NULL) {
      if (aux->vertice == b) {
         return aux->custo;
      }
      aux = aux->prox;
   }
   return -1;
}

int calcularCusto (lista **grafo, int *vet, int n) {
   int i, custo = 0;
   for (i = 1; i < n-1; i++) {
      custo += custoAresta(grafo, vet[i-1], vet[i]);
   }
   return custo;
}	

void CaminhoMenorCusto (lista **grafo, int *visitados, int pos, int destino, int *menorCusto, int *vetAux, int *tam) {
   if (visitados[pos-1] == destino) {
      int custo = calcularCusto(grafo, visitados, pos);
      if (custo < *menorCusto) {
         int i;
         *menorCusto = custo;
         *tam = pos;
         for (i = 0; i < pos; i++) {
            vetAux[i] = visitados[i];
         }
      }
   } else {
      lista *aux = grafo[visitados[pos-1]];
      while (aux != NULL) {
         if (!existe(visitados, aux->vertice, pos)) {
            visitados[pos] = aux->vertice;
            CaminhoMenorCusto(grafo, visitados, pos+1, destino, menorCusto, vetAux, tam);
         }
         aux = aux->prox;
      }
   }
}


void ComparaVetores(lista **grafo, int pos, int *visitados, int destino, int n)
{
    int opc;

    printf("1 - Imprimir todos caminhos\n");
    printf("2 - Imprimir o caminho mais curto\n");
    printf("3 - Imprimir o caminho de menor custo\n");
    printf("Digite a opcao desejada: ");
    scanf("%d", &opc);

    int **vetor = (int**)malloc((n)*sizeof(int*));

    switch (opc)
    {
    case 1:
    {
        Caminhos(grafo, pos, visitados, destino, vetor, n);
        
        break;
    }
    case 2:
    {
        int *menorCusto, *tam;
        int vetAux[n];
        CaminhoMenorCusto (grafo, visitados, pos, destino, menorCusto, vetAux, tam);  
    
        break;
    }
    case 3:
    {
        int aux = 0;
      //   imprimirCaminhoMenorCusto(grafo, pos, visitados, destino, vetor, n);
      

        break;
    }
    default:
        break;
    }
}



void VerificarCompleto(lista **g, int n)
{
    int i, cont = 0;

    for(i = 1; i <= n; i++)
    {
        lista *aux = g[i];

        while(aux != NULL)
        {
            cont++;
            aux = aux->prox;
        }
    }

    if(cont == n*(n - 1))
    {
        printf("O grafo e completo!\n");
    }
    else
    {
        printf("O grafo nao e completo!\n");
    }
}

void ImprimirGraus(lista **grafo, int n, int origem)
{
    int grauEntrada = 0, grauSaida = 0;

    lista *aux = grafo[origem];

    while(aux != NULL)
    {
        grauSaida++;
        aux = aux->prox;
    }

    for(int i = 1; i <= n; i++)
    {
        aux = grafo[i];

        while(aux != NULL)
        {
            if(aux->vertice == origem)
            {
                grauEntrada++;
            }

            aux = aux->prox;
        }
    }

    printf("Grau de entrada: %d\n", grauEntrada);
    printf("Grau de saida: %d\n", grauSaida);
}

lista *RemoverLista(lista *grafo, int destino)
{
    if(grafo == NULL)
    {
        return NULL;
    }
    else if(grafo->vertice == destino)
    {
        lista *aux = grafo;
        grafo = grafo->prox;
        free(aux);
    }
    else
    {
        grafo->prox = RemoverLista(grafo->prox, destino);
    }

    return grafo;
}

void RemoverAresta(lista **grafo, int origem, int destino)
{
    grafo[origem] = RemoverLista(grafo[origem], destino);
}

void ImprimirGrafo(lista **grafo, int n)
{
    int i;

    for(i = 1; i <= n; i++)
    {
        lista *aux = grafo[i];

        printf("Vertice %d: ", i);

        while(aux != NULL)
        {
            printf("%d ", aux->vertice);
            aux = aux->prox;
        }

        printf("\n");
    }
}

lista *InserirLista(lista *grafo, int destino, int custo)
{
    lista *novo = (lista*)malloc(sizeof(lista));
    novo->vertice = destino;
    novo->custo = custo;
    novo->prox = grafo;

    return novo;
}

void InserirAresta(lista **grafo, int origem, int destino, int custo)
{
    grafo[origem] = InserirLista(grafo[origem], destino, custo);
}

void Inicializa(lista **grafo, int n)
{
    int i;

    for(i = 0; i <= n; i++)
    {
        grafo[i] = NULL;
    }
}

int Menu()
{
    int opc;

    printf("\n\n1 - Inserir aresta\n");
    printf("2 - Remover aresta\n");
    printf("3 - Imprimir grafo\n");
    printf("4 - Imprimir graus de entrada e saida de um vertice\n");
    printf("5 - Verificar se um grafo e completo\n");
    printf("6 - Imprimir caminhos\n");

    printf("9 - Sair\n");
    printf("Digite a opcao desejada: ");
    scanf("%d", &opc);

    return opc;
}

int main()
{
    int n;

    printf("Deseja ter um grafo de quantos vertices? ");
   //  scanf("%d", &n);

   n=4;
    
    // a posição 0 nao e usada para facilitar a manipulação
    lista **grafo = (lista**)malloc((n + 1)*sizeof(lista*));

    Inicializa(grafo, n);

    InserirAresta(grafo, 1, 2, 1);
    InserirAresta(grafo, 1, 3, 2);
    InserirAresta(grafo, 1, 4, 3);
    InserirAresta(grafo, 2, 1, 1);
    InserirAresta(grafo, 2, 3, 1);
    InserirAresta(grafo, 2, 4, 2);
    InserirAresta(grafo, 3, 1, 2);
    InserirAresta(grafo, 3, 2, 1);
    InserirAresta(grafo, 3, 4, 1);
    InserirAresta(grafo, 4, 3, 1);
    InserirAresta(grafo, 4, 2, 2);
    InserirAresta(grafo, 4, 1, 3);

    while (1)
    {    
        switch (Menu())
        {
        case 1 : 
        {
            // system("cls");

            int origem = 0, destino = 0, custo = 0;

            printf("Digite a origem: ");
            scanf("%d", &origem);

            printf("Digite o destino: ");
            scanf("%d", &destino);

            printf("Digite o custo: ");
            scanf("%d", &custo);

            InserirAresta(grafo, origem, destino, custo);

            break;
        }
        case 2:
        {   
            // system("cls");

            int origem = 0, destino = 0;

            printf("Digite a origem: ");
            scanf("%d", &origem);

            printf("Digite o destino: ");
            scanf("%d", &destino);
            
            RemoverAresta(grafo, origem, destino);

            break;
        }
        case 3:
        {
            // system("cls");

            ImprimirGrafo(grafo, n);

            printf("\n Digite qualquer tecla para continuar: ");
            getchar();

            break;
        }
        case 4:
        {
            // system("cls");

            int origem = 0;

            printf("Digite o vertice: ");
            scanf("%d", &origem);

            ImprimirGraus(grafo, n, origem);   

            printf("\n Digite qualquer tecla para continuar: ");
            getchar();
            break;
        }
        case 5:
        {
            // system("cls");

            VerificarCompleto(grafo, n);
            
            printf("\n Digite qualquer tecla para continuar: ");
            getchar();
            
            break;
        }
        case 6:
        {
            // system("cls");

            int origem = 0, destino = 0;

            printf("Digite a origem: ");
            scanf("%d", &origem);
            printf("Digite o destino: ");
            scanf("%d", &destino);

            int *visitados = (int*)malloc((n)*sizeof(int));
            visitados[0] = origem;

            ComparaVetores(grafo, 1, visitados, destino, n);

            printf("\n Digite qualquer tecla para continuar: ");
            getchar();
            break;
        }
        case 9:
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
