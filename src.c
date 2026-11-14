#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 16
#define ACTORS_LENGTH 8
#define ITEMS_LENGTH 3
#define FAROESTE 1
#define CRIME 2
#define HEROI 3
#define HORROR 4
#define DRAMA 5

typedef struct {
    char key[100];
    actor *actor;
    int occupied;
} HashEntry;

struct actor{
  char name[100];
  int bonus;
  int salary;
  int fans;
  unsigned char available;
};
typedef struct actor actor;

struct movie{
  char name[50];
  actor *actors[3];
  int revenue;
  int budget;
  int marketing;
  movie *next;
  int rating;
  int genre;
};
typedef struct movie movie;

struct studio{
  char name[50];
  int money;
};
typedef struct studio studio;

struct item{
  char name[20];
  int price;
  int bonus;
  unsigned int sold;
  unsigned int available;
};
typedef struct item item;


char option[50];
int n;
movie *head;
studio *yourstudio;
item *items;
actor *actors;
HashEntry hashTable[TABLE_SIZE];

unsigned int hashFunction(char *name) {
    unsigned long hash = 5381;
    int c;

    while ((c = *name++)) {
        hash = hash * 33 + c;
    }

    return hash % TABLE_SIZE;
}

void insertActor(actor *actor) {
    unsigned int index = hashFunction(actor->name);

    while (hashTable[index].occupied) {
        index = (index + 1) % TABLE_SIZE;
    }

    strcpy(hashTable[index].key, actor->name);
    hashTable[index].actor = actor;
    hashTable[index].occupied = 1;
    return;
}

actor *searchActor(char *name) {
    unsigned int index = hashFunction(name);
    unsigned int start = index;

    while (hashTable[index].occupied) {

        if (strcmp(hashTable[index].key, name) == 0) {
            return &hashTable[index].actor;
        }

        index = (index + 1) % TABLE_SIZE;

        if (index == start) {
            break;
        }
    }

    return NULL;
}

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
    if(newmovie->actors[i]->bonus == newmovie->genre){
      newmovie->rating *= 10;
    }
  }
  
  for(int i = 0; i < 3; i++){
    int a = r * newmovie->rating / 100;
    r += newmovie->actors[i]->fans;
    if(i != 7){
      newmovie->actors[i]->fans += a;
      newmovie->actors[i]->salary += a * 5;
    }
    newmovie->actors[i]->available = 1;
  }

  return r * 20;
}


movie *make_movie(){
  movie *newmovie = malloc(sizeof(movie));;
  newmovie->next = NULL;
  printf("\nNome do filme: ");
  scanf("%s", option);
  strcpy(newmovie->name, option);
  while(1){
    printf("\nfaroeste\ncrime\nheroi\nhorror\ndrama\nGenero: ");
    scanf("%s", option);
    if(!strcmp(option, "faroeste")){
      newmovie->genre = FAROESTE;
      break;
    } else if(!strcmp(option, "crime")){
      newmovie->genre = CRIME;
      break;
    } else if(!strcmp(option, "heroi")){
      newmovie->genre = HEROI;
      break;
    } else if(!strcmp(option, "horror")){
      newmovie->genre = HORROR;
      break;
    } else if(!strcmp(option, "drama")){
      newmovie->genre = DRAMA;
      break;
    } else {
      printf("Invalido");
    }
  }
  
  printf("\nOrçamento: ");
  scanf("%d", &n);
  yourstudio->money -= n;
  newmovie->budget = n;
  printf("\nOrçamento de marketing: ");
  scanf("%d", &n);
  yourstudio->money -= n;
  newmovie->marketing = n;


  
  for(int i = 1; i < 4; i++){
    n = 0;
    printf("\nEscolha o ator numero %d: ", i);
    for(int j = 0; j < ACTORS_LENGTH; j++){
      if(actors[j].available){
        printf("%s\n", actors[j].name);
      }
    }
    scanf("%s", option);
    actor *aaa = searchActor(option);
    if(aaa == NULL){
      printf("Nome Invalido");
      i--;
    } else {
      newmovie->actors[i] = aaa;
    }
  }
  newmovie->revenue = calculate_revenue(&newmovie);
  if(newmovie->revenue > 1000000000){
    actors[7].available = 1;
  }
  printf("your movie generated %d dollars in revenue\n", newmovie->revenue);
  yourstudio->money += newmovie->revenue;
  head = organize(head, newmovie);
  return newmovie;
}

int save_game(char *f){
  FILE *fptr = fopen(f, "w");
  if(fptr == NULL){
    return 1;
  }
  fprintf(fptr, "%s\n", yourstudio->name);
  fprintf(fptr, "%d\n", yourstudio->money);
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
      fprintf(fptr, "%s\n", aux->actors[i]->name);
    }
    fprintf(fptr, "%d\n", aux->revenue);
    fprintf(fptr, "%d\n", aux->budget);
    fprintf(fptr, "%d\n", aux->marketing);
    fprintf(fptr, "%d\n", aux->rating);
    fprintf(fptr, "%d\n", aux->genre);
  }
  fclose(fptr);
  return 0;
}

