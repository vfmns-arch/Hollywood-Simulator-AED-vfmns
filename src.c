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

struct actor{
  char name[100];
  int bonus;
  long salary;
  long fans;
  unsigned char available;
};
typedef struct actor actor;

typedef struct {
    char key[100];
    actor *actor;
    int occupied;
} HashEntry;

struct movie{
  char name[50];
  actor *actors[3];
  long revenue;
  long budget;
  long marketing;
  struct movie *next;
  long rating;
  int genre;
};
typedef struct movie movie;

struct studio{
  char name[50];
  long money;
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
char option[50];

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
            return hashTable[index].actor;
        }

        index = (index + 1) % TABLE_SIZE;

        if (index == start) {
            break;
        }
    }

    return NULL;
}

movie *organize(movie *newmovie){
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


long calculate_revenue(movie *newmovie){
    long r = newmovie->marketing / 10;
    newmovie->rating = newmovie->budget / 10;

    for(int i = 0; i < ITEMS_LENGTH; i++){
        if(items[i].sold){
            newmovie->rating *= items[i].bonus;
        }
    }
    for(int i = 0; i < 3; i++){
        if(newmovie->actors[i]->bonus == newmovie->genre){
            newmovie->rating *= 2;
        }
    }

    for(int i = 0; i < 3; i++){
      long a = r;
      if(newmovie->rating < 10000){
        a /= 10000;
      }
      a *= r;
      a /= 20;
      r += newmovie->actors[i]->fans;
      newmovie->actors[i]->fans += a;
      if(strcmp(newmovie->actors[i]->name, "Ronald Reagan") != 0){
        newmovie->actors[i]->salary += a;
      }
      newmovie->actors[i]->available = 1;
    }
    printf("\n");
    printf("========================================\n");
    printf("             ESTREIA DO FILME           \n");
    printf("========================================\n");

    printf("\n  Audiencia: %ld espectadores\n", r);
    printf("  Receita:   $%ld\n", newmovie->revenue);
    printf("========================================\n");
    return r * 20;
}

void clearBuffer(){
    int c;
    while((c = getchar()) != '\n' && c != EOF);
}

void make_movie(){
  movie *newmovie = malloc(sizeof(movie));
  newmovie->next = NULL;
  printf("\n");
  printf("========================================\n");
  printf("             NOVO FILME                 \n");
  printf("========================================\n");

  printf("\n  Nome do filme: ");
  fgets(option, sizeof(option), stdin);
  option[strcspn(option, "\n")] = 0;
  strcpy(newmovie->name, option);
  while(1){
    printf("\n----------------------------------------\n");
    printf("              GENEROS                   \n");
    printf("----------------------------------------\n");
    printf("  Faroeste\n");
    printf("  Crime\n");
    printf("  Heroi\n");
    printf("  Horror\n");
    printf("  Drama\n");
    printf("----------------------------------------\n");
    printf("  Genero: ");
    fgets(option, sizeof(option), stdin);
    option[strcspn(option, "\n")] = 0;
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
      printf("Genero Invalido");
    }
  }
  while(1){
    printf("\nOrçamento do filme: ");
    long o;
    if(scanf("%ld", &o) != 1 || o > yourstudio->money || o < 0){
      clearBuffer();
      printf("Dinheiro invalido ou insuficiente\n");
    } else {
      clearBuffer();
      yourstudio->money -= o;
      newmovie->budget = o;
      break;
    }
  }
  while(1){
    printf("\nOrçamento de marketing: ");
    long o;
    if(scanf("%ld", &o) != 1 || o > yourstudio->money || o < 0){
      clearBuffer();
      printf("Dinheiro invalido ou insuficiente\n");
    } else {
      clearBuffer();
      yourstudio->money -= o;
      newmovie->marketing = o;
      break;
    }
  }
  
  for(int i = 0; i < 3; i++){
    n = 0;
    printf("\n");
    printf("========================================\n");
    printf("              ELENCO                    \n");
    printf("========================================\n");

    printf("\n  Escolha o ator numero %d:\n\n", i + 1);

    for(int j = 0; j < ACTORS_LENGTH; j++){
        if(actors[j].available){
            printf("  %-25s | Salario: $%ld\n",
                   actors[j].name, actors[j].salary);
        }
    }

    printf("----------------------------------------\n");
    printf("  Nome do ator: ");
    fgets(option, sizeof(option), stdin);
    option[strcspn(option, "\n")] = 0;
    actor *aaa = searchActor(option);
    printf("Ator escolhido: %s\n", option);
    if(aaa == NULL || aaa->available == 0){
      printf("\nNome Invalido\n");
      i--;
    }else if(aaa->salary > yourstudio->money){
      printf("Dinheiro insuficiente para contratar o ator\n");
      i--;
    } else {
      printf("\nAtor escolhido!\n");
      yourstudio->money -= aaa->salary;
      newmovie->actors[i] = aaa;
      newmovie->actors[i]->available = 0;
    }
  }
  newmovie->revenue = calculate_revenue(newmovie);
  if(newmovie->revenue > 1000000000){
    printf("Ronald Reagan desbloqueado\n");
    actors[7].available = 1;
  }
  yourstudio->money += newmovie->revenue;
  head = organize(newmovie);
  return;
}

