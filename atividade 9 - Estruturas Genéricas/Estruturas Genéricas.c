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

} humano;

typedef struct lista
{
    struct humano *pessoa;
    struct lista *prox;

} Lista;

void imprimirLista(Lista *l){
    Lista *aux = l;

    if(aux == NULL){
        printf("Lista vazia\n");
        return;
    }

    humano *x = aux->pessoa;
    professor *p;
    aluno *a;

    while(aux != NULL){
        printf("--------------------\n");
        printf("Tipo: %d\n", x->tipo);
        if(x->tipo == 1){
            p = (professor *) x->profissao;
            printf("Nome: %s\n", p->nome);
            printf("Matricula: %d\n", p->matricula);
            printf("Salario: %d\n", p->salario);
        }else{
            a = (aluno *) x->profissao;
            printf("Nome: %s\n", a->nome);
            printf("Matricula: %d\n", a->matricula);
            printf("Ano de Ingresso: %d\n", a->anoIngresso);
            printf("Curso: %s\n", a->curso);
        }

        aux = aux->prox;
    }
}

void verificaProfissao(humano *x)
{
    printf("Entrou na verifica\n");
    
    professor *p;

    if (x->tipo == 1)
    {
        p = (professor *) x->profissao;
        printf("Professor\n");
        printf("Nome: %s\n", p->nome);
        printf("Matricula: %d\n", p->matricula);
        printf("Salario: %d\n", p->salario);
    }
    else
    {
        printf("Aluno\n");
        aluno *a = (aluno *) x->profissao;
        printf("Nome: %s\n", a->nome);
        printf("Matricula: %d\n", a->matricula);
        printf("Ano de Ingresso: %d\n", a->anoIngresso);
        printf("Curso: %s\n", a->curso);
    }
}

void buscarPessoa(Lista *l){
    
    
    Lista *aux = l;
    int matricula, printou = 0;

    printf("Informe a matricula da pessoa que deseja buscar: ");
    scanf("%d", &matricula);

    int n = 0;

    while(aux != NULL){

        printf("Entrou %d vez\n", n);
        n++;

        humano *x = aux->pessoa;
        professor *p;
        aluno *a;

        if(x->tipo == 1){
            printf("Professor- entrou\n");
            p = x->profissao;
            if(p->matricula == matricula){
                printou = 1;
                verificaProfissao(x);
                break;
            }
        }else{
            printf("Aluno- entrou\n");
            a = x->profissao;
            if(a->matricula == matricula){
                printou = 1;
                verificaProfissao(x);
                break;
            }
        }

        aux = aux->prox;
    }

    if(printou == 0)
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

    humano *x = aux->pessoa;
    professor *p;
    aluno *a;

    while(aux != NULL){

        if(x->tipo == 1){
            p = x->profissao;
            if(p->matricula == matricula){
                printf("Professor removido\n");
                break;
            }
        }else{
            a = x->profissao;
            if(a->matricula == matricula){
                printf("Aluno removido\n");
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
    else if(ant == NULL){
        l = aux->prox;
    }else{
        ant->prox = aux->prox;
    }

    free(aux);
    return l;

}

humano *criarPessoa()
{
    int tipo;

    printf("1 - Professor\n");
    printf("2 - Aluno\n");
    printf("Informe o tipo de pessoa: ");
    scanf("%d", &tipo);

    humano *h;
    h->tipo = tipo;
    professor *p;
    aluno *a;

    if(tipo == 1)
    {
        h->profissao = (professor *) p;

        
        printf("Informe o nome do professor: ");
        scanf("%s", p->nome);
        printf("Informe a matricula do professor: ");
        scanf("%d", &p->matricula);
        printf("Informe o salario do professor: ");
        scanf("%d", &p->salario);

        h->profissao = p;

        verificaProfissao(p);
    }
    else if(tipo == 2)
    {
        h->profissao = (aluno *) a;

        printf("Informe o nome do aluno: ");
        scanf("%s", a->nome);
        printf("Informe a matricula do aluno: ");
        scanf("%d", &a->matricula);
        printf("Informe o ano de ingresso do aluno: ");
        scanf("%d", &a->anoIngresso);
        printf("Informe o curso do aluno: ");
        scanf("%s", a->curso);

        verificaProfissao(p);
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
        printf("Lista vazia, inserindo no inicio\n");
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

    imprimirLista(l);

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