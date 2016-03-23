#include <stdlib.h>
#include <stdio.h>
#include <math.h>

/** 
typedef struct Liste Liste;
struct Liste {

Non utilisé : extenssion possible
struct Liste * pSucc;

};
typedef Liste *pListe;
*/

double log2( double n ) {   
    return log( n ) / log( 2 );  
}

double termeEntropie(double terme) {
	return terme * log2(1/terme);
}

int main(int argc, char **argv)
{
	FILE* proba_file = NULL;
	char filename[20] = {0};
    printf("Nom du fichier ? ");
    scanf("%s", filename);
    
	proba_file = fopen(filename, "r+");
	
	double entropie = 0.0;
	double valC;
	double sommeProba = 0.0;
	
	if (proba_file != NULL) {
        // On peut lire et écrire dans le fichier
	
		
		while(fscanf(proba_file ,"%lf",&valC) != EOF) {
			sommeProba = sommeProba + valC;
			if ( sommeProba > 1.0 ) {
				fprintf(stderr,"Somme des probabilités non correcte.\n");
				return 1;
			}
			entropie = entropie + termeEntropie(valC);
		}
		
		fclose(proba_file);
    } else {
        fprintf(stderr,"Impossible d'ouvrir le fichier\n");
		return 1;
    }
    
    if ( sommeProba < 1.0 ) {
		fprintf(stderr,"Somme des probabilités non correcte.\n");
		return 1;
	}
    
    printf("Résultat de l'entropie des valeurs : %f", entropie);
    
	return 0;
}
