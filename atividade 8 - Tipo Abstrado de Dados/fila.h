// Trabalho de Estrutura de Dados
// Tipo Abstrato de Dados
// 20/06/2023
// Arthur Peixoto - github.com/ArthurPxto
// Emanuel Bravo - github.com/bravomanel

#ifndef fila_h
#define fila_h

// scruct da fila com top e vet
typedef struct fila *Fila;
// cria a fila com o tamanho do vetor inserido pelo usuario
Fila criarFila();
// imprime a fila na tela
void imprimirFila(Fila f);
// insere um numero e retorna a fila modificada
Fila inserirFila(Fila f);
// remove um numero e retorna a fila modificada
Fila removerFila(Fila f);
// libera a fila e retorna NULL
void liberarFila(Fila f);


#endif