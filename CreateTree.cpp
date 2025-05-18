#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <conio2.h>
#include <string.h>
#include "Tad.h"
#include <locale.h>

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


void Exibe(TpLista *list){
	
	while(list!=NULL){
		printf("Palavra:%s | freq:%d\n", list->palavra, list->frequencia);
		list= list->prox;
	}	
}

int main(){
	setlocale(LC_ALL, "Portuguese");
	TpLista *list= NULL;
	char text[10000];
	strcpy(text,"Amar é sonhar, sonhar é viver, viver é curtir, curtir é amar. Cada um terá uma escolha, cada um fará a escolha, cada um escolhe a sua escolha. Levaremos um tempo para crescer, levaremos um tempo para amadurecer, levaremos um tempo para entender, levaremos um tempo para envelhecer, levaremos um tempo para morrer");
	BuildList(&list,text);
	Exibe(list);

}
