#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Alunos: Arthur Peixoto e Emanuel Bravo

// Todas as combinaçoes de {a, b, c} de tamanho n, que o numero de a's é maior que a soma dos totais de b´s e de c´s   

void imprimirCombinacoes(char *vet, int pos, int n, char *aux){

    if(pos == n){

        /* printf("\n");
        printf("Combinaçao: ");
        for(int i = 0; i < n; i++){
            printf("%c ", vet[i]);
        }
        printf("\n");  */


        int contA = 0, contB = 0, contC = 0;

        for(int i = 0; i < n; i++){
            if(vet[i] == aux[0]){
                contA++;
            }
            if(vet[i] ==  aux[1]){
                contB++;
            }
            if(vet[i] ==  aux[2]){
                contC++;
            }
        }

        if(contA > (contB + contC)){
            printf("Combinacao valida!\n");

            for(int i = 0; i < n; i++){
            printf("%c ", vet[i]);
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

    int n;
    char  aux[3] = {'a', 'b', 'c'}; 

    printf("Digite o tamanho das combinacoes: ");
    scanf("%d", &n);


    char *vetor = (char*) malloc(n * sizeof(char));
        if(vetor == NULL){
            printf("Malloc Error! - vetor principal");
            exit(1);
        }

    imprimirCombinacoes(vetor, 0 , n, aux);


    return 0;
}