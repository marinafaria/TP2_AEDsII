#include <stdio.h>
#include <stdlib.h>
#include "TP2.h"
#include <stdbool.h>
#include <string.h>

int countOfLinesFromFile(FILE *data){
  int ch, number_of_lines = 0;
  while(!feof(data)){
      ch = fgetc(data);
      if(ch == '\n')
          number_of_lines++;
  }
      return (number_of_lines - 1);
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

void insert_front(node* le, list* mylist)
{
    if(mylist->first == NULL){
        le->next = mylist-> first;
        mylist->first=le;
        mylist->last=le;

    }
    else {
        le->next = mylist-> first;
        mylist->first= le;

    }

    // printf("%s %d \n",le->passwort, &le->haufigkeit);

}

node* partition( list* input, list* left, list* right ){
    node* pivot= input->first;
    node *i;
    for(i=input->first; i != NULL; i=i->next){

        if ((i -> country.points) < (pivot -> country.points)){
            insert_front( i, left);
        }
        else{
            insert_front( i, right);
        }

    }

    return pivot;
}

void qsort_list(list* l){
    list right;
    list left;
    right.first=NULL;
    right.last=NULL;
    left.first=NULL;
    left.last=NULL;
    node*pivot;
    if (l->last != l->first){
        pivot = partition(l, &left, &right );

        qsort_list(&left);
        qsort_list(&right);
        if(left.first == NULL) {
                  // Special

                  left.first = pivot;
                  l->first = left.first;
              } else {
                  // REGULAR
                  l->first = left.first;
                  left.last->next = pivot;
              }
              if(right.first == NULL) {
                  // Special
                  pivot->next = right.first;
                  l->last = pivot;
              } else {
                  // Regular
                  pivot->next = right.first;
                  l->last = right.last;
              }
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

void calculatePoints(int goals, int enemyGoals, node *p){
  p->country.games += 1;
  p->country.goals += goals;
  p->country.enemyGoals += enemyGoals;
  if(goals > enemyGoals){
    p->country.wins += 1;
    p->country.points += 3;
  }
  if(goals < enemyGoals){
    p->country.defeats += 1;
  }
  if(goals == enemyGoals){
    p->country.draws += 1;
    p->country.points += 1;
  }

}

//pontos, número de jogos, vitórias, empates, derrotas, gols marcados,
//gols sofridos, saldo de gols e aproveitamento (este último com duas casas decimais)

void search(list *l, fileInfo x){
  node *p;
  int win, lose, draws;
  char name[100];
  //printf("%s\n", x.team1);
  p = (node*)malloc(sizeof(node));
  p = l->first;
  while(p != NULL){
    //printf("%s %s\n", p->country.name, x.team1);
      if(strcmp(p->country.name,x.team1) == 0){
        calculatePoints(x.goalsTeam1, x.goalsTeam2, p);
        break;
      }else{
        //printf("%s\n", p->country.name);
        p = p->next;
      }
  }
  if(p == NULL) {
    strcpy(name, x.team1);
    //printf("eu adicionei %s na lista\n", x.team1);
    if(x.goalsTeam1 > x.goalsTeam2){
      win = 1;
      lose = 0;
      draws = 0;
    }
    if(x.goalsTeam1 < x.goalsTeam2){
      win = 0;
      lose = 1;
      draws = 0;
    }
    if(x.goalsTeam1 == x.goalsTeam2){
      win = 0;
      lose = 0;
      draws = 0;
    }
    addCountry(l, name, win, lose, draws, x.goalsTeam1, x.goalsTeam2);
  }
}

void addCountry(list *l, char *name, int win, int lose, int draws, int goals, int enemyGoals){
  node *n;
  n = (node*)malloc(sizeof(node));
  n->next = NULL;
  n->prev = l->last;
  l->last->next = n;
  l->last = n;
  l->size++;
  n->country.games = 1;
  strcpy(n->country.name, name);
  n->country.wins = win;
  n->country.defeats = lose;
  n->country.draws = draws;
  calculatePoints(goals, enemyGoals, n);
  //printf("%s\n", n->country.name);
}

// void freeList(list *l){
//   node *aux;
//   aux = l->first;
//   while(aux != NULL){
//     aux = l->first;
//     if(aux == NULL)
//       break;
//     l->first = aux->next;
//     free(aux);
//     }
//   printf("to no libera\n");
// }


void first(int fileLines, fileInfo *matches){
  list l = initializeList(); // criar cabeça da lista encadeada
  for(int k=0; k<fileLines -1 ; k++){
            //printf("%d\n", k);
      search(&l, matches[k]);
    // fazer função pra calcular pontos
  }
  //qsort_list(&l);
  node *p;
  p = (node*)malloc(sizeof(node));
  p = l.first;
  while(p != NULL){
    printf("%s %.2f %.2f %d %d %d %d %d\n", p->country.name, p->country.points, p->country.games, p->country.wins, p->country.draws, p->country.defeats, p->country.goals, p->country.enemyGoals);
    p = p->next;
  }
}

void second(){
// fazer um for pegando todos os nomes dos países, se já existir, show, se não, coloca a função de inserir na árvore
// strcmp comparado escócia, líbia dá -1, porque escócia tá antes da líbia, aí retorna a função recursiva pra
// ir percorrendo a esquerda ou direita da árvore até achar o seu lugar

}
