#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define PROF_ARBRE_MAX 6

float evt[PROF_ARBRE_MAX];
float evtTrie[PROF_ARBRE_MAX];

struct _Noeud{
	float info;
	struct _Noeud *FilsG;
	struct _Noeud *FilsD;
	char nom[PROF_ARBRE_MAX];
	char code[PROF_ARBRE_MAX];
};
typedef struct _Noeud arbre;

arbre listeSousArbre[PROF_ARBRE_MAX];
/**
 * Source : openclassrooms.com
 **/
void afficherTab(float tab[], int taille)
{
	int i;
	printf("affichage : ");
	for(i=0;i<taille;i++)
	{
		printf("%f ",tab[i]);
	}
	printf("\n");
}
void tri_insertion(float tab[], int taille)
{
   int i, j;
   for (i = 1; i < taille; ++i) {
       float elem = tab[i];
       for (j = i; j > 0 && tab[j-1] > elem; j--)
           tab[j] = tab[j-1];
       tab[j] = elem;
   }
   afficherTab(tab, taille);
}

float sommeArbre(float tab[], int Taille)
{
	int i;
	float res=0;
	for(i=0;i<Taille;i++)
	{
		res=res+tab[i];
		printf("Somme : %f\n",res);
	}
	printf("Somme : %f\n",res);
	return res;
}

arbre *recherche(float p){
	int i=0;
	for(i=0;i<PROF_ARBRE_MAX;i++)
	{
		if(listeSousArbre[i].info==p) 
		{
			printf("info : %f trouve\n",p);
			return &listeSousArbre[i];
		}
	}
	printf("info : %f pas trouve\n",p);
	return NULL;
}

int trouverEvt (float e)
{
	int i;
	for(i=0; i<PROF_ARBRE_MAX; i++)
	{
		if(evt[i]==e) return i;
	}
	printf("Ne devrait pas arriver");
	return -1;
}

char ze[1] = "0";
//declaration inutile pour separer les deux chaines de caracteres(sinon il lit les deux au lieu de lire que ze
int separation = 5843;
char un[1] = "1";
void afficherRes(arbre * a,char code[]){
	if(a!=NULL)
	{
		if ((a->FilsG ==NULL)&&(a->FilsD==NULL))
		{
			int evnt = trouverEvt(a->info);
			printf("code e%d : %s\n",evnt+1,code);
		}
		//~ printf("Info de A : %f",a->info);
		else{
			char codeGauche[strlen(code)];
			strcpy(codeGauche, code);
			strcat(codeGauche, ze);
			//printf("Code gauche : %s\n",codeGauche);
			afficherRes(a->FilsG, codeGauche);
			
			char codeDroit[strlen(code)];
			strcpy(codeDroit, code);
			strcat(codeDroit, un);
			//printf("Code droit : %s\n",codeDroit);
			afficherRes(a->FilsD, codeDroit);
		}
	}
}

void aff(arbre *a, char vide[]){
	if(a != NULL) {
		char newvide[strlen(vide)];
		strcpy(newvide,vide);
		strcat(newvide,".....");
		if(a->FilsD != NULL) aff(a->FilsD, newvide); 
		printf("%s %f",vide,a->info); printf("<\n");
		if(a->FilsG != NULL) aff(a->FilsG, newvide);
	}
}

int main(int argc, char **argv)
{
	
	int i,b;
	do{
		for (i=0;i<PROF_ARBRE_MAX;i++)
		{
			float tmp;
			printf("Probabilite de l'evenement %d : ",i+1);
			scanf("%f",&tmp);
			evt[i]=tmp;
			evtTrie[i]=tmp;
		}
		if (abs(sommeArbre(evt,PROF_ARBRE_MAX) - 1.0) < 0.00001)
		{
			b=0;
		}else{
			b=1;
			printf("La somme des proba est differente de 1 !\n");
		}
	}while(b);
	
	tri_insertion(evtTrie, PROF_ARBRE_MAX);
	//~ for (i=0;i<PROF_ARBRE_MAX;i++)
	//~ {
		//~ printf("T[%d] = %f ",i+1,evtTrie[i]);
	//~ }
	
	i=0;
	int j=0;
	arbre * a;
	arbre * fd;
    arbre * fg;
	while(evtTrie[i]<1.0)
	{
		fg = recherche(evtTrie[i]);
		if (fg==NULL)
		{
			fg = malloc(sizeof(arbre));
			fg->info = evtTrie[i];
			fg->FilsD = NULL;
			fg->FilsG = NULL;
			fg->code[i] = '0';
		}
		
		fd = recherche(evtTrie[i+1]);
		if (fd==NULL)
		{
			fd = malloc(sizeof(arbre));
			fd->info = evtTrie[i+1];
			fd->FilsD = NULL;
			fd->FilsG = NULL;
			fd->code[i] = '1';
		}
		
		listeSousArbre[j].info = fg->info + fd->info;
		listeSousArbre[j].FilsD = fd;
		listeSousArbre[j].FilsG = fg;
		j++;
		
		//Trouver une solution pour lier l'arbre cree avec une donnee exterieur...
		
		evtTrie[i] = 2;
		evtTrie[i+1] = fg->info + fd->info;
		
		tri_insertion(evtTrie, PROF_ARBRE_MAX);
		
		fg=NULL;
		fd=NULL;
	}
	//le noeud j-1 est la racine de l'arbre
	afficherRes(&listeSousArbre[j-1],"");

    aff(&listeSousArbre[j-1],"");
	
	
	return 0;
}

