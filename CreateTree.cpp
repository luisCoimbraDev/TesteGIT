#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <conio2.h>
#include <string.h>
#include "Tad.h"
#include <locale.h>




void Exibe(TpLista *list){
	
	while(list!=NULL){
		printf("Palavra:%s | freq:%d | codigo: %d\n", list->palavra, list->frequencia, list->no->codigo);
		list= list->prox;
	}	
}


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
	Tree *temp;
	char aux[30];
	int freq;
	TpLista toma;
	
	atual =  *list;
	while(atual!=NULL){
		prox = atual->prox;
		while(prox!=NULL){
			if(atual->frequencia > prox->frequencia){
				strcpy(aux, atual->palavra);
				freq = atual->frequencia;
				temp = atual->no;
				
				strcpy(atual->palavra, prox->palavra);
				atual->frequencia = prox->frequencia;
				atual->no = prox->no;
				
				strcpy(prox->palavra, aux);
				prox->frequencia = freq;
				prox->no = temp;
			}
			prox = prox->prox;
		}
		atual = atual->prox;
	}
}

void SortListDesc(TpLista **list){
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
				atual->no = prox->no;
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

Tree *CriaNovaTree(Tree *esquerda, Tree *direita){
	
	Tree *t = (Tree*)malloc(sizeof(Tree));
	t->codigo = -1;
	t->esq = esquerda;
	t->dir = direita;
	
	return t;
}

TpLista *CriaNovaLista(int frequencia, Tree *esquerda, Tree *direita){
	
	TpLista *lista = (TpLista*)malloc(sizeof(TpLista));
	lista->frequencia = frequencia;
	//lista->no = CriaNovaTree(esquerda,direita);
	lista->no = (Tree*)malloc(sizeof(Tree));
	lista->no->esq = esquerda;
	lista->no->codigo = -1;
	lista->no->dir = direita;
	strcpy(lista->palavra,"");
	lista->prox = NULL;
	
	return lista;
}

void Inserir(TpLista **list, TpLista *aux){
	TpLista *pos = *list;
	if(*list == NULL)
		*list = aux;
	else{
		while(pos->prox!=NULL)
			pos = pos->prox;
		pos->prox = aux;
		
	}
	SortList(&(*list));
}

void pre_ordem(Tree *raiz){
    if(raiz!=NULL){
        printf("%d\n", raiz->codigo);
        pre_ordem(raiz->esq);
        pre_ordem(raiz->dir);
    }

}

void criaArvoreHuffman(TpLista **list){
	TpLista *aux, *excluir;

	int soma =0;
	while((*list)->prox!=NULL){// o erro é que esta sendo apagado a cabeça da list no ultimo caso
		soma=0;
		soma = (*list)->frequencia+(*list)->prox->frequencia;
		aux = CriaNovaLista(soma,(*list)->no,(*list)->prox->no);
		//printf("\n\n\n");
		//pre_ordem(aux->no);	
		
		excluir = *list;
		*list=(*list)->prox;
		free(excluir);
		excluir = *list;
		*list=(*list)->prox;
		free(excluir);
		Inserir(&(*list), aux);
			
		//pre_ordem((*list)->no);	
		
	}	
}




void ExibeArvore(Tree *raiz, int *i){
	if(raiz!=NULL){
		*i=(*i)+1;
		ExibeArvore(raiz->dir, &(*i));
		for(int j=0;j<5*(*i);i++)
			printf(" ");
		printf("(%d)\n", raiz->codigo);
		ExibeArvore(raiz->esq, &(*i));
		*i = (*i)-1;
	}
	
}

void exibeHuff(Tree *raiz, int n) {
    if(raiz != NULL)
    {
        exibeHuff(raiz->dir, n + 1);
        for(int i = 0; i < 5*n; i++)
            printf(" ");
        printf("(%d)\n", raiz->codigo);
        exibeHuff(raiz->esq, n + 1);
    }
}

void SetArq(char bin[], int codigo){
	bin[strlen(bin)+1] = '\0';
	FILE *ptr = fopen("Huffman.dat","r+");
	TpHuff aux;
	int flag =0;
	fread(&aux,sizeof(TpHuff),1, ptr);
	while(!feof(ptr) && flag==0){
		if(aux.simbolo == codigo){
			flag =1;
			strcpy(aux.huff, bin);
			fseek(ptr,-sizeof(TpHuff),1);
			fwrite(&aux,sizeof(TpHuff),1,ptr);
		}
		fread(&aux,sizeof(TpHuff),1, ptr);
	}
	fclose(ptr);
}


void SetBin(Tree *raiz, char binary[], int i)
{
	if(!Ehfolha(raiz)){
		binary[i] = '0';
		SetBin(raiz->esq, binary, i+1);
		binary[i] = '1';
		SetBin(raiz->dir, binary,i+1);
	}
	else{
		SetArq(binary, raiz->codigo);	
	}
}


void criarArqBin(TpLista *list){
	
	FILE * ptr = fopen("Tabela.dat", "wb");
	TpHuff huff;
	
	while(list != NULL){
		
		huff.simbolo = list->no->codigo;
		strcpy(huff.palavra, list->palavra);
		strcpy(huff.huff," ");
		
		fwrite(&huff, sizeof(TpHuff), 1, ptr);
		list = list -> prox;
	}
	
	fclose(ptr);
}

void EncodeSentence(char sentence[], Tree *raiz){
	FILE *ptr = fopen("Frase.dat","ab+");
	int i,j;
	i=0;
	char subs[30];
	byte bits;
	
	while(i<strlen(sentence)+1){
		j=0;
		while(sentence[i]!=' ' && sentence[i]!='\0')
			subs[j++] = sentence[i++];
		subs[j] = '\0';
		
		
		
	}
	
	
	
	
}


//só pra ver se ta gravando certo


int main(){
	setlocale(LC_ALL, "Portuguese");
	TpLista *list= NULL;
	char text[10000];
	strcpy(text,"Amar ï¿½ sonhar, sonhar ï¿½ viver, viver ï¿½ curtir, curtir ï¿½ amar. Cada um terï¿½ uma escolha, cada um farï¿½ a escolha, cada um escolhe a sua escolha. Levaremos um tempo para crescer, levaremos um tempo para amadurecer, levaremos um tempo para entender, levaremos um tempo para envelhecer, levaremos um tempo para morrer");
	BuildList(&list,text);
	SortListDesc(&list);
	setNo(list);
	Exibe(list);
	SortList(&list);
	printf("\n\n");
	Exibe(list);
	criaArvoreHuffman(&list);
	exibeHuff(list->no, 0);
	//pre_ordem(list->no);

}
