#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct no {
    int valor;
    struct no* esquerdo, * direito;
    short altura;
} No;


#pragma region AVL
/*
    Função que cria um novo nó
    x -> valor a ser inserido no nó
    Retorna: o endereço do nó criado
*/
No* novoNo(int x) {
    No* novo = malloc(sizeof(No));

    if (novo) {
        novo->valor = x;
        novo->esquerdo = NULL;
        novo->direito = NULL;
        novo->altura = 0;
    }
    else
        printf("\nERRO ao alocar nó em novoNo!\n");
    return novo;
}

/*
    Retorna o maior dentre dois valores
    a, b -> altura de dois nós da árvore
*/
short maior(short a, short b) { return (a > b) ? a : b; }

//  Retorna a altura de um nó ou -1 caso ele seja null
short alturaDoNo(No* no) {
    if (no == NULL)
        return -1;
    else
        return no->altura;
}

//   Calcula e retorna o fator de balanceamento de um nó
short fatorDeBalanceamento(No* no) {
    if (no)
        return (alturaDoNo(no->esquerdo) - alturaDoNo(no->direito));
    else
        return 0;
}

// --------- ROTAÇÕES ---------------------------

// função para a rotação à esquerda
No* rotacaoEsquerda(No* r) {
    No* y, * f;

    y = r->direito;
    f = y->esquerdo;

    y->esquerdo = r;
    r->direito = f;

    r->altura = maior(alturaDoNo(r->esquerdo), alturaDoNo(r->direito)) + 1;
    y->altura = maior(alturaDoNo(y->esquerdo), alturaDoNo(y->direito)) + 1;

    return y;
}

// função para a rotação à direita
No* rotacaoDireita(No* r) {
    No* y, * f;

    y = r->esquerdo;
    f = y->direito;

    y->direito = r;
    r->esquerdo = f;

    r->altura = maior(alturaDoNo(r->esquerdo), alturaDoNo(r->direito)) + 1;
    y->altura = maior(alturaDoNo(y->esquerdo), alturaDoNo(y->direito)) + 1;

    return y;
}

No* rotacaoEsquerdaDireita(No* r) {
    r->esquerdo = rotacaoEsquerda(r->esquerdo);
    return rotacaoDireita(r);
}

No* rotacaoDireitaEsquerda(No* r) {
    r->direito = rotacaoDireita(r->direito);
    return rotacaoEsquerda(r);
}

/*
    Função para realizar o balanceamento da árvore após uma inserção ou remoção
    Recebe o nó que está desbalanceado e retorna a nova raiz após o
   balanceamento
*/
No* balancear(No* raiz) {
    short fb = fatorDeBalanceamento(raiz);

    // Rotação à esquerda
    if (fb < -1 && fatorDeBalanceamento(raiz->direito) <= 0)
        raiz = rotacaoEsquerda(raiz);

    // Rotação à direita
    else if (fb > 1 && fatorDeBalanceamento(raiz->esquerdo) >= 0)
        raiz = rotacaoDireita(raiz);

    // Rotação dupla à esquerda
    else if (fb > 1 && fatorDeBalanceamento(raiz->esquerdo) < 0)
        raiz = rotacaoEsquerdaDireita(raiz);

    // Rotação dupla à direita
    else if (fb < -1 && fatorDeBalanceamento(raiz->direito) > 0)
        raiz = rotacaoDireitaEsquerda(raiz);

    return raiz;
}

/*
    Insere um novo nó na árvore
    raiz -> raiz da árvore
    x -> valor a ser inserido
    Retorno: endereço do novo nó ou nova raiz após o balanceamento
*/
No* inserir(No* raiz, int x) {
    if (raiz == NULL) // árvore vazia
        return novoNo(x);
    else { // inserção será à esquerda ou à direita
        if (x < raiz->valor)
            raiz->esquerdo = inserir(raiz->esquerdo, x);
        else if (x > raiz->valor)
            raiz->direito = inserir(raiz->direito, x);
        else
            printf("\nInsercao nao realizada!\nO elemento %d a existe!\n", x);
    }

    // Recalcula a altura de todos os nós entre a raiz e o novo nó inserido
    raiz->altura = maior(alturaDoNo(raiz->esquerdo), alturaDoNo(raiz->direito)) + 1;

    // verifica a necessidade de rebalancear a árvore
    raiz = balancear(raiz);

    return raiz;
}

