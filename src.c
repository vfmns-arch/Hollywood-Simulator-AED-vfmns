#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ACTORS_LENGTH
#define ITEMS_LENGTH
#define FAROESTE 1
#define CRIME 2
#define HEROI 3
#define HORROR 4
#define DRAMA 5


struct actor{
  char name[100];
  const int bonus;
  int salary;
  int fans;
  unsigned char available;
}
typedef struct actor actor;

struct movie{
  char name[50];
  actor actors[3];
  int revenue;
  int budget;
  int marketing;
  movie *next;
  int rating;
  int genre;
}
typedef struct movie movie;



actor deniro;
deniro.name = "Robert DeNiro";
deniro.bonus = CRIME;
deniro.salary = 50000;
deniro.fans = 10000;

actor clint;
clint.name = "Clint Eastwood";
clint.bonus = FAROESTE;
clint.salary = 50000;
clint.fans = 8000;

actor marlon;
marlon.name = "Marlon Brando";
marlon.bonus = CRIME;
marlon.salary = 20000;
marlon.fans = 10000;

actor jack;
jack.name = "Jack Nicholson";
jack.bonus = HORROR;
jack.salary = 20000;
jack.fans = 8000;

actor bogart;
bogart.name = "Humphrey Bogart";
bogart.bonus = DRAMA;
bogart.salary = 20000;
bogart.fans = 5000;

actor pacino;
pacino.name = "Al Pacino";
pacino.bonus = CRIME;
pacino.salary = 30000;
pacino.fans = 10000;

actor adam;
adam.name = "Adam Driver";
adam.bonus = DRAMA;
adam.salary = 10000;
adam.fans = 10000;


int year = 2026;
char option[50];
int n;
movie *head = malloc(sizeof(movie));


struct studio{
  char name[50];
  int money;
}
typedef struct studio studio;

struct item{
  char name[20];
  const int price;
  const int bonus;
  unsigned int sold;
  unsigned int available;
}
typedef struct item item;

studio yourstudio;
item *items = malloc(ITEMS_LENGTH * sizeof(item));
actor *actors = malloc(ACTORS_LENGTH * sizeof(actors));

movie *organize(movie *head, movie *newmovie){
  if(head == NULL || head->revenue < newmovie->revenue){
    newmovie->next = head;
    return newmovie;
  }
  movie *aux = head;
  while(aux->next != NULL && newmovie->revenue < aux->next->revenue){
    aux = aux->next;
  }
  newmovie->next = aux->next;
  aux->next = newmovie;
  return head;
}

int calculate_revenue(movie *newmovie){
  int r = newmovie->marketing / 10;
  newmovie->rating = newmovie->budget;

  
  for(int i = 0; i < ITEMS_LENGTH; i++){
    if(items[i].sold){
      newmovie->rating *= items[i].bonus;
    }
  }

  for(int i = 0; i < 3; i++){
    if(newmovie->actors[i].bonus == newmovie->genre){
      newmovie->rating *= 10;
    }
  }
  
  for(int i = 0; i < 3; i++){
    int a = r * newmovie->rating / 100;
    r += newmovie->actors[i].fans;
    newmovie->actors[i].fans += a;
    newmovie->actors[i].salary += a * 5;
    newmovie->actors[i].available = 1;
  }

  return r * 20;
}


movie make_movie(){
  movie newmovie;
  newmovie.next = head;
  printf("\nNome do filme: ");
  scanf("%s", option);
  strcpy(newmovie.name, option);
  while(1){
    printf("\nfaroeste\ncrime\nheroi\nhorror\ndrama\nGenero: ");
    scanf("%s", option);
    if(!strcmp(option, "faroeste")){
      newmovie.genre = FAROESTE;
      break;
    } else if(!strcmp(option, "crime")){
      newmovie.genre = CRIME;
      break;
    } else if(!strcmp(option, "heroi")){
      newmovie.genre = HEROI;
      break;
    } else if(!strcmp(option, "horror")){
      newmovie.genre = HORROR;
      break;
    } else if(!strcmp(option, "drama")){
      newmovie.genre = DRAMA;
      break;
    } else {
      printf("Invalido");
    }
  }
  
  printf("\nOrçamento: ");
  scanf("%d", &n);
  yourstudio.money -= n;
  newmovie.budget = n;
  printf("\nOrçamento de marketing: ");
  scanf("%d", &n);
  yourstudio.money -= n;
  newmovie.marketing = n;


  
  for(int i = 1; i < 4; i++){
    n = 0;
    printf("\nEscolha o ator numero %d: ", i);
    for(int j = 0; j < ACTORS_LENGTH; j++){
      if(actors[j].available){
        printf("%s\n", actors[j].name);
      }
    }
    scanf("%s", option);
    for(int j = 0; j < ACTORS_LENGTH; j++){
      if(!strcmp(option, actors[j].name) && actors[j].available){
        n = 1;
        newmovie.actors[i] = actors[j];
        actors[j].available = 0;
        break;
      }
    }
    if(!n){
      printf("Nome invalido\n");
      i--;
    }
  }


  newmovie.revenue = calculate_revenue(&newmovie);
  printf("your movie generated %d dollars in revenue\n", newmovie.revenue);
  yourstudio.money += newmovie.revenue;

  return newmovie;
}

