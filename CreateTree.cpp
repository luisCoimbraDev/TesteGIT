#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <conio2.h>
#include <string.h>
#include "Tad.h"
#include <locale.h>


void Exibe(TpLista *list);

char SearchContent(char subs[], TpLista **list){ // aqui eu procuro na lista se ja existe a palavra que eu to buscando
	TpLista *aux;
	
	if((*list)==NULL){
		(*list) = (TpLista*)malloc(sizeof(TpLista));
		(*list)->prox = NULL;
		strcpy((*list)->palavra, subs);
		(*list)->frequencia = 1;
		
	}else
		if(stricmp((*list)->palavra,subs)==0){
			(*list)->frequencia++;
		}
		else{
			aux = (*list);
			while(aux->prox!=NULL && stricmp(aux->palavra,subs)!=0)
				aux= aux->prox;
			
			if(stricmp(aux->palavra,subs)!=0){
				aux->prox = (TpLista*)malloc(sizeof(TpLista));
				strcpy(aux->prox->palavra, subs);
				aux->prox->frequencia = 1;
				aux->prox->prox = NULL;
			}else{
				aux->frequencia++;
			}
		}	
}

void SortList(TpLista **list){
	TpLista *prox;
	TpLista *atual;
	char aux[30];
	int freq;
	
	atual =  *list;
	while(atual!=NULL){
		prox = atual->prox;
		while(prox!=NULL){
			if(atual->frequencia<prox->frequencia){
				strcpy(aux, atual->palavra);
				freq = atual->frequencia;
				strcpy(atual->palavra, prox->palavra);
				atual->frequencia = prox->frequencia;
				strcpy(prox->palavra, aux);
				prox->frequencia = freq;
			}
			prox = prox->prox;
		}
		atual = atual->prox;
	}
	

}

void BuildList(TpLista **list, char text[]){ // aqui eu construo a lista da arvore de Huffman
	char substring[20];
	TpLista *auxlist;
	int i=0;
	int j=0;
	
	while(i<strlen(text)+1){
		
		j=0;
		while(text[i]!='\0' && text[i]!= ' ' && text[i]!= '.' && text[i]!= ',' && text[i]!= '!' && text[i]!= ';' && text[i]!= '?')
			substring[j++] = text[i++];
		
		
		substring[j] = '\0';
		if(strcmp(substring, "\0") !=0)
			SearchContent(substring, &(*list));
		
		if(text[i] == ' ')
			SearchContent(" ", &(*list));
		i++;
	}
}

void setNo(TpLista *list){
	int cod = 0;
	while(list != NULL){
		list->no = (Tree*)malloc(sizeof(Tree));
		list->no->codigo = cod++;
		list->no->dir = NULL;
		list->no->esq = NULL;
		
		list = list->prox;
	}
}

Tree *CriaNo(int cod){
	
	Tree *t = (Tree*)malloc(sizeof(Tree));
	t->codigo = cod;
	t->esq = NULL;
	t->dir = NULL;
	
	return t;
}

Tree *CriaNovaTree(int esquerda, int direita){
	
	Tree *t = (Tree*)malloc(sizeof(Tree));
	t->codigo = -1;
	t->esq = CriaNo(esquerda);
	//printf("codigo esquerda: %d \t", t->esq->codigo);
	t->dir = CriaNo(direita);
	//printf("codigo direita: %d \t", t->dir->codigo);

	
	return t;
}

TpLista * CriaNovaLista(int frequencia, int esquerda, int direita){
	
	TpLista *lista = (TpLista*)malloc(sizeof(TpLista));
	lista->frequencia = frequencia;
	//printf("frequencia: %d \t", lista->frequencia);
	lista->no = CriaNovaTree(esquerda,direita);
	//printf("cabeca no: %d \n\n", lista->no->codigo);
	strcpy(lista->palavra,"");
	lista->prox = NULL;
	
	return lista;
}

