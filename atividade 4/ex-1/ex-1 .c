#include <stdio.h>
#include <stdlib.h>

// Alunos: Arthur Peixoto e Emanuel Bravo

// Todas as combinaçoes de {a, b, c} de tamanho n, que o numero de a's é maior que a soma dos totais de b´s e de c´s   

void imprimirCombinacoes(int *vet, int pos, int n, int *aux){

    if(pos == n){

       /*  printf("\n");
        printf("Combinaçao: ");
        for(int i = 0; i < n; i++){
            printf("%d ", vet[i]);
        }
        printf("\n"); */


        int contA = 0, contB = 0, contC = 0;

        for(int i = 0; i < n; i++){
            if(vet[i] == aux[0]){
                contA++;
            }
            if(vet[i] == aux[1]){
                contB++;
            }
            if(vet[i] == aux[2]){
                contC++;
            }
        }

        if(contA > (contB + contC)){
            printf("Combinacao valida!\n");

            for(int i = 0; i < n; i++){
            printf("%d ", vet[i]);
            }
            
            printf("\n");
        }
    }
    else{
        for(int i = 0; i < 3; i++){
            vet[pos] = aux[i];
            imprimirCombinacoes(vet, pos + 1, n, aux);
        }
    }
}


int main(){

    int n, a, b, c, aux[3];

    printf("Digite o tamanho das combinacoes: ");
    scanf("%d", &n);

    printf("Digite o primeiro numero: ");
    scanf("%d", &a);

    printf("Digite o segundo numero: ");
    scanf("%d", &b);

    printf("Digite o terceiro numero: ");
    scanf("%d", &c);

    aux[0] = a;
    aux[1] = b;
    aux[2] = c;

    int *vetor = (int*) malloc(n * sizeof(int));
        if(vetor == NULL){
            printf("Malloc Error! - vetor principal");
            exit(1);
        }

    imprimirCombinacoes(vetor, 0 , n, aux);


    return 0;
}