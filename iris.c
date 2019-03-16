#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define BUFF 150

struct data{
	double longueur_sepale; 
	double largeur_sepale; 
	double longueur_petale;
	double largeur_petale;
	char *nom_espece;
	double norme;
};
typedef struct data data_t;


void shuffle (int *tab, int nbre_ligne){
	int tmp;
	int i;
	int j;

	for(i = (nbre_ligne - 1); i > 1 ; i--){ 
		j = rand()%i;
		tmp = tab[j];
		tab[j] = tab[i];
		tab[i] = tmp;		
	}
}
int main(void){

	FILE *fichier; 
	fichier = fopen("iris.data","r"); 
	data_t *data; 
	data = (data_t *)malloc(sizeof(data_t)*1); 
	int size = BUFF;
	char *token = NULL;
	char str[size];
	int nbre_ligne = 0;
	double *vect;
	int i;
	int j;
	double acc = 0.0;
	double moyenne[4] = {0};
	int n = 78; 
	double *t;
	int *tab;
	t = malloc(sizeof(double)* 4 * n);


	while(!feof(fichier)){
		if(fgets(str,size ,fichier)){
			if(strcmp(str,"\n")== 0){
				continue;
			}
			token = strtok(str, ",");
			nbre_ligne +=1;
			data = realloc(data, sizeof(data_t)*nbre_ligne);
			vect = &data[nbre_ligne - 1].longueur_sepale; // pointe sur l'adresse du dernier element ajouter
			while(token != NULL){
				for(i = 0; i < 4; i++){
					vect[i] = strtod(token, NULL);
					printf(" %f\n", vect[i]);
					token = strtok(NULL, ",");
				}
				data[nbre_ligne - 1].nom_espece = strdup(token);
				printf(" %s\n", data->nom_espece);
				token = strtok(NULL, ",");
			}

			
			for(i = 0; i < 4; i++){
				acc+= vect[i] * vect[i];
			}
			data[nbre_ligne - 1].norme = sqrt(acc);
			

			for(i = 0; i < 4; i++){

				vect[i] = vect[i]/data[nbre_ligne - 1].norme;

			}

			
		}
		
	}

	for(i = 0; i < nbre_ligne; i++){

		moyenne[0] += data[i].longueur_sepale;
		moyenne[1] += data[i].largeur_petale;
		moyenne[2] += data[i].longueur_petale;
		moyenne[3] += data[i].largeur_petale;

	}

	moyenne[0] /= nbre_ligne;
	moyenne[1] /= nbre_ligne;
	moyenne[2] /= nbre_ligne;
	moyenne[3] /= nbre_ligne;

	for(i = 0; i < n; i++){
		for( j = 0; j < 4; j++){

			t[j + 4 * i] = (double)rand()/(double)RAND_MAX * 0.07 - 0.02 + moyenne[j];
		}
	}

	tab = malloc(sizeof(int) * nbre_ligne);
	for(i = 0; i < nbre_ligne; i++){
		tab[i] = i;
	}

	
	shuffle(tab,nbre_ligne);
	

	fclose(fichier);
	return 0;
}





