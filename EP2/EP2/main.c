#include <stdio.h>
#include <stdlib.h>

typedef struct no {
  int valor;
  struct no *esquerdo, *direito;
  short altura;
} No;

/*
    Função que cria um novo nó
    x -> valor a ser inserido no nó
    Retorna: o endereço do nó criado
*/
No *novoNo(int x) {
  No *novo = malloc(sizeof(No));

  if (novo) {
    novo->valor = x;
    novo->esquerdo = NULL;
    novo->direito = NULL;
    novo->altura = 0;
  } else
    printf("\nERRO ao alocar nó em novoNo!\n");
  return novo;
}

/*
    Retorna o maior dentre dois valores
    a, b -> altura de dois nós da árvore
*/
short maior(short a, short b) { return (a > b) ? a : b; }

//  Retorna a altura de um nó ou -1 caso ele seja null
short alturaDoNo(No *no) {
  if (no == NULL)
    return -1;
  else
    return no->altura;
}

//   Calcula e retorna o fator de balanceamento de um nó
short fatorDeBalanceamento(No *no) {
  if (no)
    return (alturaDoNo(no->esquerdo) - alturaDoNo(no->direito));
  else
    return 0;
}

// --------- ROTAÇÕES ---------------------------

// função para a rotação à esquerda
No *rotacaoEsquerda(No *r) {
  No *y, *f;

  y = r->direito;
  f = y->esquerdo;

  y->esquerdo = r;
  r->direito = f;

  r->altura = maior(alturaDoNo(r->esquerdo), alturaDoNo(r->direito)) + 1;
  y->altura = maior(alturaDoNo(y->esquerdo), alturaDoNo(y->direito)) + 1;

  return y;
}

// função para a rotação à direita
No *rotacaoDireita(No *r) {
  No *y, *f;

  y = r->esquerdo;
  f = y->direito;

  y->direito = r;
  r->esquerdo = f;

  r->altura = maior(alturaDoNo(r->esquerdo), alturaDoNo(r->direito)) + 1;
  y->altura = maior(alturaDoNo(y->esquerdo), alturaDoNo(y->direito)) + 1;

  return y;
}

No *rotacaoEsquerdaDireita(No *r) {
  r->esquerdo = rotacaoEsquerda(r->esquerdo);
  return rotacaoDireita(r);
}

No *rotacaoDireitaEsquerda(No *r) {
  r->direito = rotacaoDireita(r->direito);
  return rotacaoEsquerda(r);
}

/*
    Função para realizar o balanceamento da árvore após uma inserção ou remoção
    Recebe o nó que está desbalanceado e retorna a nova raiz após o
   balanceamento
*/
No *balancear(No *raiz) {
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
No *inserir(No *raiz, int x) {
  if (raiz == NULL) // árvore vazia
    return novoNo(x);
  else { // inserção será à esquerda ou à direita
    if (x < raiz->valor)
      raiz->esquerdo = inserir(raiz->esquerdo, x);
    else if (x > raiz->valor)
      raiz->direito = inserir(raiz->direito, x);
    else
      {
          printf("\nInsercao nao realizada!\nO elemento %d a existe!\n", x);
          x = rand()%50;
          if (x < raiz->valor)
            raiz->esquerdo = inserir(raiz->esquerdo, x);
          else if (x > raiz->valor)
            raiz->direito = inserir(raiz->direito, x);
      }
  }

  // Recalcula a altura de todos os nós entre a raiz e o novo nó inserido
  raiz->altura =
      maior(alturaDoNo(raiz->esquerdo), alturaDoNo(raiz->direito)) + 1;

  // verifica a necessidade de rebalancear a árvore
  raiz = balancear(raiz);

  return raiz;
}

void imprimir(No *raiz, int nivel) {
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

No *novaAmostra(int elementos, int *array) // quantidade de elemntos
{
    No* raiz = novoNo(array[0]);
  for (int i = 1; i < elementos; i++) {
    raiz = inserir(raiz, array[i]);
  }
  return raiz;
}

void criarNumros(int *array, int qtdElemento) {
    srand(time(NULL));
  for (int i = 0; i < qtdElemento; i++) {
    array[i] = rand()%50;
  }
}

void verificacao(int *array, int qtdElemento)
{
    int cont;
    
    for(int i = 0; i < qtdElemento; i++)
    {
        if(array[i] == array[i+1])
        {
            array[i] = rand()%50;
            verificacao(array, qtdElemento);
        }
    }
}

//BST


int main() {

  int opcao, valor;
  No *raiz = NULL;

  do {
    printf("\n0 - Sair\n1 - Criar arvore\n");
    scanf("%d", &opcao);

    switch (opcao) {
    case 0:
      printf("Saindo!!!");
      break;
    case 1: {
        raiz = NULL;
      printf("quantidade de elementos: ");
      int elementos;

      scanf("%d", &elementos);
      int array[elementos];

      criarNumros(array, elementos);
      verificacao(array, elementos);
      raiz = novaAmostra(elementos, array);
      printf("AVL");
      imprimir(raiz, 1);
      break;
    }
    default:
      printf("\nOcao invalida!!!\n");
    }

  } while (opcao != 0);

  return 0;
}