/*
    Função para remover um nó da Árvore binária balanceada
    Pode ser necessário rebalancear a árvore e a raiz pode ser alterada
    por isso precisamos retornar a raiz
*/
No* remover(No* raiz, int chave) {
    if (raiz == NULL) {
        printf("Valor nao encontrado!\n");
        return NULL;
    }
    else { // procura o nó a remover
        if (raiz->valor == chave) {
            // remove nós folhas (nós sem filhos)
            if (raiz->esquerdo == NULL && raiz->direito == NULL) {
                free(raiz);
                printf("Elemento folha removido: %d !\n", chave);
                return NULL;
            }
            else {
                // remover nós que possuem 2 filhos
                if (raiz->esquerdo != NULL && raiz->direito != NULL) {
                    No* aux = raiz->esquerdo;
                    while (aux->direito != NULL)
                        aux = aux->direito;
                    raiz->valor = aux->valor;
                    aux->valor = chave;
                    printf("Elemento trocado: %d !\n", chave);
                    raiz->esquerdo = remover(raiz->esquerdo, chave);
                    return raiz;
                }
                else {
                    // remover nós que possuem apenas 1 filho
                    No* aux;
                    if (raiz->esquerdo != NULL)
                        aux = raiz->esquerdo;
                    else
                        aux = raiz->direito;
                    free(raiz);
                    printf("Elemento com 1 filho removido: %d !\n", chave);
                    return aux;
                }
            }
        }
        else {
            if (chave < raiz->valor)
                raiz->esquerdo = remover(raiz->esquerdo, chave);
            else
                raiz->direito = remover(raiz->direito, chave);
        }

        // Recalcula a altura de todos os nós entre a raiz e o novo nó inserido
        raiz->altura =
            maior(alturaDoNo(raiz->esquerdo), alturaDoNo(raiz->direito)) + 1;

        // verifica a necessidade de rebalancear a árvore
        raiz = balancear(raiz);

        return raiz;
    }
}

void imprimir(No* raiz, int nivel) {
    int i;
    if (raiz) {
        imprimir(raiz->direito, nivel + 1);
        printf("\n\n");

        for (i = 0; i < nivel; i++)
            printf("\t");

        printf("%d", raiz->valor);
        imprimir(raiz->esquerdo, nivel + 1);
    }
}

No* novaAmostra(int elementos) // quantidade de elemntos
{
    // srand(time(NULL));
    No* raiz = novoNo((rand() % 49) + 1);

    for (int i = 0; i < elementos - 1; i++) {
        raiz = inserir(raiz, (rand() % 49) + 1);
    }
    return raiz;
}
#pragma endregion

#pragma region BST
void bstIdentPrint(No* raiz, int espacos)
{//vai ir para o ultimo da direita e imprime depois volta e imprime e vai ate o ultimo da esquerda e imprime
    if (raiz != NULL)
    {
        bstIdentPrint(raiz->direito, espacos + 1);
        for (int i = 0; i < espacos; i++)
        {
            printf("\t");//tabs
        }
        printf("%d\n", raiz->valor);
        bstIdentPrint(raiz->esquerdo, espacos + 1);

    }    
}

void adicionarBst(No* raiz, int x) {
    if (raiz == NULL) // árvore vazia
        return novoNo(x);
    else { // inserção será à esquerda ou à direita 
        if (x > raiz->valor)
        {
            if (raiz->direito == NULL)//verificar se a direita for nulo adicionar lá
            {
                raiz->direito = novoNo(x);
                return;
            }
            adicionarBst(raiz->direito, x);
        }
        else if (x < raiz->valor)
        {
            if (raiz->esquerdo == NULL)
                //verificar se a esquerda for nulo adicionar lá
            {
                raiz->esquerdo = novoNo(x);
                return;
            }
            adicionarBst(raiz->esquerdo, x);
        }
        
    }
}

No* BSTAmostra(int elementos) // quantidade de elemntos
    {
        No* raiz = novoNo(rand() % 50);

        for (int i = 0; i < elementos; i++) {
            inserir(raiz, rand() % 50);
        }
        return raiz;
    }
#pragma endregion


int main(void) {
    int res =0, qtdAmostras = 0, qtdElemento = 0;

    do {

        printf("\nDigite 1 para nova simulação\nDigite 2 para sair\n");
        scanf_s("%d", &res); // resposta

        switch (res) {
        case 1:
            printf("Digite a quantidade de amostras: ");
            scanf_s("%d", &qtdAmostras);
            printf("Digite a quantidade de elementos para cada amostra: ");
            scanf_s("%d", &qtdElemento);
            for (int i = 0; i < qtdAmostras; i++)
            {
                printf("\nAVL amostra %d\n", i+1);
                imprimir(novaAmostra(qtdElemento), 0);

                printf("\nBST amostra %d\n  ", i + 1);
                bstIdentPrint(BSTAmostra(qtdElemento), 0);
            }

            break;
        case 2:
            break;
        }

    } while (res != 2);

    return 0;
}

