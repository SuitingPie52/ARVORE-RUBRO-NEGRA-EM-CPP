//////////////////////////////////////////////////////
// Programa que implenmenta uma Árvore Rubro-Negra //
////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct no {
	
	int numero;
	struct no *esquerda;
	struct no *direita;
	int cor;	// 0 preto, 1 vermelho
	
};

////////////////////////////////////////////////////
// funcao que rotaciona a árvore para a esquerda //
//////////////////////////////////////////////////

struct no* rotacionarEsquerda(struct no *raiz) {
	
	// ROTACAO PROPIAMENTE DITA:
	// raiz - > direita (x) vira a raíz e raiz original vira a raiz -> esquerda
	struct no *x = raiz -> direita;
	raiz -> direita = x -> esquerda; 
	x -> esquerda = raiz;
	
	// AJUSTE DA COR 
	x -> cor = raiz -> cor;
	raiz -> cor = 1;
	
	return x; 
	
}

///////////////////////////////////////////////////
// funcao que rotaciona a árvore para a direita //
/////////////////////////////////////////////////

struct no* rotacionarDireita(struct no *raiz) {
	
	// ROTACAO PROPIAMENTE DITA:
	struct no *x = raiz -> esquerda;
	raiz -> esquerda = x -> direita; 
	x -> direita = raiz;
	
	// AJUSTE DA COR 
	x -> cor = raiz -> cor;
	raiz -> cor = 1;
	
	return x; 
	
}

/////////////////////////////////
// funcao que sobe o vermelho //
///////////////////////////////

void subirVermelho(struct no *raiz) {
	
	raiz -> cor = 1;
	raiz -> esquerda -> cor = 0;
	raiz -> direita -> cor = 0;
	
}

/////////////////////////////////////
// funcao que devolve a cor do nó //
///////////////////////////////////

int vermelho(struct no* raiz) {
	
	int retorno = 0;
	
	if (raiz != NULL) {
		
		retorno = raiz -> cor; 
		
	}
	
	return retorno;
	
}

////////////////////////////////////////
// funcao que insere um nó na árvore //
//////////////////////////////////////

struct no *inserir(struct no *raiz, int numero) {
	
	if (raiz == NULL) {
		
		raiz = (struct no *) malloc(sizeof(struct no));
		raiz -> numero = numero;
		raiz -> esquerda = NULL;	
		raiz -> direita = NULL;
		raiz -> cor = 1; 
		
	} else {
		
		if (numero < raiz -> numero) {
			
			raiz -> esquerda = inserir(raiz -> esquerda, numero);
		} else {
			
			raiz -> direita = inserir(raiz -> direita, numero);
			
		}
		
	}
	
	if ( vermelho(raiz -> direita) &&
		!vermelho(raiz -> esquerda)  ) {
			
			raiz = rotacionarEsquerda(raiz);
			
	}
	
	if ( vermelho(raiz -> esquerda) &&
		 vermelho(raiz -> esquerda -> esquerda)  ) {
		 	
			raiz = rotacionarDireita(raiz);
		 	
	}
	
	if ( vermelho(raiz -> esquerda) &&
		 vermelho(raiz -> direita)  ) {
		 	
		 	subirVermelho(raiz);
		 	
	}
	
	return raiz;
	
}

void imprimir(struct no *raiz, char *endentador) {
	
	if (raiz != NULL) {

		printf("%s%d\n", endentador, raiz -> numero);
		
		char *temp = (char *) malloc(1024 * sizeof(char));
		strcpy(temp, endentador);
		strcat(temp, "---");
	
		imprimir(raiz -> esquerda, temp);
		imprimir(raiz -> direita, temp);
	

	}
	
}

int main () {
	
	struct no *raiz = NULL;
	int i = 0;
	
	for (i = 0; i < 50; i++) {
		
		raiz = inserir(raiz, i);
		
	}
	
	imprimir(raiz, "");
	
}


