// Trabalho de Estrutura de Dados
// Estruturas Genéricas
// 20/06/2023
// Arthur Peixoto - github.com/ArthurPxto
// Emanuel Bravo - github.com/bravomanel

#include <stdio.h>
#include <stdlib.h>

typedef struct docente
{
    int matricula;
    char nome[100];
    int salario;

} professor;

typedef struct discente
{
    int matricula;
    char nome[100];
    int anoIngresso;
    char curso[50];

} aluno;

typedef struct humano
{
    int tipo; // 1 = professor, 2 = aluno
    void *profissao; // ponteiro para professor ou aluno

} pessoa;

typedef struct lista
{
    struct humano *pessoa;
    struct lista *prox;

} Lista;

void buscarPessoa(Lista *l){
    
    Lista *aux = l;
    int matricula;
    printf("Informe a matricula da pessoa que deseja buscar: ");
    scanf("%d", &matricula);

    while(aux != NULL){

        if(aux->pessoa->tipo == 1){
            professor *p = (professor *)aux->pessoa->profissao;
            if(p->matricula == matricula){
                printf("Nome: %s\n", p->nome);
                printf("Matricula: %d\n", p->matricula);
                printf("Salario: %d\n", p->salario);
                return;
            }
        }else{
            aluno *a = (aluno *)aux->pessoa->profissao;
            if(a->matricula == matricula){
                printf("Nome: %s\n", a->nome);
                printf("Matricula: %d\n", a->matricula);
                printf("Ano de ingresso: %d\n", a->anoIngresso);
                printf("Curso: %s\n", a->curso);
                return;
            }
        }

        aux = aux->prox;
    }

    printf("Pessoa nao encontrada\n");
}

Lista *removerLista(Lista *l){
    Lista *aux = l;
    Lista *ant = NULL;

    if(aux == NULL){
        printf("Lista vazia\n");
        return l;
    }

    int matricula;
    printf("Informe a matricula da pessoa que deseja remover: ");
    scanf("%d", &matricula);

    while(aux != NULL){

        if(aux->pessoa->tipo == 1){
            professor *p = (professor *)aux->pessoa->profissao;
            if(p->matricula == matricula){
                break;
            }
        }else{
            aluno *a = (aluno *)aux->pessoa->profissao;
            if(a->matricula == matricula){
                break;
        }

        ant = aux;
        aux = aux->prox;
    }
    }

    if(aux == NULL){
        printf("Pessoa nao encontrada\n");
        return l;
    }

    if(ant == NULL){
        l = aux->prox;
    }else{
        ant->prox = aux->prox;
    }

    free(aux);
    return l;

}

pessoa *criarPessoa()
{
    int tipo;

    printf("1 - Professor\n");
    printf("2 - Aluno\n");
    printf("Informe o tipo de pessoa: ");
    scanf("%d", &tipo);

    pessoa *p = (pessoa *)malloc(sizeof(pessoa));
    p->tipo = tipo;
    

    if(tipo == 1)
    {
        p->profissao = (professor *)malloc(sizeof(professor));

        professor *x = (professor *)malloc(sizeof(professor));
        
        printf("Informe o nome do professor: ");
        scanf("%s", x->nome);
        printf("Informe a matricula do professor: ");
        scanf("%d", &x->matricula);
        printf("Informe o salario do professor: ");
        scanf("%d", &x->salario);

        p->profissao = x;

    }
    else if(tipo == 2)
    {
        p->profissao = (aluno *)malloc(sizeof(aluno));

        aluno *x = (aluno *)malloc(sizeof(aluno));

        printf("Informe o nome do aluno: ");
        scanf("%s", x->nome);
        printf("Informe a matricula do aluno: ");
        scanf("%d", &x->matricula);
        printf("Informe o ano de ingresso do aluno: ");
        scanf("%d", &x->anoIngresso);
        printf("Informe o curso do aluno: ");
        scanf("%s", x->curso);

        p->profissao = x;
    }

    return p;
}

Lista *inserirNoFinal(Lista *l)
{
    Lista *novo = (Lista *)malloc(sizeof(Lista));
    novo->pessoa = criarPessoa();
    novo->prox = NULL;

    if(l == NULL)
    {
        l = novo;
    }
    else
    {
        Lista *aux = l;
        while(aux->prox != NULL)
        {
            aux = aux->prox;
        }
        aux->prox = novo;
    }

    return l;
}

Lista *criarLista()
{
    Lista *l = (Lista *)malloc(sizeof(Lista));
    l->pessoa = NULL;
    l->prox = NULL;

    return l;
}

int menu(int opc)
{
    printf("1 - Inserir uma pessoa\n");
    printf("2 - Remover uma pessoa pela matricula\n");
    printf("3 - Buscar uma pessoa pela matricula\n");
    printf("4 - Contar um numero de alunos de determinado curso\n");
    printf("5 - Imprimir os professores com os maiores salarios\n");
    printf("6 - Sair\n");
    printf("Opcao: ");
    scanf("%d", &opc);

    return opc;
}

int main(){
    int opc;

    Lista *l = criarLista();

    while(1){
        opc = menu(opc);

        switch(opc){
            case 1:

                l = inserirNoFinal(l);

                break;
            case 2:

                l = removerLista(l);

                break;
            case 3:
                
                buscarPessoa(l);

                break;
            case 4: 

                //contarNumeroAlunos(l);

                break;
            case 5:

                //imprimirProfessores(l);

                break;
            case 6:
                printf("Saindo...\n");
                return 0;
                break;
            default:
                printf("Opcao invalida\n");
                break;
        }
    }
}