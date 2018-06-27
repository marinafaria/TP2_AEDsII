#include <stdbool.h>
#include <stdio.h>

#ifndef TP2_H_INCLUDED
#define TP2_H_INCLUDED
#define TAM 50

typedef struct{
int date;
char team1[TAM];
char team2[TAM];
int goalsTeam1;
int goalsTeam2;
char championship[TAM];
char city[TAM];
char country[TAM];
char neutral[TAM];
}fileInfo;

typedef struct{
  char name[TAM];
  float points;
  float games;
  int wins;
  int draws;
  int defeats;
  int goals;
  int enemyGoals;
  float aproveitamento;
}countries;

typedef struct node node;
typedef struct list list;

struct node {
    node *prev;
    node *next;
    countries country;
};

struct list {
    node *first;
    node *last;
    int size;
};

typedef struct tree{
  countries country;
  tree *right;
  tree *left;
}tree;

int countOfLinesFromFile(FILE *data);
void alocate(fileInfo *matches, int fileLines);
void readFile(fileInfo *matches, FILE* data, int fileLines);
void first(int fileLines);

#endif
