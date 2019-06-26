#include "map.h"
#include "iris.h"
#include <time.h>
int main(int argc, char** argv){
	//argv1 nom du fichier
	// argv2 dimention du vecteur de donnée
	//argv3 taille de la base de donnée 
	double * moy;
	srand(time(NULL));
	int dim = atoi(argv[2]), size = atoi(argv[3]);
	data_t *data = load_data_file(dim, size, argv[1]);
	//display(data, dim, size);
	map_t *map = NULL;
	double alpha = 0.7;
	double alpha2 = 0.07;
	int rayon_voisin = 3;
	int rayon_voisin2 = 1;
	int nb_iteration = 500;
	int nb_iteration2 = 2000;
	moy = moyenne(data, dim, size);
	int w = 22;
	int h = 12;
	map = init_map(h, w, dim, moy, 0.001, 0.001);
	apprentissage(map,data,size,alpha,rayon_voisin,nb_iteration,dim);
	apprentissage(map,data,size,alpha2,rayon_voisin2,nb_iteration2,dim);
	
	etiquetage(map,data,size,dim);

	return 0;
}
