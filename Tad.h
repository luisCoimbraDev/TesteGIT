
struct Arvore{
	struct Arvore *esq, *dir;
	int codigo;
};typedef struct Arvore Tree;

struct TpLista{
	struct TpLista *prox;
	char palavra[30];
	int frequencia;
	Tree *no;	
};typedef struct TpLista Lista;

struct TpHuff{ // essa estrutura eu vou usar para buscar no arquivo binario
	char palavra[30];
	int simbolo;
	unsigned char num;
};


struct Bits{	
	unsigned char b7:1;
	unsigned char b6:1;
	unsigned char b5:1;
	unsigned char b4:1;
	unsigned char b3:1;
	unsigned char b2:1;
	unsigned char b1:1;
	unsigned char b0:1;
};

union byte{
	Bits bits;
	unsigned char num;
};

char Ehfolha(Tree *f){
	if(f->esq == NULL && f->dir== NULL)
		return 1;
	return 0;
}

