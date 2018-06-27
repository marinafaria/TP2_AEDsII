#include <stdio.h>
#include <stdlib.h>
#include "TP2.h"
#include <math.h>
#include <string.h>
#include <stdbool.h>

int main(int argc, char *argv[]){
  int fileLines;
  char dataName[20];
  sprintf(dataName,"%s", argv[1]);
  FILE* data = fopen(dataName, "r");
  fileLines = countOfLinesFromFile(data);
  fileInfo matches[fileLines];
  alocate(matches, fileLines);
  readFile(matches, data, fileLines);
  first(fileLines);
  tree *raiz = NULL;
  fclose(data);
}

//gcc -Wall -std=c99 *.c -lm -o tp2
//./tp2 results.csv

//com debug
//gcc -Wall -std=c99 main.c TP2.c -g -lm -o tp2
//gdb ./tp2 results.csv
//run
//pra sair, quit

//saber se deu free em tudo
//valgrind --leak-check=full --track-origins=yes ./tp2 results.csv
