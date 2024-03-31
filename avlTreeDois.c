#include "stdio.h"
#include "stdlib.h"

struct No
{
	int dado;
	int altura;
	struct No* esquerda;
	struct No* direita;
};
//Inserção e exclusão em Árvore AVL
struct No* NovoNo(int dado)
{
	struct No* temp = (struct No*)malloc(sizeof(struct No));
	temp->dado = dado;
	temp->esquerda = NULL;
	temp->direita = NULL;
	temp->altura = 1;
	return temp;
}

int maximo(int a,int b)
{
 	return (a>b)?a:b;
}

int altura(struct No* no)
{
	if(no==NULL)
		return 0;

 	return no->altura;
}

int Balanceamento(struct No* no)
{
	if(no==NULL)
		return 0;

 	return altura(no->esquerda) - altura(no->direita);
}

struct No* RotacaoEsquerda(struct No* z)
{
	struct No* y = z->direita;
	struct No* t2 = y->esquerda;

	y->esquerda = z;
	z->direita = t2;

	z->altura = maximo(altura(z->esquerda),altura(z->direita))+1;
	y->altura = maximo(altura(y->esquerda),altura(y->direita))+1;

	return y;
}

struct No* RotacaoDireita(struct No* z)
{
	struct No* y = z->esquerda;
	struct No* t3 = y->direita;

	y->direita = z;
	z->esquerda = t3;

	z->altura = maximo(altura(z->esquerda),altura(z->direita))+1;
	y->altura = maximo(altura(y->esquerda),altura(y->direita))+1;

	return y;
}

void preordem(struct No* raiz)
{
	if(raiz==NULL)
		return;

	printf("%d ",raiz->dado);
	preordem(raiz->esquerda);
	preordem(raiz->direita);
}

struct No* EncontrarMinimo(struct No* no)
{
	while(no->esquerda!=NULL)
		no = no->esquerda;

	return no;
}

struct No* Excluir(struct No* raiz,int dado)
{
	if(raiz==NULL)
		return raiz;

	if(dado < raiz->dado)
		raiz->esquerda = Excluir(raiz->esquerda,dado);

	else if(dado > raiz->dado)
		raiz->direita = Excluir(raiz->direita,dado);

	else
	{
		if(raiz->direita==NULL && raiz->esquerda==NULL)
		{
			free(raiz);
			raiz = NULL;
		}

		else if(raiz->esquerda!=NULL && raiz->direita==NULL)
		{
			struct No* temp = raiz->esquerda;
			raiz = raiz->esquerda;
			free(temp);
		}

		else if(raiz->direita!=NULL && raiz->esquerda==NULL)
		{
			struct No* temp = raiz->direita;
			raiz = raiz->direita;
			free(temp);
		}

		else
		{
			struct No* temp = EncontrarMinimo(raiz->direita);
			raiz->dado = temp->dado;
			raiz->direita = Excluir(raiz->direita,temp->dado);
		}
	}
	if(raiz==NULL)
		return raiz;

	raiz->altura = 1 + maximo(altura(raiz->esquerda),altura(raiz->direita));

	int balanceamento = Balanceamento(raiz);

	//Caso Esquerda Esquerda
	if(balanceamento > 1 && Balanceamento(raiz->esquerda) >=0)
		return RotacaoDireita(raiz);

	// Caso Direita Direita
	if(balanceamento < -1 && Balanceamento(raiz->direita) <=0)
		return RotacaoEsquerda(raiz);

	// Caso Esquerda Direita
	if(balanceamento > 1 && Balanceamento(raiz->esquerda) < 0)
	{
		raiz->esquerda = RotacaoEsquerda(raiz->esquerda);
		return RotacaoDireita(raiz);
	}
	
	//Caso Direita Esquerda
	if(balanceamento < -1 && Balanceamento(raiz->direita) > 0)
	{
		raiz->direita = RotacaoDireita(raiz->direita);
		return RotacaoEsquerda(raiz);
	}
	return raiz;
}

struct No* Inserir(struct No* raiz,int dado)
{
	if(raiz==NULL)
		return NovoNo(dado);

	if(dado < raiz->dado)
		raiz->esquerda = Inserir(raiz->esquerda,dado);

