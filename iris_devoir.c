#include "iris.h"


void normalisation(double *v, int length, double norm){
	int i;
	for(i = 0; i < length; i++){
		v[i] /= norm;
	}
}

double * moyenne(data_t *data,int length, int size_db){
	double *moy = calloc (length, sizeof * moy); // reintialiser tt a zero 
	int i, j;
	for (i = 0; i < size_db; ++i){ // parcours les donner 
		for (j = 0; j < length; ++j){ // parcours le vecteur 
			moy[j] += data[i].v[j];
		}


		for (j = 0; j < length; ++j){
			moy[j] /= size_db;
		}

		
	}
	return moy;
}