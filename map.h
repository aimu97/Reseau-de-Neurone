#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "iris.h"
#ifndef MAP_H_
#define _MAP_H_
typedef struct  neuron
{
	double *weight; // vecteur de la memoire dun neruone 
	char* label;
	
} neuron_t;

typedef struct map{
	double *capteur;
	int height;
	int width;
	int dim;
	neuron_t **map;	
}map_t;

void apprentissage(map_t *map,data_t *data,int size_db, double alpha, int rayon_voisin, int nb_iteration,int dimention);
map_t *init_map(int height,int width, int length, double *v_moy, double min, double max);
double distance_euclidienne(double *vect1,double *vect2, int dimention);
int* genere_tab(int size_db);
double randomm(double min,double max);
void etiquetage(map_t *map,data_t *data,int size_db,int dimention);

#endif
