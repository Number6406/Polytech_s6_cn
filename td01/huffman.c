#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 8

struct noeud{
    char evenement;
    int frequence;
    struct noeud *fg;
    struct noeud *fd;
};

typedef struct noeud Noeud;

struct liste{
	Noeud *elem;
	struct liste *succ;
	struct liste *pred;
};

typedef struct liste Liste;

Liste* tabToList(int tab[]) {
	int i;
	Liste *l = malloc(sizeof(Liste));
	for (i = 0; i < N; i++) {
		Liste *n = malloc(sizeof(Liste));
		n->elem->evenement = (char)i;
		n->elem->frequence = tab[i];
		
	}
	return l;
}

int main(void) {
	
	int event[N] = {0.23,0.09,0.30,0.19,0.08,0.06,0.03,0.02};
	
	
	
	return 0;
}
