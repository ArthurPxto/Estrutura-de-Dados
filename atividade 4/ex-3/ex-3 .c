#include <stdlib.h>
#include <stdio.h>

// Alunos: Arthur Peixoto e Emanuel Bravo

// Dado un valor em centavos, imprimir todas as maneiras de representa-lo utilidando moedas de 1, 5, 10, 25 e 50 centavos 

void imprimirCombinacoes(int *vet, int n){

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

    printf("%d moeda(s) de 1 / %d moeda(s) de 5 / %d moeda(s) de 10 / %d moeda(s) de 25 / %d moeda(s) de 50 ", vetMoedas[0], vetMoedas[1], vetMoedas[2], vetMoedas[3], vetMoedas[4]);

    printf("\n ------------------ \n");

}

void Combinacoes(int *vet, int pos, int n, int *aux, int valor){

    if(pos == n){

        int somador = 0 , i;

        for(i = 0; i  < n; i++){

            somador += vet[i];
        }

        if(somador == valor){

            /*  printf("\n ------------------ \n");
            printf("Combinacao: \n");
            for(i = 0; i < n; i++){
                printf("%d ", vet[i]);
            }
            printf("\n ------------------ \n"); 

             printf("Combinacao em moedas: ");


             printf("\n ------------------ \n");  */

            imprimirCombinacoes(vet, n);
        }


    
    }
    else{
        for(int i = 0; i < 6; i++){
            vet[pos] = aux[i];
            Combinacoes(vet, pos + 1, n, aux, valor);
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
    
    Combinacoes(vet, 0, valor, aux, valor);
    


    return 0;
}