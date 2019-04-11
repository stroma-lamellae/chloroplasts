
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/types.h>
#include <sys/stat.h>

/*
 *defining of constants allowing for easy changing of the width of the area required, and the tolerance
 */
#define TRUE 1
#define FALSE 0
#define INSIDE_LENGTH 11
#define OUTSIDE_LENGTH 12
#define TOLERANCE 0.01

/*
 * Defining of the function NextDensity, used to calculate the averages for the next density in a square
 */
int NextDensity(double fromGrid[OUTSIDE_LENGTH][OUTSIDE_LENGTH], double toGrid[OUTSIDE_LENGTH][OUTSIDE_LENGTH]);

int main(int argc, char *argv[]){

    double gridA[OUTSIDE_LENGTH][OUTSIDE_LENGTH], gridB[OUTSIDE_LENGTH][OUTSIDE_LENGTH];
    int years = atoi(argv[1]), currentYear = 1, nextDensityValue = FALSE, i, j;
    double density;
    FILE *initialDensityFile;

    /*
     *Checks if there are exactly 2 arguments
     */
    if(argc < 3){
       printf("Not enough arguments\n");
       return (EXIT_FAILURE);
    }
    else if(argc > 3){
       printf("Too many arguments\n");
       return (EXIT_FAILURE);
    }

    initialDensityFile = fopen(argv[2],"r");

    /*
     *check if the file exists and can be read
     */
    if(initialDensityFile == NULL){
        printf("File can not be read\n");
        fclose(initialDensityFile);
        return (EXIT_FAILURE);
    }

    for(i = 0; i < OUTSIDE_LENGTH; i++){
        for(j = 0; j < OUTSIDE_LENGTH; j++){
            fscanf(initialDensityFile, "%lf", &density);
            if(density == EOF){
                break;
            }
            else{
                gridA[i][j] = density;
            }
        }
    }

    printf("Densities for year 0 are:\n");
    for(i = 0; i < OUTSIDE_LENGTH; i++){
        for(j = 0; j < OUTSIDE_LENGTH; j++){
            printf("%0.1lf\t", gridA[i][j]);
        }
        putchar('\n');
    }
    putchar('\n');

    for(i = 0; i < OUTSIDE_LENGTH; i++){
        for(j = 0; j < OUTSIDE_LENGTH; j++){
            gridB[i][j] = gridA[i][j];
        }
    }

    while(currentYear <= years && nextDensityValue == FALSE){
        nextDensityValue = NextDensity(gridA, gridB);
        printf("Densities for year %i are:", currentYear);
        putchar('\n');
        if(currentYear %2 != 0){
            for(i = 0; i < OUTSIDE_LENGTH; i++){
                for(j = 0; j < OUTSIDE_LENGTH; j++){
                    printf("%0.1lf\t", gridB[i][j]);
                }
                putchar('\n');
            }
            putchar('\n');
        }
        else if(currentYear %2 == 0){
            for(i = 0; i < OUTSIDE_LENGTH; i++){
                for(j = 0; j < OUTSIDE_LENGTH; j++){
                    printf("%0.1lf\t", gridA[i][j]);
                }
                putchar('\n');
            }
            putchar('\n');
        }

        if(nextDensityValue == TRUE){
            printf("The plantation has reached steady state after %i years", currentYear);
            putchar('\n');
            exit(0);
        }
        else{
            currentYear++;
        }
    }
}

/*
 *The function for calculating the next density in each square
 */
int NextDensity(double fromGrid[OUTSIDE_LENGTH][OUTSIDE_LENGTH], double toGrid[OUTSIDE_LENGTH][OUTSIDE_LENGTH]){

    int isStable = FALSE, breakLoop = FALSE;
    int iCalc, iCheck, jCalc, jCheck;
    static int currentYearFunc = 1;


    for(iCalc = 1; iCalc < INSIDE_LENGTH; iCalc++){
        for(jCalc = 1; jCalc < INSIDE_LENGTH; jCalc++){
            if(currentYearFunc % 2 != 0){
                toGrid[iCalc][jCalc] = (fromGrid[iCalc-1][jCalc] + fromGrid[iCalc][jCalc-1] + fromGrid[iCalc][jCalc] + fromGrid[iCalc][jCalc+1] + fromGrid[iCalc+1][jCalc]) / 5.0;
            }
            else if(currentYearFunc % 2 == 0){
                fromGrid[iCalc][jCalc] = (toGrid[iCalc-1][jCalc] + toGrid[iCalc][jCalc-1] + toGrid[iCalc][jCalc] + toGrid[iCalc][jCalc+1] + toGrid[iCalc+1][jCalc]) / 5.0;
            }
        }
    }

    currentYearFunc++;

    for(iCheck = 1; iCheck < INSIDE_LENGTH; iCheck++){
        for(jCheck = 1; jCheck < INSIDE_LENGTH; jCheck++){
            if(fabs(fromGrid[iCheck][jCheck] - toGrid[iCheck][jCheck]) > TOLERANCE){
                isStable = FALSE;
                breakLoop = TRUE;
                break;
            }
            else if(fabs(fromGrid[iCheck][jCheck] - toGrid[iCheck][jCheck]) <= TOLERANCE){
                isStable = TRUE;
            }
        }
        if(breakLoop == TRUE){
            break;
        }
    }

    if(isStable == TRUE){
        return TRUE;
    }
    else{
        return FALSE;
    }
}