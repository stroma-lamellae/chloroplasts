/** 
Name: Phoenix Bishea
Eid: pnb338

*/

#include <iostream>

using namespace std;

const int numRow = 10;
const int numCol = 10;

//initialize arrays
void initializeArray(bool[][10]); 
void printArray(const bool[][10]);
void playGameOfLife(bool[][10]);
int numNeighbors(const bool[][10], int row, int col);

int main() {
    int iters;
    int nothing;
    cin >> iters;
    cin.ignore();
    bool arr[numRow][numCol];
    initializeArray(arr);
    // prints the game we are playing
    cout << "Rows =" << numRow << " Columns =" <<  numCol  << " Number of iters =" << iters << endl;
    printArray(arr);
    for (int i = 0; i < iters; i++) {
        cout << endl;
        playGameOfLife(arr);
        printArray(arr);
    }
    return nothing; /// return bool
}

void initializeArray(bool arr[][numCol]) {
    char letter[numCol + 1]; //take in row input
    cin.getline(letter, numCol + 1); //return first letter
    // '<' is true and '>' is false
    for (size_t i = 0; i < numRow; i++) {
        for (size_t j = 0; j < numCol; j++) {
            if (letter[j] == '>') {
                arr[i][j] = 1;
            } else {
                arr[i][j] = 0;
            }
        }
        cin.getline(letter, numCol + 1);
    }
}

void printArray(const bool arr[][numCol]) {
    for (size_t i = 0; i < numRow; i++) {
        for (size_t j = 0; j < numCol; j++) {
            if (arr[i][j] && j < numCol) {
                cout << '>';
            } else {
                cout << '<';
            }
        }
        cout << endl;
    }
}

int numNeighbors(const bool board[][numCol], int row, int col) {
    int numNeighbors = 0; // initializes starting numNeighbors
    int sizeMin = 0;
    int sizeMax = 9;
    // sets up the boundaries
    bool ifminCol = (col + 1) <= sizeMax;
    bool ifminRow = (row + 1) <= sizeMax; 
    bool ifmaxCol = (col - 1) >= sizeMin;
    bool ifmaxRow = (row - 1) >= sizeMin;
    // if the operation is within bounds, complete it and tally living numNeighbors
    if (ifminCol && board[row][col + 1]) numNeighbors++; // increment if a living neighbor is found
    if (ifmaxCol 
        && board[row][col - 1]) numNeighbors++;

    if (rowLessMax 
        && board[row + 1][col]) numNeighbors++;

    if (ifmaxRow 
        && board[row - 1][col]) numNeighbors++;

    if (rowLessMax && ifminCol 
        && board[row + 1][col + 1]) numNeighbors++;
    
    if (ifmaxRow && ifminCol 
        && board[row - 1][col + 1]) numNeighbors++;

    if (rowLessMax && ifmaxCol 
        && board[row + 1][col - 1]) numNeighbors++;

    if (ifmaxRow&& ifmaxCol 
        && board[row - 1][col - 1]) numNeighbors++;

    return numNeighbors;
}

void playGameOfLife(bool board[][numCol]) {
    //makes a temp board
    bool temp[numRow][numCol];
    for (size_t i = 0; i < numRow; i++) {
        for (size_t j = 0; j < numCol; j++) {
            temp[i][j] = board[i][j];
        }
    }
    // updates each cell in the array 
    for (size_t i = 0; i < numRow; i++) {
        for (size_t j = 0; j < numCol; j++) {
            int numNeighbors = numNeighbors(temp, i, j);
            bool isAlive = temp[i][j];
            if (isAlive && (numNeighbors < 2 || numNeighbors > 3)) {
                board[i][j] = 0;
            } else if (!isAlive && (numNeighbors == 3)) {
                board[i][j] = 1;
            }
        }
    }
}
