//Sammi Mak
//5931464
//sm15zj

#include <iostream>
#include <cstdlib>
#include <pthread.h>
#include <signal.h>
#include <unistd.h>
#include <ctime>
#include <time.h>
// #include "players.h"
// #include "kobold.h"

//CTRL C is to terminate Process
//kill -s SIGUSR1 PID is to print the maze
//kill -s SIGUSR2 PID is to create a n

#define ROWS 20
#define COLS 80
#define MAGENTA "\033[35m"
#define RESET   "\033[0m"
pthread_mutex_t lock;
Player::Player farvin = '1';
Player::Player garvin = '2';
Player::Player tharvin = '3';
Player::Player sally = '4';
Kobold::Kobold kobbie = 'K';
Player::Player gold = 'G';
static const int NUMTHREADS=4;
char maze [ROWS][COLS] = {0};
int rand(int a);
volatile int occupied;
bool find_run;
bool run = true;

//Pass multiple arguements into thread
struct threadargs{
  char **maze;
  Player::Player *aPlayer;
  Kobold::Kobold *aKobold;
};

//Signals
void ctrl_c(int sig) {
  std::cout << "Ending Process" << std::endl;
  run=false;
  std::cout << std::endl;
}

//Dealer's choice: Add new object to map
void addCurse(int h, int w){
  maze[h][w] = 'C';
}

//Places all players & gold on map
void placeEveryone(char(& maze)[ROWS][COLS], Player::Player &a, Player::Player &b, Player::Player &c, Player::Player &d, Player::Player &g){
  kobbie.placeKobold(maze, rand(19), rand(79));
  a.placePlayer(maze, rand(19), rand(79));
  b.placePlayer(maze, rand(19), rand(79));
  c.placePlayer(maze, rand(19), rand(79));
  d.placePlayer(maze, rand(19), rand(79));
  g.placePlayer(maze, rand(19), rand(79));
}

//Call to create a new maze with players placed
void createMaze() {
    srand (time(NULL));
    for(int i=0; i<ROWS; i++){
      for(int j=0; j<COLS; j++){
        //if border then have an X
        if((i == 0 || i == ROWS-1)){
          maze[i][j] = 'X';
        }
        else if(j == 0 || j == COLS-1){
          maze[i][j] = 'X';
        }
        else {
          int chance = rand(5);
          switch (chance) {
            //This allows more floor space via an ugly method
            case 1:
            case 2:
            case 3:
            case 4:
            maze[i][j] = ' ';
            break;
            case 5:
            maze[i][j] = 'X';
            break;
          }
        }
      }
    }
    placeEveryone(maze, farvin, garvin, tharvin, sally, gold);
    addCurse(rand(18),rand(78));
}

//Used to display and print maze with players & objects loaded
void printMaze(char(& maze)[ROWS][COLS]){
  for(int i=0; i<ROWS; i++){
    for(int j=0; j<COLS; j++){
        if(maze[i][j]!='X'){
          std::cout<<MAGENTA<<maze[i][j] << RESET;
        }
        else{
        std::cout << maze[i][j];
        }
      }
      std::cout<<std::endl;
    }
  }

//Print maze via signal
void USR1(int sig){
  std::cout<<"Current state of maze:"<<std::endl;
  printMaze(maze);
  std::cout<<"Player scores: "<<farvin.icon<<": "<<farvin.score<<" HP: "<<farvin.HP<<std::endl;
  std::cout<<"Player scores: "<<garvin.icon<<": "<<garvin.score<<" HP: "<<garvin.HP<<std::endl;
  std::cout<<"Player scores: "<<tharvin.icon<<": "<<tharvin.score<<" HP: "<<tharvin.HP<<std::endl;
  std::cout<<"Player scores: "<<sally.icon<<": "<<sally.score<<" HP: "<<sally.HP<<std::endl;
  std::cout<<"PID: "<<getpid()<<std::endl;
}

//Create new maze via signal
void USR2(int sig){
  std::cout<<"Creating new maze:"<<std::endl;
  createMaze();
  printMaze(maze);
  std::cout<<"Player scores: "<<farvin.icon<<": "<<farvin.score<<" HP: "<<farvin.HP<<std::endl;
  std::cout<<"Player scores: "<<garvin.icon<<": "<<garvin.score<<" HP: "<<garvin.HP<<std::endl;
  std::cout<<"Player scores: "<<tharvin.icon<<": "<<tharvin.score<<" HP: "<<tharvin.HP<<std::endl;
  std::cout<<"Player scores: "<<sally.icon<<": "<<sally.score<<" HP: "<<sally.HP<<std::endl;
}

//will return true if given char is at position
bool checkPos(int h, int w, char a){
  if(maze[h][w] == 0 || maze[h][w] == 'X'){
    return 0;

  }
  else if (maze[h][w] == a) {
    return 1;
  }
}

//clears space
void setFloor(char(& maze)[ROWS][COLS], int h, int w){
  maze[h][w] = ' ';
}

//Generate a random value inbewteen 1 and a
int rand(int a){
  return rand() % a + 1;
}

