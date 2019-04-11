/*
 * CPS 305 Assignment 1
 *PLEASE COMPILE MY CODE TO THE c99 STANDARD
 High Level Overview: 
User is given a pointer to a random item in the 2D array.  
User must guess the corresponding INDEX of the array (i and j values). 
This guessing game repeats for various addresses in the array, until the
user Quits.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define buffer 20
#define defaultMatrixSize 5

//struct for a complex number with real and imaginary parts
typedef struct {
    int real_part;
    int imag_part;
} complex ;

//Generates a complex number containing a real and imaginary part and returns the complex number
complex generateRandomComplex(int limit){
    complex number;
    number.real_part=rand()%limit;
    number.imag_part=rand()%limit;
    return number;
}
//Prints out the horizontal matrix labels for easy identification, accepts # of columns as argument
void labelXAxis(int N){
    printf("\n           ");
    for(int xLabel=0;xLabel<N;xLabel++){
        printf("M[0][%d]               ",xLabel);
    }
}
int main(int argc, char *argv[]){
    //variable declarations
    char input[buffer];
    char inputImag[buffer/2];
    char inputReal[buffer/2];
    char *errArgument;
    int N = defaultMatrixSize;
    char *token;
    double uniqueAdressCount = 0;
    double totalGuesses = 0;
    double correctNoHint = 0;
    double correctwHint = 0;
    double correctwBadGuesses = 0;
    int incorrectFlag = 0;
    int hintFlag = 0;
    srand((unsigned)time(NULL));

    //set size of 2-D matrix to program argument if provided defaulting to 5 otherwise
    if(argc >= 2){
        int argument= (int)strtol(argv[1],&errArgument,10);
        if(*errArgument == '\0') //if the terminal argument was fully converted into an integer
            N = argument;  //sets matrix size to terminal argument
    }
    //allocate matrix
    complex **matrix;
    matrix=(complex **)malloc(N * sizeof(complex *));
    for(int i=0;i<N;i++){
        matrix[i]=(complex *)malloc(sizeof(complex)* N);
    }
    //fill in matrix with random complex numbers
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            matrix[i][j]=generateRandomComplex(N-1);
        }
    }

    while(1){
        complex answer=generateRandomComplex(N-1);
        while(1) {
            printf("M[0][0]=%p.  ",&matrix[0][0]);
            printf("M[i][j]=%p. ",&matrix[answer.real_part][answer.imag_part]);
            printf("What's i and j? (or Q or H or HH or HHH): ");
            fgets(input, 10, stdin);  //additional chars(11+) will cause the loop to iterate, taking the next 10 chars as input automatically, no real negative effects
            token=strtok(input," ");
            strcpy(inputReal,token);  //get the first word from the string inputted by user and store it
            token = strtok(NULL, " "); //advance strtok function to next word
            if(token!=NULL)
                strcpy(inputImag,token);  //copy second number inputted into the imaginary number variable
            if (strcmp(inputReal, "Q\n") == 0){
                printf("----------------------\n");
                printf("%.0lf  Total Number\n",uniqueAdressCount);
                printf("%.0lf%% Correct the first time\n",correctNoHint/totalGuesses*100);
                printf("%.0lf%% Correct after 2 or more guesses (no hints)\n",correctwBadGuesses/totalGuesses*100);
                printf("%.0lf%% Correct after hint(s)\n",correctwHint/totalGuesses*100);
                printf("----------------------\n");

                for(int i = 0; i < N; i++)  //free matrix to prevent memory leaks
                    free(matrix[i]);
                free(matrix);
                exit(0);
            }
            else if (strcmp(inputReal, "H\n")==0){ //if first word is H then...
                for(int i=0;i<N;i++) {
                    printf("M[%d][0] %p \n",i, &matrix[i][0]);
                }
                printf("\n");
                hintFlag = 1;
            }
            else if (strcmp(inputReal, "HH\n")==0){
                labelXAxis(N);
                printf("\nM[0][0] ");
                for(int j=0;j<N;j++){
                   printf("%p        ",&matrix[0][j]);
                }
                printf("\n");
                for(int i=1;i<N;i++){
                    printf("M[%d][0] %p \n",i, &matrix[i][0]);
                }
                printf("\n");
                hintFlag = 1;
            }
            else if (strcmp(inputReal, "HHH\n")==0){
                labelXAxis(N);
                for(int i=0;i<N;i++) {
                    printf("\nM[%d][0] ",i);
                    for (int j = 0; j < N; j++) {
                        printf("%p        ", &matrix[i][j]);
                    }
                }
                printf("\n\n");
                hintFlag = 1;
            }
            else {
                char *errI;
                char *errJ;
                int guessI;
                int guessJ;
                guessI = (int) strtol(inputReal,&errI,10);  //convert string to int, and keep track of next non integer for error checking
                guessJ = (int) strtol(inputImag, &errJ, 10);

                if(*errI != '\0' || *errJ!='\n')  //if a non integer is entered for either i or j re-ask for input
                    continue;
                else  //important case where a valid number is supplied for i and j
                    totalGuesses=totalGuesses+1;
                    if(guessI==answer.real_part && guessJ==answer.imag_part){
                        printf("You guessed correctly, good job!\n");
                        if(hintFlag)
                            correctwHint=correctwHint+1;
                        else
                            correctNoHint=correctNoHint+1;
                        if(incorrectFlag)
                            correctwBadGuesses = correctwBadGuesses+1;
                        hintFlag = 0;
                        incorrectFlag = 0;
                        break;
                    }
                    else{
                        printf("Try again\n");
                        incorrectFlag = 1;
                        continue;
                    }
            }
        }
        uniqueAdressCount=uniqueAdressCount+1;  //counts how many rounds played
    }
}