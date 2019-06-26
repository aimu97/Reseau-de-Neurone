#include "iris.h"

data_t* load_data_file(int lengh, int size_db, const char* file_name){ // taille du vecteur + taille de la base de données 

	FILE *fichier; 
	fichier = fopen(file_name,"r"); 
	data_t *data; 
	data = (data_t *)malloc(sizeof(data_t)*(size_db)); // fois 150
	char *token = NULL;
	char *str, *tok=NULL, *tmp = NULL;
	size_t l; // nbre de charatre utiliser par getline
	ssize_t r;
	int nbre_ligne = 0, nbre_champs = 0;
	double *vect, norm = 0.0f;
	//int i;
	//int j;

	while((r = getline (&str,&l,fichier))!= -1 && nbre_ligne < size_db){
			token = str;
			data[nbre_ligne].v = (double *) malloc(lengh * sizeof(double));
			vect = data[nbre_ligne].v; // pointe sur l'adresse du dernier element ajouter
			nbre_champs = 0;
			norm = 0.0f;
			for (tok = token; nbre_champs <= lengh; tok = NULL)
			{
				token = strtok(tok, ",");
				if (token != NULL && nbre_champs < lengh)
				{
					vect[nbre_champs] = strtod(token, &tmp);
					norm += vect[nbre_champs] * vect[nbre_champs];
					tmp = NULL;
				}
				else
				{
					data[nbre_ligne].norm = sqrt(norm);
					normalisation(data[nbre_ligne].v, lengh, data[nbre_ligne].norm);
					token[strlen(token) - 1] = '\0';
					data[nbre_ligne].nom_espece = strdup(token); // allocation de label
				}
				nbre_champs++;
			}
			nbre_ligne++;	
		}
	return data;
}


void display(data_t *data,int length, int size_db){
	int i; 
	int j;
	for(i = 0; i < size_db; i++){
		printf("%s ",data[i].nom_espece);
		for(j = 0; j < length; j++){
			printf("%f ",data[i].v[j]);
		}
		printf("\n \n");
		}
	}