	else if(dado > raiz->dado)
		raiz->direita = Inserir(raiz->direita,dado);

	else
		return raiz;

	raiz->altura = maximo(altura(raiz->esquerda),altura(raiz->direita))+1;

	int balanceamento = Balanceamento(raiz);

	// Caso Esquerda Esquerda
	if(balanceamento > 1 && dado < raiz->esquerda->dado)
		return RotacaoDireita(raiz);

	// Caso Direita Direita
	if(balanceamento < -1 && dado > raiz->direita->dado)
		return RotacaoEsquerda(raiz);

	// Caso Esquerda Direita
	if(balanceamento > 1 && dado > raiz->esquerda->dado)
	{
		raiz->esquerda = RotacaoEsquerda(raiz->esquerda);
		return RotacaoDireita(raiz);
	}

	// Caso Direita Esquerda
	if(balanceamento < -1 && dado < raiz->direita->dado)
	{
		raiz->direita = RotacaoDireita(raiz->direita);
		return RotacaoEsquerda(raiz);
	}

	return raiz;
}

// Esse main é para a segunda questão
int main()
{
	struct No* raiz = NULL;

    //estrutura inicial
	raiz = Inserir(raiz,7);
	raiz = Inserir(raiz,5);
	raiz = Inserir(raiz,25);
	raiz = Inserir(raiz,10);
	raiz = Inserir(raiz,50);
    raiz = Inserir(raiz,3);
	raiz = Inserir(raiz,8);
    raiz = Inserir(raiz,20);
	raiz = Inserir(raiz,30);
	/*
				ÁRVORE AVL -->      7 
								  /   \	
								5      25
							   /     /    \
							  3      10    50
							 /      /  \   /
						    1      8   20 30
	*/
	raiz = Inserir(raiz,1);
	raiz = Inserir(raiz,64);
	raiz = Inserir(raiz,12);
	raiz = Inserir(raiz,18);
	raiz = Inserir(raiz,66);
	raiz = Inserir(raiz,38);
	raiz = Inserir(raiz,95);
	raiz = Inserir(raiz,58);
	raiz = Inserir(raiz,59);
	raiz = Inserir(raiz,70);
	raiz = Inserir(raiz,68);
	raiz = Inserir(raiz,39);
	raiz = Inserir(raiz,62);
	raiz = Inserir(raiz,7);
	raiz = Inserir(raiz,60);
	raiz = Inserir(raiz,43);
	raiz = Inserir(raiz,16);
    raiz = Inserir(raiz,67);
	raiz = Inserir(raiz,34);
	raiz = Inserir(raiz,35);

	/*
            ÁRVORE AVL -->     __________50__________
                              /                      \	
                        ____10____                ____66____
                       /          \              /          \
                      7            25            59          70
                    /   \        /    \        /   \        /   \
                   7     8      18     38     58   62      68   95
                 /  \          /  \   /  \        /  \    /
                1    5       12   20 34  39      60  64  67
				               \    / \    \
							   16  30 35   43
	*/
	printf("\nTravessia pre-ordem da arvore: "); preordem(raiz);

	raiz = Excluir(raiz,35);
	raiz = Excluir(raiz,34);
	raiz = Excluir(raiz,67);
	raiz = Excluir(raiz,16);
	raiz = Excluir(raiz,43);
	raiz = Excluir(raiz,60);
	raiz = Excluir(raiz,7);
	raiz = Excluir(raiz,62);
	raiz = Excluir(raiz,39);
	raiz = Excluir(raiz,68);
	raiz = Excluir(raiz,70);
	raiz = Excluir(raiz,59);
	raiz = Excluir(raiz,58);
	raiz = Excluir(raiz,95);
	raiz = Excluir(raiz,38);
	raiz = Excluir(raiz,66);
	raiz = Excluir(raiz,18);
	raiz = Excluir(raiz,12);
	raiz = Excluir(raiz,64);
	raiz = Excluir(raiz,1);

	/*
				ÁRVORE AVL -->      10 
								  /    \	
								7       25
							   / \     /  \
							  3   8   20   50
							   \           /
							    5         30
							
	*/

	printf("\nTravessia pre-ordem apos excluir 50, 95, 70, 60, 35 : "); preordem(raiz);
	return 0;
}