#include "map.h"
#include "iris.h"
#define couleur(param) printf("\033[%sm",param)


double randomm(double min,double max){
	double r = 0.0;
	r = (double)rand()/(double)RAND_MAX *(max - min) + min;
	return r;
}


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

int* genere_tab(int size_db){
	int *tab = malloc(sizeof(int)*size_db);
	for(int i = 0; i < size_db;i++){
		tab[i] = i;
	}
	return tab;
}

double distance_euclidienne(double *vect1,double *vect2, int dimention){
	int i;
	double distance = 0.0; 
	for (i = 0; i < dimention;i++){
		distance += (vect1[i] - vect2[i])*(vect1[i] - vect2[i]);
	}

	distance = sqrt(distance);

	return distance;
}


map_t *init_map(int height,int width, int length, double *v_moy, double min, double max){

	map_t *map = (map_t*)malloc(sizeof(map_t));
	map -> capteur = NULL;
	map -> height = height;
	map -> width = width;
	map -> map = malloc(height * sizeof(neuron_t*));

	int i;
	int j;
	int k;

	for(i = 0; i < height; i++){
		map -> map[i] = malloc(width * sizeof(neuron_t));

		for(j = 0; j < width; j++){
			map -> map[i][j].weight = malloc(sizeof(double) * length);
			for (k = 0; k < length; k++){
				map -> map[i][j].weight[k] = randomm(v_moy[k] - min,v_moy[k] + max);

			}
		}
	}


	return map;

}


void apprentissage(map_t *map,data_t *data,int size_db, double alpha, int rayon_voisin, int nb_iteration,int dimention){
	int *tab = genere_tab(size_db);
	int ligne = 0;
	int colone = 0;
	double alpha_init = alpha;
	int decrement = (int) nb_iteration / rayon_voisin;
	decrement = (decrement <= 0) ? 1 : decrement; // eviter que decrement vaut 0 decrementer le rayon
	for(int i = 1; i <= nb_iteration; i++){
		shuffle(tab,size_db);
		alpha = alpha_init * (1.0 - ((double) i / (double) nb_iteration));
		rayon_voisin -= (i % decrement == 0 && rayon_voisin > 1) ? 1 : 0;
		for(int j = 0; j < size_db;j++){
			double min_dist = 1000.0;
			for(int h = 0; h < map ->height; h++){
				for(int w = 0; w < map -> width; w++){
					double distance = distance_euclidienne(map->map[h][w].weight,data[tab[j]].v,dimention);
					if(distance < min_dist){
						ligne = h;
						colone = w;
						min_dist = distance;
					}
				}
			}
			int begin_ligne =(ligne - rayon_voisin < 0) ? 0: ligne - rayon_voisin;
			int end_ligne = (ligne + rayon_voisin < map->height)? ligne + rayon_voisin: map->height - 1;

			int begin_colone =(colone - rayon_voisin < 0)? 0: colone - rayon_voisin;
			int end_colone = (colone + rayon_voisin < map->width)? colone + rayon_voisin: map->width - 1;

			for(int l = begin_ligne; l <= end_ligne; l++){
				for(int c = begin_colone; c <= end_colone; c++){
					for(int k = 0; k < dimention; k++){

					map->map[l][c].weight[k] += alpha * (data[tab[j]].v[k] - map->map[l][c].weight[k]);
				}
				}
			}
		}
	}
}

void etiquetage(map_t *map,data_t *data,int size_db,int dimention){

	for(int h = 0; h < map->height; h++){
		for(int w = 0; w < map->width; w++){
			double min_dist = 1000.0;
			int indice_min = 0;
			for(int i = 0; i < size_db; i++){
				double distance = distance_euclidienne(map->map[h][w].weight,data[i].v,dimention);
				if(distance < min_dist){
					indice_min = i;
					min_dist = distance;
				}

			}
			map->map[h][w].label = data[indice_min].nom_espece;

			if(strcmp (map->map[h][w].label, "Iris-setosa") == 0){
				couleur("31");
				printf("S");
				couleur("0");
			}

			if(strcmp(map->map[h][w].label,"Iris-versicolor") == 0){
				couleur("33");
				printf("V");
				couleur("0");
			}

			if(strcmp (map->map[h][w].label,"Iris-virginica") == 0){
				couleur("35");
				printf("A");
				couleur("0");
			}

		} 
		printf("\n");
	}
}
