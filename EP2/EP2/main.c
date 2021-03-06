#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct no {
  int valor;
  struct no *esquerdo, *direito;
  short altura;
} No;

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

#pragma region AVL
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
#pragma endregion

//cria numeros para um array
void criarNumros(int *array, int qtdElemento) {
  for (int i = 0; i < qtdElemento; i++) {
    array[i] = rand()%50;
  }
}

//verifica se os numeros de um array não possui repetidos
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
#pragma region BST
//insere um no na arvore BST
void inserirBST(No *raiz, int num){
    
    
        if(raiz->valor < num)
        {
            if(raiz->direito == NULL)
            {
                raiz->direito = novoNo(num);
                return;
            }
            inserirBST(raiz->direito, num);
        }
        else if(raiz->valor > num)
        {
            if(raiz->esquerdo == NULL)
            {
                raiz->esquerdo = novoNo(num);
                return;
            }
            inserirBST(raiz->esquerdo, num);
        }
    
}

//printa a arvore para facilitar a visualizacao
void bstIdentPrint(No *raiz, int espacos)
{//vai ir para o ultimo da direita e imprime depois volta e imprime e vai ate o ultimo da esquerda e imprime
  if(raiz != NULL)
    {
      bstIdentPrint(raiz->direito, espacos+1);
      for(int i = 0; i<espacos; i++)
        {
          printf("\t");//tabs
        }
      printf("%d\n",raiz->valor);
      bstIdentPrint(raiz->esquerdo, espacos+1);
      
    }
}

//cria a amostra "cria uma arvore BST"
No *BSTAmostra(int elementos, int *array) // quantidade de elemntos
{
    No* raiz = novoNo(array[0]);
    int repetido = 0;
  for (int i = 1; i < elementos; i++) {
    inserirBST(raiz, array[i]);
    if(repetido == 1)
    {
        repetido = 0;
        do
        {
            inserirBST(raiz, rand()%50);
        }while(repetido != 1);
        
    }
  }
  return raiz;
}
#pragma endregion

//calcula a altura de qualquer uma das arvores
int altura(No *raiz){
    if(raiz == NULL){
        return -1;
    }
    else{
        int esquerdo = altura(raiz->esquerdo);
        int direito = altura(raiz->direito);
        if(esquerdo > direito)
            return esquerdo + 1;
        else
            return direito + 1;
    }
}
//calcula a media da altura de bst ou avl
float mediaAltura(float *array, float qtdAmostras)
{
    float media = 0;
    for(int i = 0; i < qtdAmostras; i++)
    {
        media += array[i];
    }
    return media/qtdAmostras;
}

int main() {
srand(time(NULL));
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
        int elementos;
        int qtdAmostras;
      printf("quantidade de elementos: ");
      scanf("%d", &elementos);
      
      printf("Quantidade de Amostras: ");
      scanf("%d", &qtdAmostras);

      float arrayAVL[qtdAmostras];
      float arrayBST[qtdAmostras];
      
      int array[elementos];
      
      for(int i = 0; i < qtdAmostras; i++)
      {
          criarNumros(array, elementos);
          verificacao(array, elementos);
          raiz = novaAmostra(elementos, array);
          printf("\nAVL");
          imprimir(raiz, 1);
        arrayAVL[i] = altura(raiz)+1;
        
          printf("\nAltura da AVL: %.2f", arrayAVL[i]);
        
          
          printf("\n-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-");
          printf("\nBST\n");
          raiz = BSTAmostra(elementos, array);
          bstIdentPrint(raiz,1);

        arrayBST[i] = altura(raiz)+1;
        
          printf("\nAltura da BST: %.2f", arrayBST[i]);
          printf("\n-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-");
      }

      float amostras = qtdAmostras;
      float mediaAVL = mediaAltura(arrayAVL, amostras);
      float mediaBST = mediaAltura(arrayBST, amostras);
      float mediaGeral = (mediaAVL+mediaBST)/2;
      
      printf("\nMedia da altura AVL: %.2f", mediaAVL);
      printf("\nMedia da altura BST: %.2f", mediaBST);
      printf("\nMedia da geral: %.2f", mediaGeral);

      
      break;
    }
    default:
      printf("\nOcao invalida!!!\n");
    }

  } while (opcao != 0);

  return 0;
}