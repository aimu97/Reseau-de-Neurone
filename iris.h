#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define BUFF 150

#ifndef IRIS_H_
#define IRIS_H_


struct data{
	double *v; // stock les longeurs et sepales
	char *nom_espece;
	double norm;
};
typedef struct data data_t;

data_t* load_data_file(int lengh, int size_db, const char* file_name);
void normalisation(double *v, int length, double norm);
void display(data_t *data,int length, int size_db);
double * moyenne(data_t *data,int length, int size_db);


#endif