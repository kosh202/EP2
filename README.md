# EP2

Utilizei algumas funções que fiz com a lista de  exercicios sobre arvores para completar esse EP, que seria as partes as funções de como fazer uma arvore BST
``` C

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
```
e principalmente o de printar
```c
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
```
os exercicios me ajudaram bastrante no EP e para estudar para a prova.

* O programa está dentro da pasta EP
