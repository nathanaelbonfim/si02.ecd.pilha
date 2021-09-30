#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAMANHO_LINHA 40 


typedef struct elemento {
    int dados;
    struct elemento* prox;
};

int pi_liberada = 0;

typedef struct elemento *Pilha;

Pilha verificaPilha(Pilha* pi);
Pilha* criaPilha(int* liberada);
int inserePilha(Pilha* pi);
int tamanhoPilha(Pilha *pi);
int removePilha(Pilha *pi);
int consultaTopoPilha(Pilha *pi, int dados);
int liberaPilha(Pilha *pi);

//================================
// Funções auxiliares
//================================

// Substitui o fflush(stdin) que não funciona no linux
void limparBuffer() {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF) { }
}

// Limpa a tela no Windows e Linux
void limpaTela() {
    #ifdef WINDOWS
        system("cls");
    #else
        system("clear");
    #endif
}

// Desenha uma linha com uma qtd e caractere específicos
// Inclui '\n'
void desenhaLinha(char caractere, int qtdCaracteres) {
    for (int i = 0; i < qtdCaracteres; i++) {
        putchar(caractere);
    }
    printf("\n");
}

void desenhaCabecalho(char frase[]) {
    limpaTela();
    desenhaLinha(*"=", TAMANHO_LINHA);
    printf(" %s\n", frase);
    desenhaLinha(*"-", TAMANHO_LINHA);
}

//================================



int main(void) {
    Pilha *pi = NULL;
    int x, final, dados;

    do {
        puts("1 - Cria");
        puts("2 - Inseri");
        puts("3 - Tamanho");
        puts("4 - Remove");
        puts("5 - Topo");
        puts("6 - Libera");
        puts("0 - Sair");

        scanf("%i", &final);

        switch(final) {
            case 1: { pi = criaPilha(&pi_liberada); break; }
            case 2: { x  = inserePilha(pi); }
            case 3: { x  = tamanhoPilha(pi); }
            case 4: { x  = removePilha(pi); }
            case 5: { x  = consultaTopoPilha(&pi, &dados); }
            case 6: { x  = liberaPilha(pi); }
            case 0: { puts("---<Fim da execução>---\n"); break; }
            default: { puts("Valor inválido!\n"); break; }
        }

        limparBuffer();
        limpaTela();
    } while (final != 0);
}


Pilha* criaPilha(int *liberada) {
    if (pi_liberada != 0) {
        puts("Já existe uma pilha criada!'\n");
        limparBuffer();
        return NULL;
    }

    Pilha *pi = (Pilha*)malloc(sizeof(Pilha));

    if (pi == NULL) {
        puts("Não foi possível criar a pilha por falta de espaço!");
    } else {
        *pi = NULL;
        pi_liberada = 1;
    }

    limparBuffer();
    return pi;
}

int inserePilha(Pilha *pi) {
    int dados = 0;

    puts("Digite um dado: ");
    scanf("%d", &dados);
    
    // Pilha não criada ou faltou espaço
    if (pi == NULL) return 0; 

    struct elemento no = (elemento*)malloc(sizeof(elemento));

    // Pilha está vazia
    if (no == NULL) return 2;

    // Realização do empilhamento
    no->dados = dados;
    no->prox = (*pi);
    *pi = no;

    return 1;
}

int tamanhoPilha(Pilha *pi) {
    // Pilha não criada ou faltou espaço
    if (pi == NULL) return 0;

    // Pilha está vazia
    if ((*pi)== NULL) return -1;

    int contador = 0;
    struct elemento *no = *pi;

    // Conta a quantidade de elementos na pilha
    while (no != NULL) {
        contador++;
        no = no->prox;
    }

    return contador;
}

int removePilha(Pilha *pi) {
    // Pilha não criada ou faltou espaço
    if (pi == NULL) return 0;

    // Pilha está vazia
    if ((*pi)== NULL) return 2;

    printf("%p", pi);
    getche();

    // Realização do desempilhamento
    elemento *no = *pi;
    *pi = no->prox;
    free(no);

    return 1;
}

int consultaTopoPilha(Pilha *pi, int dados) {
        // Pilha não criada ou faltou espaço
    if (pi == NULL) return 0;

    // Pilha está vazia
    if ((*pi)== NULL) return 2;

    // Exibe o elemento do topo da pilha
    dados = (*pi)->dados;
    printf("\nTopo = %i\n", dados);
    getche();

    return 1;
}

int liberaPilha(Pilha *pi) {
    if (pi == NULL) {
        elemento *no;

        while ((*pi) != NULL) {
            no = *pi;
            *pi = (*pi)->prox;
        }

        pi = NULL;
        free(pi);
        
        // Pilha liberada
        pi_liberada = 0;
        return 1;
    }

    // Pilha não existe
    return 0;
}

