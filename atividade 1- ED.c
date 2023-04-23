#include <stdio.h>
#include <stdlib.h>

// alunos: Arthur Peixoto / Emanuel Bravo;

 typedef struct arvore{
    int info;
    struct arvore *esq;
    struct arvore *dir;
} arvore;

arvore *LerArvore(FILE *arq) {
   char c;
   int num;
   arvore *a;
   

   fscanf(arq,"%c",&c);
   fscanf(arq,"%d",&num);
   
   if (num==-1) {
      fscanf(arq,"%c",&c);
      return NULL;
   }
   else {
      a = (arvore*) malloc(sizeof(arvore));

      a->info = num;
      a->esq = LerArvore(arq);
      a->dir = LerArvore(arq);

      fscanf(arq,"%c",&c);
      return a;
   }
}


void ImprimirPreOrdem(arvore *a) {
   if (a != NULL) {
      printf("%d ", a->info);
      ImprimirPreOrdem(a->esq);
      ImprimirPreOrdem(a->dir);
   }
}

void ImprimirOrdem(arvore *a) {
   if (a != NULL) {      
      ImprimirPreOrdem(a->esq);
      printf("%d ", a->info);
      ImprimirPreOrdem(a->dir);
   }
}

void ImprimirPosOrdem(arvore *a) {

   if (a != NULL) {      
      ImprimirPreOrdem(a->esq);
      ImprimirPreOrdem(a->dir);
      printf("%d ", a->info);
   }
}

int menu() {


    int opc;

    printf("\n------- Menu ------- \n");
        printf("1) Ler uma Arvore \n");
        printf("2) Imprimir a Arvore \n");
        printf("3) Buscar um elemento na arvore \n");
        printf("4) Contar o numero de elementos na arvore \n");
        printf("5) Imprimir as folhas das arvore \n");
        printf("6) sair \n");
        printf("-------------------- \n");
        
        printf("\n Digite a opcao desejada: ");
        scanf("%d", &opc);

        return opc;
}

int Busca(arvore *a, int x) {
   if (a==NULL)
      return 0;
   else {
      if (a->info == x)
         return 1;
      else 
         if (Busca(a->esq, x) == 1)
            return 1;
         else
            return Busca(a->dir, x);
   }
}  

void ContarElementos(arvore *a, int n) {

    if(a != NULL)
    {
        ContarElementos(a->esq, n);
        n++;
        ContarElementos(a->dir, n);
    } 
}

void ImprimirNosFolhas(arvore *a) {
    // verifica se o nó atual é nulo
   if(a != NULL){
    // verifica se a->esq e a-> direita e nulo
    // se forem nulos ele printa
        if(a->esq == NULL && a->dir == NULL){
        printf("\n [%d]", a->info);
        }
        else{
        ImprimirNosFolhas(a->esq);
        ImprimirNosFolhas(a->dir);
        }
   }
   
}

int main ()
{
    int opc, ordem, info, n = 0;

    arvore *a = NULL;

    FILE *arq;

    while(1){

        switch (opc = menu()){
            
        case 1:
            
            arq = fopen("entrada.txt", "r");

            if(arq == NULL)
            {
                printf("\n 0 \n");

            }

            a = LerArvore(arq);

            fclose(arq);

            printf(" \narquivo lido com sucesso \n");
            
            break;
        case 2:
               printf("1) pre-ordem \n"); 
               printf("2) ordem \n"); 
               printf("3) pos-ordem \n"); 
               printf("selecione a ordem da arvore: "); 
               scanf("%d", &ordem);
               
               switch (ordem)
               {
               case 1:

                ImprimirPreOrdem(a);


                break;
               case 2:

                ImprimirOrdem(a);

               
                break;
               case 3:
                
                ImprimirPosOrdem(a);


                break;
               
               default:
                    printf("opcao invalida! \n");
                    getchar();
                break;
               }


            break;
        case 3:

            system("cls");

            printf(" \n Qual elemento deseja buscar? ");
            scanf("%d", &info);

            if(Busca(a , info) == 1)
            {
                printf("\n elemento encontrado \n");
            }
            else{
                printf("\n o elemento nao esta na arvore \n ");
            }

            break;
        case 4:
            
            ContarElementos(a, n);
            
            printf("Existem %d elementos nessa arvore", n);

            break;
        case 5:
            system("cls");

            ImprimirNosFolhas(a);
           break;
        case 6:

            return 0;
            
            break;
        
        default:
            printf("Opcao nao encontrada, tente novamente!\n ");
            break;
        }
    }

}