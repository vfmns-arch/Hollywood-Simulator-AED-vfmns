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
  actor *actors;
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

actor actors[ACTORS_LENGTH];

int year = 2026;
char option[50];
int n;
movie *head = NULL;


struct studio{
  char name[50];
  int money;
}
typedef struct studio studio;

struct item{
  char name[20];
  int price;
  int bonus;
  int sold;
  int available;
}
typedef struct item item;

item items[ITEMS_LENGTH];

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
  return 0;
}
