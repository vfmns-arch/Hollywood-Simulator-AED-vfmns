#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FAROESTE 1
#define CRIME 2
#define HEROI 3
#define HORROR 4
#define DRAMA 5



struct actor{
  char name[100];
  const int bonus;
  int salary;
  int fame;
}
typedef struct actor actor;

struct movie{
  char name[50];
  actor *actors;
  int revenue;
}
typedef struct movie movie;



actor deniro;
deniro.name = "Robert DeNiro";
deniro.bonus = CRIME;
deniro.salary = 50000;
deniro.fame = 1;

actor clint;
clint.name = "Clint Eastwood";
clint.bonus = FAROESTE;
clint.salary = 50000;
clint.fame = 1;

actor marlon;
marlon.name = "Marlon Brando";
marlon.bonus = CRIME;
marlon.salary = 20000;
marlon.fame = 1;

actor jack;
jack.name = "Jack Nicholson";
jack.bonus = HORROR;
jack.salary = 20000;
jack.fame = 1;

actor bogart;
bogart.name = "Humphrey Bogart";
bogart.bonus = DRAMA;
bogart.salary = 20000;
bogart.fame = 1;

actor pacino;
pacino.name = "Al Pacino";
pacino.bonus = CRIME;
pacino.salary = 30000;
pacino.fame = 1;

actor adam;
adam.name = "Adam Driver";
adam.bonus = DRAMA;
adam.salary = 10000;
adam.fame = 1;



int main(){
  char option[9];
  printf("New Game\nLoad\n");
  while(1){
    scanf("%s", option);
    if(!strcmp(option, "New Game"){
      char n[30];
      printf("Escolha o nome de seu estudio\n", n);
      scanf("%s", n);
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