void load_game(char *f){
  FILE *fptr = fopen(f, "r");
  if(fptr == NULL){
    printf("No save file found");
    return;
  }
  char st[100];
  fgets(yourstudio->name, 50, fptr);
  fscanf(fptr, "%d", yourstudio->money);

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


  movie *aux;
  unsigned char co = 0;
  while(fgets(aux->name, 50, fptr) != NULL){
    aux = malloc(sizeof(movie));
    if(!co){
      head = aux;
      co = 1;
    }
    for(int i = 0; i < 3; i++){
      char st[100];
      fgets(st, 100, fptr);
      aux->actors[i] = searchActor(st);
    }
    fscanf(fptr, "%d", aux->revenue);
    fscanf(fptr, "%d", aux->budget);
    fscanf(fptr, "%d", aux->marketing);
    fscanf(fptr, "%d", aux->rating);
    fscanf(fptr, "%d", aux->genre);
    aux->next = NULL;
    aux = aux->next;
  }
  fclose(fptr);
  return;
}

void new_game(){
  yourstudio->money = 100000;
  strcpy(actors[0].name, "Robert DeNiro");
  actors[0].bonus = CRIME;
  actors[0].salary = 50000;
  actors[0].fans = 10000;
  actors[0].available = 1;
  insertActor(&actors[0]);


  strcpy(actors[1].name, "Clint Eastwood");
  actors[1].bonus = FAROESTE;
  actors[1].salary = 50000;
  actors[1].fans = 8000;
  actors[1].available = 1;
  insertActor(&actors[1]);


  strcpy(actors[2].name, "Marlon Brando");
  actors[2].bonus = CRIME;
  actors[2].salary = 20000;
  actors[2].fans = 10000;
  actors[2].available = 1;
  insertActor(&actors[2]);


  strcpy(actors[3].name, "Jack Nicholson");
  actors[3].bonus = HORROR;
  actors[3].salary = 20000;
  actors[3].fans = 8000;
  actors[3].available = 1;
  insertActor(&actors[3]);

  strcpy(actors[4].name, "Humphrey Bogart");
  actors[4].bonus = DRAMA;
  actors[4].salary = 20000;
  actors[4].fans = 5000;
  actors[4].available = 1;
  insertActor(&actors[4]);
  strcpy(actors[5].name, "Al Pacino");
  actors[5].bonus = CRIME;
  actors[5].salary = 30000;
  actors[5].fans = 10000;
  actors[5].available = 1;
  insertActor(&actors[5]);
  strcpy(actors[6].name, "Adam Driver");
  actors[6].bonus = DRAMA;
  actors[6].salary = 10000;
  actors[6].fans = 10000;
  actors[6].available = 1;
  insertActor(&actors[6]);
  strcpy(actors[7].name, "Ronald Reagan");
  actors[7].bonus = FAROESTE;
  actors[7]. salary = 0;
  actors[7].fans = 1000000;
  actors[7].available = 0;
  insertActor(&actors[7]);
  strcpy(items[0].name, "Microfones");
  items[0].price = 100000;
  items[0].bonus = 2;
  items[0].sold = 0;
  items[0].available = 1;

  strcpy(items[1].name, "Camera colorida");
  items[1].price = 1000000;
  items[1].bonus = 10;
  items[1].sold = 0;
  items[1].available = 1;

  strcpy(items[2].name, "Efeitos especiais");
  items[2].price = 1000000;
  items[2].bonus = 10;
  items[2].sold = 0;
  items[2].available = 1;
  return;
}

int main(){
  head = NULL;
  yourstudio = malloc(sizeof(studio));
  items = malloc(ITEMS_LENGTH * sizeof(item));
  actors = malloc(ACTORS_LENGTH * sizeof(actors));
  printf("New Game\nLoad\n");
  while(1){
    scanf("%s", option);
    if(!strcmp(option, "New Game")){
      printf("Escolha o nome de seu estudio\n", n);
      scanf("%s", option);
      strcpy(yourstudio->name, option);
      new_game();
      break;
    } else if(!strcmp(option, "Load")){
      printf("Digite o nome do save\n");
      scanf("%s", option);
      if(!load_game(option)){
        break;
      }
      printf("Nao foi possivel achar o save\n");
    } else {
      printf("Comando invalido.\n");
    }
  }
  while(1){
    printf("Que deseja fazer?\nLoja\nNovo filme\nstatus\n");
  }
  free(actors);
  free(items);
  free(yourstudio);
  while(head != NULL){
    movie *aux = head;
    head = head->next;
    free(aux);
  }
  return 0;
}
