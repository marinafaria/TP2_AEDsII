#include <stdio.h>
#include <stdlib.h>
#include "TP2.h"
#include <stdbool.h>
#include <string.h>

int countOfLinesFromFile(FILE *data) {
  int ch, number_of_lines = 0;
  while(!feof(data)) {
    ch = fgetc(data);
    if(ch == '\n')
      number_of_lines++;
  }
  return (number_of_lines);
}

void readFile(fileInfo *matches, FILE* data, int fileLines) {
  rewind(data);
  int i = 0;
  char temporary[100];
  fscanf(data,"%s", temporary);
  i = 0;
  while(i < fileLines) {
    fscanf(data,"%d, %50[^,], %50[^,], %d, %d, %50[^,], %50[^,], %50[^,], %50[^\n]", &matches[i].date, matches[i].team1,
    matches[i].team2,&matches[i].goalsTeam1,&matches[i].goalsTeam2,
    matches[i].championship, matches[i].city, matches[i].country, matches[i].neutral);
    i++;
  }
}

int tieBreaker(countries country1, countries country2, char *type) {
  if (strcmp(type, "ranking") == 0) {
    if(country1.points < country2.points)
      return -1;
    else if(country1.points > country2.points)
      return 1;
    else {
      if(country1.pointsBalance < country2.pointsBalance)
        return -1;
      else if(country1.pointsBalance > country2.pointsBalance)
        return 1;
      else {
        if(country1.goalsDifference < country2.goalsDifference)
          return -1;
        else if(country1.goalsDifference > country2.goalsDifference)
          return 1;
        else {
          if(country1.goals < country2.goals)
            return -1;
          else if(country1.goals > country2.goals)
            return 1;
          else {
            if(strcmp(country1.name, country2.name) > 0)
              return -1;
            else if(strcmp(country1.name, country2.name) < 0)
              return 1;
          }
        }
      }
      return 0;
    }
  }
  if (strcmp(type, "confrontations") ==0) {
    if(country1.games < country2.games)
      return -1;
    else if(country1.games > country2.games)
      return 1;
  }
  return 0;
}

void quicksort(countries *a, int left, int right, char *type) {
  int i, j;
  countries y;
  countries x;
  i = left;
  j = right;
  x = a[(left + right) / 2];

  while(i <= j) {
    while (tieBreaker(x, a[i], type) < 0)
      i++;
    while (tieBreaker(x, a[j], type) > 0)
      j--;
    if(i <= j) {
      y = a[i];
      a[i] = a[j];
      a[j] = y;
      i++;
      j--;
    }
  }

  if(j > left)
    quicksort(a, left, j, type);
  if(i < right)
    quicksort(a, i, right, type);
}


list initializeList() {
  list l;
  node *n;
  n = (node*)malloc(sizeof(node));
  l.first = n;
  l.last = n;
  l.size = 0;
  l.first->next = NULL;
  l.last->next = NULL;
  return l;
}

listConfrontations initializelistConfrontations() {
  listConfrontations l;
  nodeConfrontations *n;
  n = (nodeConfrontations*)malloc(sizeof(nodeConfrontations));
  l.first = n;
  l.last = n;
  l.size = 0;
  l.first->next = NULL;
  l.last->next = NULL;
  return l;
}

void calculatePoints(int goals, int enemyGoals, node *p) {
  p->country.games += 1;
  p->country.goals += goals;
  p->country.enemyGoals += enemyGoals;
  if(goals > enemyGoals) {
    p->country.wins += 1;
    p->country.points += 3;
  }
  if(goals < enemyGoals)
    p->country.defeats += 1;
  if(goals == enemyGoals) {
    p->country.draws += 1;
    p->country.points += 1;
  }
}

void addCountry(list *l, char *name, int goals, int enemyGoals) {
  node *n;
  n = (node*)malloc(sizeof(node));
  n->next = NULL;
  l->last->next = n;
  l->last = n;
  l->size++;
  strcpy(n->country.name, name);
  calculatePoints(goals, enemyGoals, n);
}

