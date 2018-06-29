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
  int method = atoi(argv[2]);
  int yearStart = atoi(argv[3]);
  int yearEnd = atoi(argv[4]);
  FILE* data = fopen(dataName, "r");
  if(data == NULL){
    printf("Um dos arquivos inseridos nao pode ser aberto!");
  }
  fileLines = countOfLinesFromFile(data);
  fileInfo *matches = (fileInfo*)malloc(fileLines * (sizeof(fileInfo)));
  readFile(matches, data, fileLines);
  if(method ==1){
    first(fileLines, matches, yearStart, yearEnd);
  }
  // tree *raiz = NULL;
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
//valgrind --leak-check=full --track-origins=yes ./tp2 results.

//fontes
//https://www.vivaolinux.com.br/script/Ordenacao-QuickSort
