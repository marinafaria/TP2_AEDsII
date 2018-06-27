#include <stdbool.h>
#include <stdio.h>

#ifndef TP2_H_INCLUDED
#define TP2_H_INCLUDED
#define TAM 100

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
  float pointsBalance;
}countries;

typedef struct node node;
typedef struct list list;
typedef struct tree tree;

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

struct tree{
  countries country;
  tree *right;
  tree *left;
};

int countOfLinesFromFile(FILE *data);
void readFile(fileInfo *matches, FILE* data, int fileLines);
list initializeList();
void search(list *l, fileInfo x);
void addCountry(list *l, char *name, int win, int lose, int draws, int goals, int enemyGoals);
void first(int fileLines, fileInfo *matches);

#endif
