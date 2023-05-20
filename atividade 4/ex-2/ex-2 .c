#include <stdio.h>
#include <stdlib.h>

// Alunos: Arthur Peixoto e Emanuel Bravo

// Todas as combinaçoes de {15, 31 ,55 , 44} de tamanho n, cujo a soma dos elementos é par

void imprimirCombinacoes(int *vet, int pos, int n, int *aux){

    if(pos == n){

        /*  printf("\n");
        printf("Combinaçao: ");
        for(int i = 0; i < n; i++){
            printf("%d ", vet[i]);
        }
        printf("\n"); */

        int somador = 0;

        for(int i = 0; i < n; i++){
            somador += vet[i];
        }
        if(somador % 2 == 0){
            printf("Combinacao valida!\n");

            for(int i = 0; i < n; i++){
            printf("%d ", vet[i]);
            }
            
            printf("\n");
        }

    }
    else{
        for(int i = 0; i < 4; i++){
            vet[pos] = aux[i];
            imprimirCombinacoes(vet, pos + 1, n, aux);
        }
    }
    



}

int main(){

    int n;;

    printf("Digite o tamanho das combinacoes: ");
    scanf("%d", &n);

    int *vet = (int*)malloc(n * sizeof(int));
        if(vet == NULL){
            printf("Malloc Error! - vetor principal\n");
            exit(1);
        }
    int *aux = (int*)malloc(4 * sizeof(int));
        if(aux == NULL){
            printf("Malloc Error! - vetor auxiliar\n");
            exit(1);
        }
    
    aux[0] = 15;
    aux[1] = 31;
    aux[2] = 55;
    aux[3] = 44;
    

    imprimirCombinacoes(vet, 0, n, aux);

    return 0;
}