void addCountryConfrontations(listConfrontations *l, char *name) {
  nodeConfrontations *n;
  n = (nodeConfrontations*)malloc(sizeof(nodeConfrontations));
  n->next = NULL;
  l->last->next = n;
  l->last = n;
  l->size++;
  n->confrontationsList. games = 1;
  strcpy(n->confrontationsList.teams, name);
}

void search(list *l, int goals, int enemyGoals, char *name, char *championship) {
  node *p;
  if(strcmp(championship, "FIFA World Cup") == 0) {
    p = (node*)malloc(sizeof(node));
    p = l->first->next;
    while(p != NULL) {
      if(strcmp(p->country.name, name) == 0) {
        calculatePoints(goals, enemyGoals, p);
        break;
      }
      else {
        p = p->next;
      }
    }
    if(p == NULL) {
      addCountry(l, name, goals, enemyGoals);
    }
  }
}


void searchConfrontations(listConfrontations *lConfrontations, char *name){
  nodeConfrontations *p;
    p = (nodeConfrontations*)malloc(sizeof(nodeConfrontations));
    p = lConfrontations->first;
    while(p != NULL) {
      if(strcmp(p->confrontationsList.teams, name) == 0) {
        p->confrontationsList.games += 1;
        break;
      }
      else {
        p = p->next;
      }
    }
    if(p == NULL) {
      addCountryConfrontations(lConfrontations, name);
    }
}

void freeList(list *l){
  node *aux;
  aux = l->first;
  while(aux != NULL){
    aux = l->first;
    if(aux == NULL)
      break;
    l->first = aux->next;
    free(aux);
    }
  printf("to no libera\n");
}


void first(int fileLines, fileInfo *matches, int yearStart, int yearEnd) {
  list l = initializeList(); // criar cabeça da lista encadeada
  char type [20];
  for(int k = 0; k < fileLines - 1; k++) {
    if(matches[k].date > yearStart*10000 && matches[k].date < yearEnd*10000) {
      search(&l, matches[k].goalsTeam1, matches[k].goalsTeam2, matches[k].team1, matches[k].championship);
      search(&l, matches[k].goalsTeam2, matches[k].goalsTeam1, matches[k].team2, matches[k].championship);
    }
  }
  countries *vector = (countries*)malloc(l.size * (sizeof(countries)));
  node *p;
  p = (node*)malloc(sizeof(node));
  p = l.first->next;
  int i = 0;
  while(p != NULL) {
    vector[i].pointsBalance = (100 * p->country.points)/(3 * p->country.games);
    vector[i].goalsDifference = (p->country.goals - p->country.enemyGoals);
    vector[i].goals = p->country.goals;
    strcpy(vector[i].name, p->country.name);
    vector[i].points = p->country.points;
    vector[i].games = p->country.games;
    vector[i].wins = p->country.wins;
    vector[i].draws = p->country.draws;
    vector[i].defeats = p->country.defeats;
    vector[i].enemyGoals = p->country.enemyGoals;
    p = p->next;
    i++;
  }
  strcpy(type, "ranking");
  quicksort(vector, 0, l.size -1, type);
  for(int q = 0; q < l.size; q++) {
    //printf("%s %.2f %.2f %d %d %d %d %d %d %.2f\n", vector[q].name, vector[q].points, vector[q].games, vector[q].wins, vector[q].draws,
    //vector[q].defeats, vector[q].goals, vector[q].enemyGoals, vector[q].goalsDifference, vector[q].pointsBalance);
  }

//confrontos
  listConfrontations lConfrontations = initializelistConfrontations();
  countries *vectorConfrontations = (countries*)malloc(l.size * (sizeof(countries)));
  char aux[100];
  for(int k = 0; k < fileLines - 1 ;k++) {
    if(matches[k].date > yearStart*10000 && matches[k].date < yearEnd*10000) {
      if(strcmp(matches[k].team1,matches[k].team2) > 0) {
        strcpy(aux,matches[k].team1);
        strcpy(matches[k].team1, matches[k].team2);
        strcpy(matches[k].team2, aux);
      }
        strcat(matches[k].team1, ",");
        strcat(matches[k].team1, matches[k].team2);
      searchConfrontations(&lConfrontations, matches[k].team1);
    }
  }
  nodeConfrontations *pconfrontations;
  pconfrontations = (nodeConfrontations*)malloc(sizeof(nodeConfrontations));
  pconfrontations = lConfrontations.first->next;
  int m = 0;
  while(pconfrontations != NULL) {
    strcpy(vectorConfrontations[m].name, pconfrontations->confrontationsList.teams);
    vectorConfrontations[m].games = pconfrontations->confrontationsList.games;
    pconfrontations = pconfrontations->next;
    m++;
  }
  strcpy(type, "confrontations");
  quicksort(vectorConfrontations, 0, lConfrontations.size - 1, type);
  for(int q = 0; q < lConfrontations.size; q++){
    printf("%s %.0f\n", vectorConfrontations[q].name, vectorConfrontations[q].games);
  }
}

