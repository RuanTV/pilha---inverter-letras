#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

//dados a serem armazenados
struct informacoes{
    char dado;
};

//struct da pilha
struct elemento {
    struct informacoes dados;
    struct elemento *prox;
};

typedef struct elemento Pilha;

//prototipos - funcoes base

int inicializa_pilha(Pilha **s);

int empilhar(Pilha **s, char dado);

int topo(Pilha *s, char *dado);

int vazia(Pilha *s);

int desempilhar(Pilha **s);

//prototipos - outras funcoes

int tamanho(Pilha *s, int *tam);

int listar_todos(Pilha *s);

int inverter(Pilha **s);

int conta_palavras(char *palavra, int *qtd);

int empilhar_na_base(Pilha **s, char dado);

int inverter_2(char *palavra);

int main()
{
    //pilhas
    Pilha* s;
    inicializa_pilha(&s);

    //variaveis locais
    char dado = 'a';
    int erro;
    int tam;
    int i;
    char frase[100];

    printf("digite a palavra: ");
    fgets(frase, 100, stdin);
    frase[strlen(frase)-1] = '\0';
    system("cls");
    printf("palavra                    : %s\n", frase);

    inverter_2(frase);

    printf("\npalavra depois da alteracao: %s\n", frase);

    //printf("\n\nlistar todos os elementos: \n");
    //listar_todos(s);

    printf("\n\n");

    return 0;
}


//implementacao - funcoes base

int inicializa_pilha(Pilha **s) {

    *s = NULL;

    return 0;
}

int empilhar(Pilha **s, char dado) {

    Pilha *no = (Pilha*)malloc(sizeof(Pilha));
    if(no == NULL)
        return 1; //erro ao criar elemento

    (*no).dados.dado = dado;

    (*no).prox = *s;

    *s = no;

    return 0;
}

int topo(Pilha *s, char *dado) {

    if(s == NULL)
        return 1; //pilha vazia

    *dado = s->dados.dado;

    return 0;
}

int vazia(Pilha *s) {

    return (s == NULL) ? 1 : 0;
}

int desempilhar (Pilha **s) {

    if(*s == NULL)
        return 1;

    Pilha* aux = *s;

    *s = (*s)->prox;

    free(aux);

    return 0;
}

//implementacao - outras funcoes

int tamanho(Pilha *s, int *tam) {

    *tam = 0;

    if(vazia(s))
        *tam = 0;

    while(!vazia(s)) {

        (*tam)++;
        desempilhar(&s);

    }

    return 0;
}

int listar_todos(Pilha *s) {

    if(vazia(s))
        printf("lista vazia\n");

    //printf("topo\n");

    while(vazia(s) != 1) {

        printf("%c", s->dados.dado);
        desempilhar(&s);
    }

    return 0;
}

int inverter(Pilha **s) {

    if(vazia(*s))
        return 1; //nao e possivel inverter uma lista vazia

    Pilha *aux;
    inicializa_pilha(&aux);

    char dado = 0;


    while(vazia(*s) != 1) {

        topo(*s, &dado);
        empilhar(&aux, dado);
        desempilhar(s);
    }

    *s = aux;

    return 0;
}

int conta_palavras(char *palavra, int *qtd) {

    *qtd = 0;
    int tam = strlen(palavra);
    int i;

    for(i=0; i<tam; i++) {

        if(palavra[i] != ' ' && (palavra[i+1] == ' ' || palavra[i+1] == '\0'))
            (*qtd)++;

    }

    return 0;

}

int empilhar_na_base(Pilha **s, char dado) {

    Pilha* aux;
    inicializa_pilha(&aux);
    char info;

    while(vazia(*s) != 1) {

        topo(*s, &info);
        empilhar(&aux, info);
        desempilhar(s);

    }
    empilhar(s, dado);

    while(vazia(aux) != 1) {

        topo(aux, &info);
        empilhar(s, info);
        desempilhar(&aux);

    }

    return 0;
}

int inverter_2(char *palavra) {

    int t=0;
    int tam = strlen(palavra);
    int i, j;
    int qtd=0;
    char letra[1];
    letra[0] = 'a';

    //variaveis de espaco pra ajustar os espacos da palavra
    int qtd_espacos=0;
    int qtd_espacos2=0;
    int qtd_total_espacos=0;
    int espacos_no_fim=0;
    int espacos_no_inicio=0;

    for(i=0; i<tam; i++)
        if(palavra[i] == ' ')
            qtd_total_espacos++;

    for(i=0; i<tam; i++) {
        if(palavra[i] != ' ')
            break;
        if(palavra[i] == ' ')
            espacos_no_inicio++;
    }

    conta_palavras(palavra, &qtd);

    Pilha **p = (Pilha**)malloc(sizeof(Pilha)*qtd);

    for(i=0; i<qtd; i++) {
        inicializa_pilha(&(p[i]));
    }

    for(i=0; i<tam; i++) {

        if(palavra[i] != ' ') {
            empilhar(&(p[t]), palavra[i]);
        } else {
            qtd_espacos++;
        }

        if(palavra[i] != ' ' && (palavra[i+1] == ' ' || palavra[i+1] == '\0')) {
            if(t != 0)
                for(j=0; j < qtd_espacos; j++)
                    empilhar(&(p[t]), ' ');

            t++;

            qtd_espacos2 += qtd_espacos;

            qtd_espacos=0;
        }

    }

    espacos_no_fim = qtd_total_espacos - qtd_espacos2;

    //ajustar espacos do final
    if(t==0)
        for(i=0; i<espacos_no_fim; i++)
            empilhar_na_base(&(p[0]), ' ');
    else
        for(i=0; i<espacos_no_fim; i++)
            empilhar_na_base(&(p[t-1]), ' ');

    //ajustar espacos do inicio
    for(i=0; i<espacos_no_inicio; i++)
        empilhar(&(p[0]), ' ');

    //devolver para a funcao main
    j=0;
    for(i=0; i<t; i++) {

        while(vazia(p[i]) != 1) {
            topo(p[i], letra);
            desempilhar( &(p[i]) );
            palavra[j] = letra[0];
            j++;
        }

    }
    palavra[j] = '\0';


    return 0;

}
