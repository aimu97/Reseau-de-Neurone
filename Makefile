#  D'apres le Makefile de :
#  	Auteur : Farès BELHADJ
#  	Email  : amsi@ai.univ-paris8.fr
#  	Date   : 29/01/2017

SHELL = /bin/sh
# définition des commandes utilisées
CC = gcc
RM = rm -f
# déclaration des options du compilateur
CFLAGS = -Wall -O3
CPPFLAGS = -I.
LDFLAGS = -g -lm

# définition des fichiers et dossiers
PROGNAME = iris_data
HEADERS =  map.h iris.h 
SOURCES =  main.c parser.c map.c iris_devoir.c
OBJ = $(SOURCES:.c=.o)

all: $(PROGNAME)

$(PROGNAME): $(OBJ)
	$(CC) $(OBJ) $(LDFLAGS) -o $(PROGNAME)

%.o: %.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

clean:
	@$(RM) -r $(PROGNAME) $(OBJ)
