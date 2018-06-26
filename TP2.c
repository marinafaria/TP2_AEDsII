#include <stdio.h>
#include <stdlib.h>
#include "TP2.h"
#include <stdbool.h>

int countOfLinesFromFile(FILE *data){
  int ch, number_of_lines = 0;
  while(!feof(data)){
      ch = fgetc(data);
      if(ch == '\n')
          number_of_lines++;
  }
      return (number_of_lines - 1);
}

void alocate(fileInfo *matches, int fileLines){
      matches = (fileInfo*)malloc(fileLines * (sizeof(fileInfo)));
}

void readFile(fileInfo *matches, FILE* data, int fileLines){
  rewind(data);
  int i = 0;
  char temporary[100];
  fscanf(data,"%s", temporary);
  i = 0;
  while(i < fileLines){
    fscanf(data,"%d,%50[^,], %50[^,], %d, %d, %50[^,], %50[^,], %50[^,], %50[^\n]", &matches[i].date, matches[i].team1,
    matches[i].team2,&matches[i].goalsTeam1,&matches[i].goalsTeam2,
    matches[i].championship, matches[i].city, matches[i].country, matches[i].neutral);
    i++;
  }
}

list initializeList(){
  list l;
  node *n;
  n = (node*)malloc(sizeof(node));
  l.first = n;
  l.last = n;
  l.size = 0;
  l.first->next = NULL;
  l.last->next = NULL;
  n->prev = NULL;
  return l;
}

void addRight(list *l, int valor){
  node *n;
  n = (node*)malloc(sizeof(node));
  n->country.wins = valor;
  n->next = NULL;
  n->prev = l->last;
  l->last->next = n;
  l->last = n;
  l->size++;
}

void addLeft(list *l, int valor, node *aux){
  if (l->first->next == NULL){
    addRight(l, valor);
  }else{
  node *n;
  n =(node*)malloc(sizeof(no));
  n->next = aux;
  n->prev = aux->prev;
  n->prev->prox = n;
  aux->prev = n;
  n->digito = valor;
  l->tamanho++;
  }
}

  void freeList(lista *l){
    no *aux;
    aux = l->primeiro;
    while(aux != NULL){
      aux = l->primeiro;
      if(aux == NULL)
      break;
      l->primeiro = aux->prox;
      free(aux);
      }
      printf("to no libera\n");
  }


void first(){

}

void second(){
// fazer um for pegando todos os nomes dos países, se já existir, show, se não, coloca a função de inserir na árvore
// strcmp comparado escócia, líbia dá -1, porque escócia tá antes da líbia, aí retorna a função recursiva pra
// ir percorrendo a esquerda ou direita da árvore até achar o seu lugar

}
