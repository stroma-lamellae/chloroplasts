#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int startX, startY;

typedef struct PondStruct {
   int **grid;
   int length;
   int maxIndex;
} Pond;

typedef struct PadSetStruct {
   struct PadNodeStruct *first;
   struct PadNodeStruct *last;
} PadSet;

typedef struct PadNodeStruct{
   int x;
   int y;
   struct PadNodeStruct *next;
} PadNode;

Pond* initializePond(int size);
void print_pond(Pond *P);
void find_path(Pond *P, int x, int y, int i, int p);
PadSet* initializePadSet();
PadNode* initializePadNode();
void print_set(PadSet *pSet);
void addNode(PadSet *P, PadNode *N);
PadSet *padSetPopulatedWithNextPads(Pond *P, int x, int y);
void addNewNode(PadSet *P, int x, int y);
PadNode* removeNode(PadSet *P);
void freePadSet(PadSet *P) ;

int main( int argc, char *argv[] )
{
   if(argv[1]==NULL || argv[2]==NULL || argv[3]==NULL) {
      printf("Invalid arguments... exiting.\n");
      return 1;
   }
   int size = atoi(argv[1]);
   int xPos = atoi(argv[2]);
   int yPos = atoi(argv[3]);
   
   printf("The grid will be %dX%d\n",size, size);
   printf("The starting position is: %d, %d\n", xPos, yPos); 

   Pond *pond;
   printf("%p => ", pond);
   pond=initializePond(size);
   printf("%p\n", pond);
   print_pond(pond);
   find_path(pond, xPos, yPos, 1, 0);
   printf("No path found.");
   return 1;
}

Pond* initializePond(int size)
{
   int i,j;
   Pond *P=malloc(sizeof(Pond));
   P->length=size;
   P->maxIndex=size-1;
   P->grid=calloc(size, sizeof *P->grid);
   for(i=0; i<P->length; i++) {
      P->grid[i]=calloc(size, sizeof(int));
   }
   return P;
}

void print_pond(Pond *P)
{
   int i,j;
   for(i=0; i<P->length; i++) {
      for(j=0; j<P->length; j++) {
         printf("%2d ", P->grid[i][j]);
      }
      putchar('\n');
   }
}

void find_path(Pond *P, int x, int y, int c, int p)
{
   /*
  find_path ( Pond, x, y, i , prevKind)
     Pond[x][y] = i   //the ith pad along the path
     if i==SIZE*SIZE  //reached the end of the path
        print_pond(Pond)
        exit
     else
        let nextValidPadSet be the set of next valid pads
        for nextPad in nextValidPadSet do
            let [Px][Py] be nextPad's coordinates 
            find_path ( Pond, Px, Py, i+1, thisKind )
        Pond[x][y] = 0   //backtrack
    */

   P->grid[x][y] = c;
   if(c == P->length*P->length) {
      //print_pond(P);
      printf("Path found.\n");
      print_pond(P);
      exit(0);
   } else {
      PadSet *nextValidPadSet = padSetPopulatedWithNextPads(P, x, y);
      PadNode *tempPadNode = nextValidPadSet->first;
      while(tempPadNode!=NULL) {
         find_path(P, tempPadNode->x, tempPadNode->y, c+1, c);
         tempPadNode=tempPadNode->next;
      }
      freePadSet(nextValidPadSet);
      P->grid[x][y]=0;
   }
}

PadSet* initializePadSet()
{
   PadSet *returnPadSet;
   returnPadSet = malloc(sizeof(PadSet));
   returnPadSet->first=NULL;
   return returnPadSet;
}