int save_game(char *f){
  FILE *fptr = fopen(f, "w");
  if(fptr == NULL){
    return 1;
  }
  fprintf(fptr, "%s\n", yourstudio->name);
  fprintf(fptr, "%ld\n", yourstudio->money);
  for(int i = 0; i < ACTORS_LENGTH; i++){
    fprintf(fptr, "%s\n", actors[i].name);
    fprintf(fptr, "%ld\n", actors[i].salary);
    fprintf(fptr, "%d\n", actors[i].bonus);
    fprintf(fptr, "%ld\n", actors[i].fans);
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
    fprintf(fptr, "%ld\n", aux->revenue);
    fprintf(fptr, "%ld\n", aux->budget);
    fprintf(fptr, "%ld\n", aux->marketing);
    fprintf(fptr, "%ld\n", aux->rating);
    fprintf(fptr, "%d\n", aux->genre);
    aux = aux->next;
  }
  fclose(fptr);
  return 0;
}

int load_game(char *f){
  FILE *fptr = fopen(f, "r");
  if(fptr == NULL){
    return 1;
  }
  char st[100];
  fgets(yourstudio->name, 50, fptr);
  fscanf(fptr, "%ld", &yourstudio->money);
  fgetc(fptr);

  for(int i = 0; i < ACTORS_LENGTH; i++){
    fgets(actors[i].name, 100, fptr);
    fscanf(fptr, "%ld", &actors[i].salary);
    fscanf(fptr, "%d", &actors[i].bonus);
    fscanf(fptr, "%ld", &actors[i].fans);
    fscanf(fptr, "%u", &actors[i].available);
    fgetc(fptr);
    insertActor(&actors[i]);
  }
  for(int i = 0; i < ITEMS_LENGTH; i++){
    fgets(items[i].name, 20, fptr);
    fscanf(fptr, "%d", &items[i].price);
    fscanf(fptr, "%d", &items[i].bonus);
    fscanf(fptr, "%u", &items[i].sold);
    fscanf(fptr, "%u", &items[i].available);
    fgetc(fptr);
  }


  movie *aux;
  unsigned char co = 0;
  while(fgets(st, 50, fptr) != NULL){
    aux = malloc(sizeof(movie));
    strcpy(aux->name, st);
    printf("Nome do filme: %s\n", aux->name);
    if(!co){
      head = aux;
      co = 1;
    }
    for(int i = 0; i < 3; i++){
      char st[100];
      fgets(st, 100, fptr);
      aux->actors[i] = searchActor(st);
    }
    fscanf(fptr, "%ld", &aux->revenue);
    fscanf(fptr, "%ld", &aux->budget);
    fscanf(fptr, "%ld", &aux->marketing);
    fscanf(fptr, "%ld", &aux->rating);
    fscanf(fptr, "%d", &aux->genre);
    aux->next = NULL;
    aux = aux->next;
    fgetc(fptr);
  }
  fclose(fptr);
  return 0;
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
  items[1].bonus = 5;
  items[1].sold = 0;
  items[1].available = 1;

  strcpy(items[2].name, "Efeitos especiais");
  items[2].price = 1000000;
  items[2].bonus = 5;
  items[2].sold = 0;
  items[2].available = 1;
  return;
}

