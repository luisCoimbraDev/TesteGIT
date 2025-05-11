
//colocar a union de bits que formam um byte
struct Arvore{
	struct Arvore *esq, *dir;
	int codigo;
	int freq;
};typedef struct Arvore Tree;

struct TpLista{
	struct TpLista *prox;
	struct Tree *no;	
};typedef struct TpLista Lista;

struct TpHuff{ // essa estrutura eu vou usar para buscar no arquivo binario
	char palavra[30];
	int simbolo;
	int freq;
	//union com os codigos de HuffMan
	//sera que pode uma union aqui dentro? ou posso guardar como string?
};


char Ehfolha(Tree *f){
	if(f->esq == NULL && f->dir== NULL)
		return 1;
	return 0;
}