PadNode* initializePadNode()
{
   PadNode *returnPadNode;
   returnPadNode = malloc(sizeof(PadNode));
   returnPadNode->x=-1;
   returnPadNode->y=-1;
   returnPadNode->next=NULL;
   return returnPadNode;
}
PadSet *padSetPopulatedWithNextPads(Pond *P, int x, int y)
{
   int tempX, tempY;
   PadNode *temp; 
   PadSet *returnPadSet;
   returnPadSet = initializePadSet();

   //1 o'clock
   if(x>=2 && y <= P->maxIndex-1) {
      tempX=x-2; tempY= y+1;
      if(P->grid[tempX][tempY]!=0) {
      } else {
         //printf("1\n");
         addNewNode(returnPadSet, tempX, tempY);
      }
   }
   //2 o'clock
   if(x>=1 && y<=P->maxIndex-2) {
      tempX=x-1; tempY=y+2;
      if(P->grid[tempX][tempY]!=0) {
      } else {
         //printf("2\n");
         addNewNode(returnPadSet, tempX, tempY);
      }
   }
   //4 o'clock
   if(x<=P->maxIndex-1 && y<=P->maxIndex-2) {
      //printf("%d, %d\n", x, y);
      tempX=x+1; tempY=y+2;
      if(P->grid[tempX][tempY]!=0) {
      } else {
         //printf("4 o'clock added\n");
         addNewNode(returnPadSet, tempX, tempY);
      }
   }
   //5 o'clock
   if(x<=P->maxIndex-2 && y<=P->maxIndex-1) {
      tempX=x+2;  tempY=y+1;
      if(P->grid[tempX][tempY]!=0) {
      } else {
         //printf("5 o'clock added\n");
         addNewNode(returnPadSet, tempX, tempY);
      }
   }
   //7 o'clock
   if(x<=P->maxIndex-2 && y>=1) {
      tempX=x+2;  tempY=y-1; 
      if(P->grid[tempX][tempY]!=0) {
      } else {
         //printf("7\n");
         addNewNode(returnPadSet, tempX, tempY);
      }
   }
   //8 o'clock
   if(x<=P->maxIndex-1 && y>=2) {
      tempX=x+1;  tempY=y-2;
      if(P->grid[tempX][tempY]!=0) {
      } else {
         //printf("8\n");
         addNewNode(returnPadSet, tempX, tempY);
      }
   }
   //10 o'clock
   if(x>=1 && y>=2) {
      tempX=x-1;  tempY=y-2;
      if(P->grid[tempX][tempY]!=0) {
      } else {
         //printf("10\n");
         addNewNode(returnPadSet, tempX, tempY); 
      }
   }
   //11 o'clock
   if(x>=2 && y >= 1) {
      tempX=x-2;  tempY=y-1;
      if(P->grid[tempX][tempY]!=0) {
      } else {
         //printf("11\n");
         addNewNode(returnPadSet, tempX, tempY);
      }
   }

   //print_set(returnPadSet);
   //sleep(1);
   return returnPadSet;
}
void print_set(PadSet *pSet)
{
   PadNode *P = pSet->first;
   printf("(%d, %d) ", P->x, P->y);
   while(P->next != NULL) {
      printf("-> (%d, %d) ", P->x, P->y);
      P=P->next;
   }
   putchar('\n');
}
void addNode(PadSet *P, PadNode *N)
{
   if(P->first==NULL) {
      P->first=N;
      P->last=N;
   } else if (P->first==P->last) {
      P->first->next=N;
      P->last=N;
   } else {
      P->last->next=N;
      P->last=N;
   }
   //printf("%d, %d added\n", N->x, N->y);
}
void addNewNode(PadSet *P, int x, int y)
{
   PadNode *nodeToAdd = initializePadNode();
   nodeToAdd->x=x; 
   nodeToAdd->y=y;
   addNode(P, nodeToAdd);
}
PadNode* removeNode(PadSet *P)
{
   PadNode *temp = P->first;
   P->first=P->first->next;
   free(temp);
   return temp;
}
void freePadSet(PadSet *P) 
{
   PadNode *pNode;
   PadNode *nodeToFree;
   pNode=P->first;
   while(pNode!=NULL) {
      nodeToFree=pNode;
      pNode=pNode->next;
      free(nodeToFree);
   }
   free(P);
}