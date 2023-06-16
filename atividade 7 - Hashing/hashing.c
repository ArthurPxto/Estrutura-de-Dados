// Trabalho de Estrutura de Dados
// Hashing
// 13/06/2023
// Arthur Peixoto - github.com/ArthurPxto
// Emanuel Bravo - github.com/bravomanel

#include <stdio.h>
#include <stdlib.h>

char NomeArquivo[50] = "alunos.txt";
int TamanhoLista = 11;

typedef struct Aluno {
   int mat;
   int disponibilidade;
   char nome[100];
   char curso[50];
} aluno;


int hash (int chave) {
   int hash = chave % TamanhoLista;
   return hash;
}

void inicializar () {
   FILE *arquivo = fopen(NomeArquivo, "wb");
   aluno novo;
   novo.disponibilidade = 1;
   novo.mat = -1;
   for (int i = 0; i < TamanhoLista; i++) {
      fwrite(&novo, sizeof(aluno), 1, arquivo);
   }
   fclose(arquivo);
}


int acharPosicao(int mat) {
   int pos = hash(mat);
   aluno temp;
   FILE *arquivo = fopen(NomeArquivo, "rb");
   fseek (arquivo, pos*sizeof(aluno), SEEK_SET);
   fread(&temp, sizeof(aluno), 1, arquivo);
   while(temp.disponibilidade == 0) {
      pos = (pos + 1) % TamanhoLista;
      fseek (arquivo, pos*sizeof(aluno), SEEK_SET);
      fread(&temp, sizeof(aluno), 1, arquivo);
   }
   fclose(arquivo);
   return pos;
}

void novoAluno() {
   aluno novo;
   printf("\nMatricula do aluno:");
   scanf("%d", &novo.mat);
   printf("Nome do aluno:");
   scanf("%s", novo.nome);
   printf("Curso do aluno:");
   scanf("%s", novo.curso);

   int pos = acharPosicao(novo.mat);
   novo.disponibilidade = 0;

   FILE *arquivo = fopen(NomeArquivo, "r+b");
   fseek(arquivo, pos*sizeof(aluno), SEEK_SET);
   fwrite(&novo, sizeof(aluno), 1, arquivo);
   fclose(arquivo);
}

void acharAluno(int matricula) {
   int pos = hash(matricula);
   aluno temp;
   FILE *arquivo = fopen(NomeArquivo, "rb");
   fseek(arquivo, pos*sizeof(aluno), SEEK_SET);
   fread(&temp, sizeof(aluno), 1, arquivo);

   for (int i = 0; i < TamanhoLista; i++) {
      if (temp.mat == matricula) {
         break;
      }
      pos = (pos + 1) % TamanhoLista;
      fseek(arquivo, pos*sizeof(aluno), SEEK_SET);
      fread(&temp, sizeof(aluno), 1, arquivo);
   }

   if (temp.disponibilidade == 1) {
      printf("\nAluno não encontrado.");
   } else {
      printf("\nMatricula: %d", temp.mat);
      printf("\nAluno: %s", temp.nome);
      printf("\nCurso: %s", temp.curso);
   }

}

void imprimirTabela() {
   FILE *arquivo = fopen(NomeArquivo, "rb");
   aluno temp;
   printf("\n");
   for (int i = 0; i < TamanhoLista; i++) {
         printf("%d  ", i);
   }
   printf("\n");
   for (int i = 0; i < TamanhoLista; i++) {
      fseek(arquivo, i*sizeof(aluno), SEEK_SET);
      fread(&temp, sizeof(aluno), 1, arquivo);
      printf("%d ", temp.mat);
   }
   fclose(arquivo);
}

int Menu()
{
    int opc;

    printf("\n\n");
    printf("1 - Inserir novo aluno\n");
    printf("2 - Imprimir informações do aluno\n");
    printf("3 - Imprimir tabela de dispersão\n");

    printf("4 - Sair\n");
    printf("Digite a opcao desejada: ");
    scanf("%d", &opc);

    return opc;
}

int main()
{
   inicializar();

    while (1)
    {    
        switch (Menu())
        {
        case 1 : 
        {

            novoAluno();

            break;
        }
        case 2:
        {   
            int mat;
            printf("\nMatricula do aluno:");
            scanf("%d", &mat);
            acharAluno(mat);

            break;
        }
        case 3:
        {
            imprimirTabela();
            break;
        }
        case 4:
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