void second() {
// fazer um for pegando todos os nomes dos países, se já existir, show, se não, coloca a função de inserir na árvore
// strcmp comparado escócia, líbia dá -1, porque escócia tá antes da líbia, aí retorna a função recursiva pra
// ir percorrendo a esquerda ou direita da árvore até achar o seu lugar

}

void Inicializa(TipoDicionario T){
  int i;
  for (i = 0; i < M; i++) {
    strcpy(T[i].Chave, Vazio);
  }
}

Apontador Pesquisa(TipoChave Ch, TipoPesos p, TipoDicionario T){
  unsigned int i = 0;
  unsigned int Inicial;
  Inicial = h(Ch, p);
  while((strcmmp(T[(Inicial + i) % M].Chave, Vazio) != 0) && strcmp(T[(Inicial + i) % M].Chave, Ch) != 0) && (i < M))
    i++;
  if(strcmp(T[(Inicial + i) % M].Chave, Vazio) ! = 0) && (strcmp(T[(Inicial + i) % M].Chave, Ch) != 0) && (i < M)
    return((Inicial + i) % M);
  else
    return M;
}

Apontador Pesquisa(TipoChave Ch, TipoPesos p, TipoDicionario T){
  unsigned int i = 0;
  unsigned int Inicial;
  Inicial = h(Ch, p);
  while((strcmp(T[(Inicial + i) % M].Chave, Vazio) ! = 0) && strcmp(T[(Inicial + i) % M].Chave), Ch != 0) && (i < M)
    i++;
  if(strcmp(T[(Inicial + i) % M].Chave, CH == 0))
    return ((Inicial + i) % M);
  else
    return M;
  }

void Retira(char Ch, TipoPesos p, TipoDicionario T)‫‏‬{
  Indice i;
  i = Pesquisa(Ch, p, T);
  if (i < M)
    strcpy(T[i].Chave, Retirado);
  else
    printf("Registro nao esta presente\n");
  }

void Insere(TipoItem x, TipoPesos p, TipoDicionario T)‫‏‬ {
  unsigned int i = 0;
  unsigned int Inicial;
  if (Pesquisa(x.Chave, p, T) < M) {
    printf("Elemento ja esta presente\n");
  return;
  }

  Inicial = h(x.Chave, p);
  while ((strcmp(T[(Inicial + i) % M].Chave, Vazio) != 0) &&
  (strcmp(T[(Inicial + i) % M].Chave, Retirado) != 0) &&
  (i < M))
  i++;
  if (i < M){
    strcpy (T[(Inicial + i) % M].Chave, x.Chave);
  }
  else printf(“Tabela cheian");
}
