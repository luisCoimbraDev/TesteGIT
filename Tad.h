struct Arvore{
	struct Arvore *esq, *dir;
	int codigo;
	int freq;
};typedef struct Arvore Tree;

struct TpLista{
	struct TpLista *prox;
	struct Tree *no;	
};typedef struct TpLista Lista;


char Ehfolha(Tree *f){
	if(f->esq == NULL && f->dir== NULL)
		return 1;
	return 0;
}