//Enter battle
void battle (char(& maze)[ROWS][COLS], Player::Player *a, Kobold::Kobold *k){
  srand (time(NULL));
  //While either character is alive, fight
  while (a->checkAlive()>0 || k->checkAlive()>0){
    switch (rand(2)){
      case 1:
      //random attack damage
      a->damage(rand(6));
      std::cout<<"Player "<<a->icon<<" did damage!"<<std::endl;
      break;
      case 2:
      k->damage(rand(6));
      std::cout<<"Kobold "<<k->icon<<" did damage on "<<a->icon<<std::endl;
      break;
    }
    //After the turn, check if either died
    if (a->checkAlive()<0){
      std::cout<<"Player "<<a->icon<<" killed the Kobold!"<<std::endl;
      a->score = a->score + 25; //Increase 25 points
      maze[k->h][k->w] = ' '; //Remove kobold
      k->placeKobold(maze, rand(20), (80)); //Spawn new kobold
      k->HP = 7; //Declare kobold HP
      return;
    }
    else {
      std::cout<<"Player "<<a->icon<<" died!"<<std::endl;
      a->respawnCount = 10; //set counter for countdown
      a->dead = true;
      return;
    }
  }
}

//Character movement/interaction with objects
void* turn(void* args){
  //Grabbing the player object from the depths of the void*
  srand (time(NULL));
  struct threadargs *targsobj;
  targsobj = (struct threadargs *) args;
  char tile;
  //begin threads
  while(run){
    pthread_mutex_lock(&lock);
    std::cout<<"About to commence; PID: "<<getpid()<<std::endl; //display PID
    if(targsobj->aPlayer->dead == 0){
      std::cout<<targsobj->aPlayer->icon<<" is taking their turn."<<std::endl;
     }
     //If user is dead then do this
    else{
      std::cout<<targsobj->aPlayer->icon<<" is dead, and has to wait."<<std::endl;
      targsobj->aPlayer->respawnCount = targsobj->aPlayer->respawnCount-1; //decrease counter
      //if after this turn the respawnCount is 0 that means this player has waited 10 turns and can now respawn with 10 HP.
      if(targsobj->aPlayer->respawnCount == 0){
        targsobj->aPlayer->dead = false;
        targsobj->aPlayer->HP = 10;
      }
      break;
    }
    //Start moving
    switch (rand(4)) { //Choose direction to move
      case 1: //move up
      //If the position north of player is an x then go to next case
      //checks if location is out of bounds
      if(targsobj->aPlayer->h-1 < 0){
        break;
      }
      //If the next location is a space then proceed
      while(checkPos(targsobj->aPlayer->h-1, targsobj->aPlayer->w, ' ')){
        std::cout<<"Player is continuing north."<<std::endl;
        //set current array pos to blank
        maze[targsobj->aPlayer->h][targsobj->aPlayer->w] = ' ';
        //set new player on the map
        targsobj->aPlayer->placePlayer(maze, targsobj->aPlayer->h-1, targsobj->aPlayer->w);
        //cases if space is an interactable
        tile = maze[targsobj->aPlayer->h][targsobj->aPlayer->w];
        switch (tile) {
          case 'G':
          //if gold then add a point
          std::cout<<"Ooh, shiny."<<std::endl;
          targsobj->aPlayer->addPoint(1);
          break;
          case 'K':
          std::cout<<"Now entering battle!"<<std::endl;
          //if new position is a kobold then enter battle
          battle(maze, targsobj->aPlayer, targsobj->aKobold);
          break;
          //if player lands on the curse then they take 1-3 points of damage
          case 'C':
          std::cout<<"Better luck next time!"<<std::endl;
          targsobj->aPlayer->damage(rand(3));
          break;
        }
      }
      break;
      case 2: //move down
      //If the position south of player is an x then go to next case
      if(targsobj->aPlayer->h+1 > ROWS){
        break;
      }

      while(checkPos(targsobj->aPlayer->h+1, targsobj->aPlayer->w, ' ')){
        //set current array pos to blank
        maze[targsobj->aPlayer->h][targsobj->aPlayer->w] = ' ';
        std::cout<<"Player is contuining south."<<std::endl;
        //Place player onto the maze.
        targsobj->aPlayer->placePlayer(maze, targsobj->aPlayer->h+1, targsobj->aPlayer->w);
        //check interactable
        tile = maze[targsobj->aPlayer->h][targsobj->aPlayer->w];
        switch (tile) {
          case 'G':
          //if gold then add a point
          std::cout<<"Ooh, shiny."<<std::endl;
          targsobj->aPlayer->addPoint(1);
          break;
          case 'K':
          std::cout<<"Now entering battle!"<<std::endl;
          //if new position is a kobold then enter battle
          battle(maze, targsobj->aPlayer, targsobj->aKobold);
          break;
          //if player lands on the curse then they take 1-3 points of damage
          case 'C':
          std::cout<<"Better luck next time!"<<std::endl;
          targsobj->aPlayer->damage(rand(3));
          break;
        }
      }
      break;
      case 3: //move left
      //If the position West of player is an x then go to next case
      if(targsobj->aPlayer->w-1 < 0){
        break;
      }

      while(checkPos(targsobj->aPlayer->h, targsobj->aPlayer->w-1, ' ')){
        //set current array pos to blank
        maze[targsobj->aPlayer->h][targsobj->aPlayer->w] = ' ';
        std::cout<<"Player is continuing West."<<std::endl;
        //Place player on to the map
        targsobj->aPlayer->placePlayer(maze, targsobj->aPlayer->h, targsobj->aPlayer->w-1);
        //check interactable
        tile = maze[targsobj->aPlayer->h][targsobj->aPlayer->w];
        switch (tile) {
          case 'G':
          //if gold then add a point
          std::cout<<"Ooh, shiny."<<std::endl;
          targsobj->aPlayer->addPoint(1);
          break;
          case 'K':
          std::cout<<"Now entering battle!"<<std::endl;
          //if new position is a kobold then enter battle
          battle(maze, targsobj->aPlayer, targsobj->aKobold);
          break;
          //if player lands on the curse then they take 1-3 points of damage
          case 'C':
          std::cout<<"Better luck next time!"<<std::endl;
          targsobj->aPlayer->damage(rand(3));
          break;
        }
      }
      break;
      case 4: //move right
      //If the position East of player is an x then go to next case
      if(targsobj->aPlayer->w+1 < COLS){
        break;
      }

      while(checkPos(targsobj->aPlayer->h, targsobj->aPlayer->w+1, ' ')){
        //set current array pos to blank
        maze[targsobj->aPlayer->h][targsobj->aPlayer->w] = ' ';
        std::cout<<"Player is continuing East."<<std::endl;
        //Place player onto map
        targsobj->aPlayer->placePlayer(maze, targsobj->aPlayer->h, targsobj->aPlayer->w+1);
        //check interactable
        tile = maze[targsobj->aPlayer->h][targsobj->aPlayer->w];
        switch (tile) {
          case 'G':
          //if gold then add a point
          std::cout<<"Ooh, shiny."<<std::endl;
          targsobj->aPlayer->addPoint(1);
          break;
          case 'K':
          std::cout<<"Now entering battle!"<<std::endl;
          //if new position is a kobold then enter battle
          battle(maze, targsobj->aPlayer, targsobj->aKobold);
          break;
          //if player lands on the curse then they take 1-3 points of damage
          case 'C':
          std::cout<<"Better luck next time!"<<std::endl;
          targsobj->aPlayer->damage(rand(3));
          break;
        }
      }
      break;
    }
    std::cout<<targsobj->aPlayer->icon<<" is ending their turn."<<std::endl;
    usleep(500000);
    pthread_mutex_unlock(&lock);
    //delete targsobj;

  }
  return 0;
}

