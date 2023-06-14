// Trabalho de Estrutura de Dados
// Hashing
// 13/06/2023
// Arthur Peixoto - github.com/ArthurPxto
// Emanuel Bravo - github.com/bravomanel

#include <stdio.h>
#include <stdlib.h>

char NomeArquivo[50] = "alunos.txt";
int TamanhoLista;

typedef struct Aluno {
   int mat;
   int disponibilidade;
   char nome[100];
   char curso[50];
} aluno;


int hash (int chave) {
   return chave % TamanhoLista;
}

void inicializar () {
   FILE *arquivo = fopen(NomeArquivo, "wb");
   aluno novo;
   novo.disponibilidade = 1;
   for (int i = 0; i < TamanhoLista; i++) {
      fwrite(&novo, sizeof(aluno), 1, arquivo);
   }
   fclose(arquivo);
}


int acharPosicao(int x) {
   int pos = hash(x);
   aluno temp;
   FILE *arquivo = fopen(NomeArquivo, "rb");
   fseek (arquivo, x*sizeof(aluno), SEEK_SET);
   fread(&temp, sizeof(aluno), 1, arquivo);
   while(temp.disponibilidade == 0) {
      pos = (pos + 1) % TamanhoLista;
      fseek (arquivo, x*sizeof(aluno), SEEK_SET);
      fread(&temp, sizeof(aluno), 1, arquivo);
   }
   fclose(arquivo);
   return pos;
}

void novoAluno() {
   aluno *novo = (aluno*)malloc(sizeof(aluno));
   printf("\nMatricula do aluno:");
   scanf("%d", &novo->mat);
   printf("\nNome do aluno:");
   scanf("%s", novo->nome);
   printf("\nCurso do aluno:");
   scanf("%s", novo->curso);

   int pos = acharPosicao(novo->mat);
   novo->disponibilidade = 0;

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

   while (temp.mat != matricula || temp.disponibilidade == 1) {
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

   // printf("\nDigite o tamanho máximo da tabela hash: ");
   // scanf("%d", &TamanhoLista);

   TamanhoLista = 11;
   printf("\nTamanho máximo da tabela hash: 11");

   inicializar();

   // char NomeArquivo[50] = "alunos.txt";

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
