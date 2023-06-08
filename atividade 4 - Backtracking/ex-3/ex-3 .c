#include <stdlib.h>
#include <stdio.h>
#include <math.h>

// Alunos: Arthur Peixoto e Emanuel Bravo

// Dado un valor em centavos, imprimir todas as maneiras de representa-lo utilidando moedas de 1, 5, 10, 25 e 50 centavos 
int cont = 0;

void imprimirCombinacoes(int *vet, int n, int **ptr){

    int vetMoedas[5] = {0 , 0, 0, 0, 0};

    for(int i = 0; i < n; i++){
        if(vet[i] == 1){
            vetMoedas[0]++;
        }
        else if(vet[i] == 5){
            vetMoedas[1]++;
        }
        else if(vet[i] == 10){
            vetMoedas[2]++;
        }
        else if(vet[i] == 25){
            vetMoedas[3]++;
        }
        else if(vet[i] == 50){
            vetMoedas[4]++;
        }
    }

    ptr[cont] = vetMoedas;

/*     printf("\n  depois imprimindo aux-> cont %d\n", cont); 

    printf("\n ---------imprimindo ptr--------- \n");
    if(cont == 0){
        for(int i = 0; i < 5; i++){
            printf("%d ", *(ptr[cont] + i));
        }
        printf("\n");
    }
    else{
    for(int i = 0; i < cont; i++){
        for(int j = 0; j < 5; j++){
            printf("%d ", *(ptr[i] + j));
        }
        printf("\n");
    }
    printf("\n ------------------ \n");
    getchar(); 
    } */
    if(cont <= 1){
        for(int i = 0; i < 5; i++){
            *(ptr[cont] + i) = vetMoedas[i];
        }
        printf("\n %d moeda(s) de 1 / %d moeda(s) de 5 / %d moeda(s) de 10 / %d moeda(s) de 25 / %d moeda(s) de 50 \n ", vetMoedas[0], vetMoedas[1], vetMoedas[2], vetMoedas[3], vetMoedas[4]);
        cont++;
    }
    else{

        int flag = 0;
        for(int i = 0; i < cont; i++){
            for(int j = 0; j < 5; j++){
                if(*(ptr[i] + j) == vetMoedas[j]){
                    flag++;
                }
            }
        }
        if(flag < 5){
            for(int i = 0; i < 5; i++){
            *(ptr[cont] + i) = vetMoedas[i];
        }
            printf("\n %d moeda(s) de 1 / %d moeda(s) de 5 / %d moeda(s) de 10 / %d moeda(s) de 25 / %d moeda(s) de 50 \n ", vetMoedas[0], vetMoedas[1], vetMoedas[2], vetMoedas[3], vetMoedas[4]);
            cont++;
        }

    }

    /* printf("\n ------------------ \n"); */



}

void Combinacoes(int *vet, int pos, int n, int *aux, int valor, int **ptr){

    if(pos == n){

        int somador = 0 , i;

        for(i = 0; i  < n; i++){

            somador += vet[i];
        }

        if(somador == valor){

           /*  printf("imprimindo vet: \n");

            for(i = 0; i < n; i++){
                printf("%d ", vet[i]);
            }
            printf("\n"); */

            imprimirCombinacoes(vet, n, ptr);

        }


    
    }
    else{
        for(int i = 0; i < 6; i++){
            vet[pos] = aux[i];
            Combinacoes(vet, pos + 1, n, aux, valor, ptr);
        }
    }
}

int main(){

    int valor, aux[6] = {1, 5, 10, 25, 50, 0};

    printf("Digite o valor em centavos: ");
    scanf("%d", &valor);

    int *vet = (int*)malloc(valor * sizeof(int));
        if(vet == NULL){
            printf("Malloc Error! - vetor principal\n");
            exit(1);
        }
    
    int *ptr = (int*)malloc(valor * sizeof(ptr));
        if(ptr == NULL){
            printf("Malloc Error! - vetor ponteiros\n");
            exit(1);
        }


    Combinacoes(vet, 0, valor, aux, valor, ptr);
    


    return 0;
}