void save_game(){
  FILE *fptr = fopen("save.txt", "w");
  fprintf(fptr, "%s\n", yourstudio.name);
  fprintf(fptr, "%d\n", yourstudio.money);
  for(int i = 0; i < ACTORS_LENGTH; i++){
    fprintf(fptr, "%s\n", actors[i].name);
    fprintf(fptr, "%d\n", actors[i].bonus);
    fprintf(fptr, "%d\n", actors[i].fans);
    fprintf(fptr, "%u\n", actors[i].available);
  }
  for(int i = 0; i < ITEMS_LENGTH; i++){
    fprintf(fptr, "%s\n", items[i].name);
    fprintf(fptr, "%d\n", items[i].price);
    fprintf(fptr, "%d\n", items[i].bonus);
    fprintf(fptr, "%u\n", items[i].sold);
    fprintf(fptr, "%u\n", items[i].available);
  }
  movie *aux = head;
  while(aux != NULL){
    fprintf(fptr, "%s\n", aux->name);
    for(int i = 0; i < 3; i++){
      fprintf(fptr, "%s\n", aux->actors[i].name);
    }
    fprintf(fptr, "%d\n", aux->revenue);
    fprintf(fptr, "%d\n", aux->budget);
    fprintf(fptr, "%d\n", aux->marketing);
    fprintf(fptr, "%d\n", aux->rating);
    fprintf(fptr, "%d\n", aux->genre);
  }
  fclose(fptr);
  return;
}

void load_game(){
  FILE *fptr = fopen("save.txt", "r");
  if(fptr == NULL){
    printf("No save file found");
    return;
  }
  char st[100];
  fgets(yourstudio.name, 50, fptr);
  fscanf(fptr, "%d", yourstudio.money);

  for(int i = 0; i < ACTORS_LENGTH; i++){
    fgets(actors[i].name, 100, fptr);
    fscanf(fptr, "%d", actors[i].bonus);
    fscanf(fptr, "%d", actors[i].fans);
    fscanf(fptr, "%u", actors[i].available);
  }
  for(int i = 0; i < ITEMS_LENGTH; i++){
    fgets(items[i].name, 20, fptr);
    fscanf(fptr, "%d", items[i].price);
    fscanf(fptr, "%d", items[i].bonus);
    fscanf(fptr, "%u", items[i].sold);
    fscanf(fptr, "%u", items[i].available);
  }
  
  movie *aux = head;
  while(fgets(aux->name, 50, fptr) != NULL){
    for(int i = 0; i < 3; i++){
      char st[100];
      fgets(st, 100, fptr);
      for(int j = 0; j < ACTORS_LENGTH; j++){
        if(!strcmp(actors[j].name, st)){
          aux->actors[i] = actors[j];
          break;
        }
      }
    }
    fscanf(fptr, "%d", aux->revenue);
    fscanf(fptr, "%d", aux->budget);
    fscanf(fptr, "%d", aux->marketing);
    fscanf(fptr, "%d", aux->rating);
    fscanf(fptr, "%d", aux->genre);
    
  }
  fclose(fptr);
}

int main(){
  printf("New Game\nLoad\n");
  while(1){
    scanf("%s", option);
    if(!strcmp(option, "New Game"){
      printf("Escolha o nome de seu estudio\n", n);
      scanf("%s", option);
      strcpy(studio.name, option);
      loadnew();
      break;
    } else if(!strcmp(option, "Load"){
      loadgame();
      break;
    } else {
      printf("Comando invalido.\n");
    }
  }
  free(actors);
  free(items);
  while(head != NULL){
    movie *aux = head;
    head = head->next;
    free(aux);
  }
  return 0;
}
