#include <stdbool.h>
#include <stdio.h>

#ifndef TP2_H_INCLUDED
#define TP2_H_INCLUDED
#define TAM 100

typedef struct {
  int date;
  char team1[TAM];
  char team2[TAM];
  int goalsTeam1;
  int goalsTeam2;
  char championship[TAM];
  char city[TAM];
  char country[TAM];
  char neutral[TAM];
} fileInfo;

typedef struct {
  char name[TAM];
  float points;
  float games;
  int wins;
  int draws;
  int defeats;
  int goals;
  int enemyGoals;
  int goalsDifference;
  float pointsBalance; // variável que armazena o aproveitamento. Não achei tradução melhor, desculpe!
} countries;

typedef struct node node;
typedef struct list list;
typedef struct tree tree;
typedef struct confrontation confrontation; //confrontos
typedef struct nodeConfrontations nodeConfrontations;
typedef struct listConfrontations listConfrontations;

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

struct confrontation{
  char teams[TAM];
  int games;
};

struct nodeConfrontations {
  nodeConfrontations *prev;
  nodeConfrontations *next;
  confrontation confrontationsList;
};

struct listConfrontations {
  nodeConfrontations *first;
  nodeConfrontations *last;
  int size;
};

struct tree{
  countries country;
  tree *right;
  tree *left;
};

int countOfLinesFromFile(FILE *data);
void readFile(fileInfo *matches, FILE* data, int fileLines);
void insert_front(node* le, list* mylist);
node* partition( list* input, list* left, list* right );
void qsort_list(list* l);
list initializeList();
listConfrontations initializelistConfrontations();
void calculatePoints(int goals, int enemyGoals, node *p);
void search(list *l, int goals, int enemyGoals, char *name, char *championship);
void searchConfrontations(listConfrontations *lConfrontations, char *name);
void addCountry(list *l, char *name, int goals, int enemyGoals);
void addCountryConfrontations(listConfrontations *l, char *name);
void first(int fileLines, fileInfo *matches, int yearStart, int yearEnd);

#endif