void reposiciona(TpLista **list, TpLista **anterior, TpLista **atual, TpLista **proximo){
	
	*anterior = *list;
	
	while((*anterior)->prox->prox->prox != NULL){
		*anterior = (*anterior)-> prox;
		*atual = (*anterior) -> prox;
		*proximo = (*atual) -> prox;
	}

	
}

void InserirOrd(TpLista **list, TpLista *novo){
	
	TpLista *aux = novo;
	if(*list == NULL){
		*list = aux;
	}else{
		
		if(aux->frequencia > (*list)->frequencia){
			aux->prox = *list;
			*list = aux;
		}else{
			TpLista *pos = *list, *ant = NULL;
			while(pos != NULL && aux->frequencia < pos->frequencia){
				ant = pos;
				pos = pos->prox;
			}
			if(pos != NULL){
				aux->prox = pos;
			}
			ant->prox = aux;	
		}
	}
	
}

void criaArvoreHuffman(TpLista **list){
	
	TpLista *anterior = NULL, *atual = NULL, *proximo = NULL;
	reposiciona(&(*list), &anterior,&atual,&proximo);
	//printf("Anterior: %s \t Atual: %s \t Proximo: %s \n\n\n", anterior->palavra, atual->palavra, proximo -> palavra);
	
	while((*list)->prox != NULL){
		
		int novaFreq = atual->frequencia + proximo->frequencia;
		//printf("\nFreq total: %d",novaFreq); getch();
		TpLista *aux = CriaNovaLista(novaFreq, atual->no->codigo, proximo->no->codigo);
		anterior->prox = NULL;
		free(atual);
		free(proximo);
		InserirOrd(&(*list),aux);
		//SortList(&(*list));
		//Exibe(*list);
		//printf("\n\n");
		
		reposiciona(&(*list), &anterior,&atual,&proximo);
	}
	
}

void pre_ordem(Tree *raiz){
    if(raiz!=NULL){
        printf("%d\n", raiz->codigo);
        pre_ordem(raiz->esq);
        pre_ordem(raiz->dir);
    }

}

void criarArqBin(TpLista *list){
	
	FILE * ptr = fopen("Tabela.dat", "wb");
	TpHuff huff;
	
	while(list != NULL){
		
		huff.simbolo = list->no->codigo;
		strcpy(huff.palavra, list->palavra);
		huff.num = ' '; //coloquei vazio por enquanto
		
		fwrite(&huff, sizeof(TpHuff), 1, ptr);
		list = list -> prox;
	}
	
	fclose(ptr);
}

void exibeArq(){
	
	FILE * ptr = fopen("Tabela.dat", "rb");
	TpHuff huff;
	
	fread(&huff, sizeof(TpHuff), 1, ptr);
	while(!feof(ptr)){
		printf("Simbolo: %d \t Palavra: %s \t Codigo Huffman: %c\n", huff.simbolo, huff.palavra, huff.num);
		fread(&huff, sizeof(TpHuff), 1, ptr);
	}
	
	fclose(ptr);
}

//só pra ver se ta gravando certo
void Exibe(TpLista *list){
	
	while(list!=NULL){
		printf("Palavra:%s | freq:%d | codigo: %d\n", list->palavra, list->frequencia, list->no->codigo);
		list= list->prox;
	}	
}

int main(){
	setlocale(LC_ALL, "Portuguese");
	TpLista *list= NULL;
	char text[10000];
	strcpy(text,"Amar é sonhar, sonhar é viver, viver é curtir, curtir é amar. Cada um terá uma escolha, cada um fará a escolha, cada um escolhe a sua escolha. Levaremos um tempo para crescer, levaremos um tempo para amadurecer, levaremos um tempo para entender, levaremos um tempo para envelhecer, levaremos um tempo para morrer");
	BuildList(&list,text);
	SortList(&list);
	setNo(list);
	//Exibe(list);
	criaArvoreHuffman(&list);
	pre_ordem(list->no);

}