int main(){
  head = NULL;
  yourstudio = malloc(sizeof(studio));
  items = malloc(ITEMS_LENGTH * sizeof(item));
  actors = malloc(ACTORS_LENGTH * sizeof(actor));
  printf("Opcoes:\nNew Game\nLoad\n");
  while(1){
    fgets(option, sizeof(option), stdin);
    option[strcspn(option, "\n")] = 0;
    if(!strcmp(option, "new game")){
      printf("\n");
      printf("========================================\n");
      printf("          BEM-VINDO A HOLLYWOOD          \n");
      printf("========================================\n");
      printf("\n");
      printf("  Um novo estudio esta prestes a nascer!\n");
      printf("\n");
      printf("  Escolha o nome do seu estudio: ");
      fgets(yourstudio->name, sizeof(yourstudio->name), stdin);
      yourstudio->name[strcspn(yourstudio->name, "\n")] = 0;
      new_game();
      break;
    } else if(!strcmp(option, "Load")){
      printf("Digite o nome do save\n");
      fgets(option, sizeof(option), stdin);
      option[strcspn(option, "\n")] = 0;
      if(!load_game(option)){
        break;
      }
      printf("Nao foi possivel achar o save\n");
    } else {
      printf("Comando invalido.\n");
    }
  }
  while(1){
    printf("\n");
    printf("========================================\n");
    printf("          HOLLYWOOD STUDIOS             \n");
    printf("========================================\n");
    printf("             MENU PRINCIPAL             \n");
    printf("----------------------------------------\n");
    printf("  Loja\n");
    printf("  Novo Filme\n");
    printf("  Status\n");
    printf("  Save\n");
    printf("  Exit\n");
    printf("----------------------------------------\n");
    printf("  Escolha uma opcao: ");
    fgets(option, sizeof(option), stdin);
    option[strcspn(option, "\n")] = 0;
    if(!strcmp(option, "loja")){
      while(1){
        printf("Opcoes:\nExit\n");
        for(int i = 0; i < ITEMS_LENGTH; i++){
          if(items[i].available && !items[i].sold){
            printf("%s, %d dolares\n", items[i].name, items[i].price);
          }
        }
        fgets(option, sizeof(option), stdin);
        option[strcspn(option, "\n")] = 0;
        if(!strcmp(option, "exit")){
          printf("Saindo da Loja...\n\n");
          break;
        }
        for(int i = 0; i < ITEMS_LENGTH; i++){
          if(!strcmp(option, items[i].name) && items[i].price <= yourstudio->money && items[i].available && !items[i].sold){
            yourstudio->money -= items[i].price;
            items[i].sold = 1;
            items[i].available = 0;
            break;
          }
          if(i == ITEMS_LENGTH - 1){
            printf("Comando Invalido\n\n");
          }
        }
      }    
    } else if(!strcmp(option, "novo filme")){
      make_movie();
    } else if(!strcmp(option, "status")){
      printf("\n");
      printf("========================================\n");
      printf("             STUDIO STATUS              \n");
      printf("========================================\n");

      printf("\n  Estudio: %s\n", yourstudio->name);
      printf("  Saldo:   $%ld\n", yourstudio->money);

      printf("\n----------------------------------------\n");
      printf("                ATORES                  \n");
      printf("----------------------------------------\n");

      for(int i = 0; i < ACTORS_LENGTH; i++){
          if(actors[i].available){
              printf("  %-25s | $%ld\n",
                     actors[i].name, actors[i].salary);
          }
      }
      printf("Items Comprados:\n\n");
      for(int i = 0; i < ITEMS_LENGTH; i++){
        if(items[i].sold){
          printf("%s\n\n", items[i].name);
        }
      }
      printf("Filmes produzidos:\n\n");
      movie *aux = head;
      while(aux != NULL){
        printf("\nNome: %s\n", aux->name);
        printf("Genero: ");
        if(aux->genre == FAROESTE){
          printf("Faroeste\n");
        } else if(aux->genre == CRIME){
          printf("Crime\n");
        } else if(aux->genre == HEROI){
          printf("Heroi\n");
        } else if(aux->genre == HORROR){
          printf("Horror\n");
        } else if(aux->genre == DRAMA){
          printf("Drama\n");
        }
        printf("Orçamento: %ld\n", aux->budget);
        printf("Orçamento de marketing: %ld\n", aux->marketing);
        printf("Atores:\n");
        for(int i = 0; i < 3; i++){
          printf("%s salario: %ld\n", aux->actors[i]->name, aux->actors[i]->salary);
        }
        printf("Receita: %ld\n\n", aux->revenue);
        aux = aux->next;
      }
    } else if(!strcmp(option, "save")){
      printf("Digite o nome do arquivo de save\n");
      fgets(option, sizeof(option), stdin);
      option[strcspn(option, "\n")] = 0;
      if(save_game(option)){
        printf("Nao foi possivel salvar o jogo\n");
      }
    } else if(!strcmp(option, "exit")){
      break;
    } else {
      printf("Comando Invalido\n");
    }
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