//Main method
int main() {
  //initialize stuff
  if (signal(SIGINT, ctrl_c)==SIG_ERR) {
    std::cout<<"Unable to change signal handler."<<std::endl;
    return 1;
  }

  if(signal(SIGUSR1, USR1)==SIG_ERR){
    std::cout<<"Unable to change signal handler."<<std::endl;
    return 1;
  }
  if(signal(SIGUSR2, USR2)==SIG_ERR){
    std::cout<<"Unable to change signal handler."<<std::endl;
    return 1;
  }
  //creating struct objects for threads
  //Player 1
  struct threadargs* readargs = new threadargs();
  readargs->aPlayer = &farvin;
  readargs->maze = ((char**)maze);
  readargs->aKobold = &kobbie;
  //Player 2
  struct threadargs readargs2;
  readargs2.aPlayer = &garvin;
  readargs2.maze = (char**)maze;
  readargs2.aKobold = &kobbie;
  //Player 3
  struct threadargs readargs3;
  readargs3.aPlayer = &tharvin;
  readargs3.maze = (char**)maze;
  readargs3.aKobold = &kobbie;
  //Player 4
  struct threadargs readargs4;
  readargs4.aPlayer = &sally;
  readargs4.maze = (char**)maze;
  readargs4.aKobold = &kobbie;

  //deallocate

  //Initializes maze in the beginning
  createMaze();
  printMaze(maze);
  //start threadings
  pthread_t ct[NUMTHREADS];
  pthread_mutex_init(&lock, NULL);

  pthread_mutex_lock(&lock);
  pthread_create(&ct[0], NULL, &turn, (void*)readargs);
  usleep(1000000);
  pthread_mutex_unlock(&lock);

  pthread_mutex_lock(&lock);
  pthread_create(&ct[1], NULL, &turn, (void*)&readargs2);
  usleep(1000000);
  pthread_mutex_unlock(&lock);

  pthread_mutex_lock(&lock);
  pthread_create(&ct[2], NULL, &turn, (void*)&readargs3);
  usleep(1000000);
  pthread_mutex_unlock(&lock);

  pthread_mutex_lock(&lock);
  pthread_create(&ct[3], NULL, &turn, (void*)&readargs4);
  usleep(1000000);
  pthread_mutex_unlock(&lock);

  while(run){
    usleep(3000000);
  }
}
