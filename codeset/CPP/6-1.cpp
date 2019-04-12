/** 
Name: Phoenix Bishea
Eid: pnb338

Q1: Why are the arrays passed to both print life functions const? 

    The arrays passed to print life are not being directly modified.
    Since the value never changes it can be declared const.

Q2: Why are the arrays passed to both play life functions not const?

    The arrays passed to play life are not const because they are modified.
    Play life changes the cells in the array every iteration depending
    on the rules of the game of life.

Q3: If we did change the arrays passed to play life functions to make them const, 
    what else would have to happen to make play life work?
    
    Under these circumstances an additional array would have to be created and returned
    from play life to main to make play life work. The array passed to play life could not
    be modified.
*/

#include <iostream>

using namespace std;

/// global constant for fixed rows and cols of the 2D array
const int NUM_ROWS = 10;
const int NUM_COLS = 10;
const int MIN = 0;
const int MAX = 9;

/** function declarations
    you will need to write the definitions of these functions below.
    DO NOT MODIFY the declarations.
    You may create your own functions, but you must use these.
*/

/** 2d array functions, notice that for 2d arrays the second size 
    needs to be fixed, or more precisely it needs to be a const.
    if you typed a literal, like 5, it would be a literal constant,
    which also works.
*/
void printLife2DArray(const bool[][NUM_COLS]);
void playLife2DArray(bool[][NUM_COLS]);

 /** Initializes the bool array created in main to the input array.
     Note: '*' is true and '.' is false.
 */ 
void initializeLife2DArray(bool[][NUM_COLS]); 
int getNeighbors(const bool[][NUM_COLS], int row, int col);


int main() {

    /// read in the number of iterations to run

    /** make a 2d bool array with the number of rows and cols
    
    Some input examples and explanation of game of life
    Look at http://en.wikipedia.org/wiki/Conway%27s_Game_of_Life#Examples_of_patterns
    */

    /** print out what game we are playing */
    // cout << "Game Of Life rows=" << /* nrows */ << " cols=" <<  ncols  << 
    //       " iterations=" << /* number of iterations */ << endl;

    /** 
        start your code
    */

    // reads in the number of iterations to run
    int iterations;
    cin >> iterations;
    cin.ignore(); // consumes the newline character at the end of the first line

    // initializes a 2d bool array with the number of rows and cols
    bool arr[NUM_ROWS][NUM_COLS];
    initializeLife2DArray(arr);

    // prints the game we are playing
    cout << "Game Of Life rows=" << NUM_ROWS << " cols=" <<  NUM_COLS  << 
          " iterations=" << iterations << endl;

    // prints the initial board
    printLife2DArray(arr);

    // completes x iterations
    for (int i = 0; i < iterations; i++) {
        cout << endl;
        playLife2DArray(arr);
        printLife2DArray(arr);
    }

    return 0; /// return a ok
}

void initializeLife2DArray(bool arr[][NUM_COLS]) {

    char line[NUM_COLS + 1]; // line to take in row input

    // gets the first line
    cin.getline(line, NUM_COLS + 1);

    // sets values to true and false in the bool array
    // '*' is true and '.' is false
    for (size_t i = 0; i < NUM_ROWS; i++) {
        for (size_t j = 0; j < NUM_COLS; j++) {
            if (line[j] == '*') {
                arr[i][j] = 1;
            } else {
                arr[i][j] = 0;
            }
        }
        cin.getline(line, NUM_COLS + 1);
    }
}

void printLife2DArray(const bool arr[][NUM_COLS]) {

    // converts the bool array into the board of life
    // '*' is true and '.' is false
    for (size_t i = 0; i < NUM_ROWS; i++) {
        for (size_t j = 0; j < NUM_COLS; j++) {
            if (arr[i][j]) {
                cout << '*';
            } else {
                cout << '.';
            }
        }
        cout << endl;
    }
}

void playLife2DArray(bool board[][NUM_COLS]) {

    // creates a temporary board and sets it equal to the game board
    bool tempBoard[NUM_ROWS][NUM_COLS];
    for (size_t i = 0; i < NUM_ROWS; i++) {
        for (size_t j = 0; j < NUM_COLS; j++) {
            tempBoard[i][j] = board[i][j];
        }
    }

    // updates cells using the game of life rules
    for (size_t i = 0; i < NUM_ROWS; i++) {
        for (size_t j = 0; j < NUM_COLS; j++) {

            // gets a cell's neighbors and status
            int neighbors = getNeighbors(tempBoard, i, j);
            bool alive = tempBoard[i][j];

            // changes the cell's condition depending on its neighbors
            if (alive && (neighbors < 2 || neighbors > 3)) {
                board[i][j] = 0;
            } else if (!alive && (neighbors == 3)) {
                board[i][j] = 1;
            }
        }
    }
}

int getNeighbors(const bool board[][NUM_COLS], int row, int col) {
   
    int neighbors = 0; // initializes starting neighbors
    
    // sets up the boundaries
    bool colLessMax = (col + 1) <= MAX;
    bool rowLessMax = (row + 1) <= MAX; 
    bool colGreaterMin = (col - 1) >= MIN;
    bool rowGreaterMin = (row - 1) >= MIN;

    // if the operation is within bounds, complete it and tally living neighbors
    if (colLessMax 
        && board[row][col + 1]) neighbors++; // increment if a living neighbor is found

    if (colGreaterMin 
        && board[row][col - 1]) neighbors++;

    if (rowLessMax 
        && board[row + 1][col]) neighbors++;

    if (rowGreaterMin 
        && board[row - 1][col]) neighbors++;

    if (rowLessMax && colLessMax 
        && board[row + 1][col + 1]) neighbors++;
    
    if (rowGreaterMin && colLessMax 
        && board[row - 1][col + 1]) neighbors++;

    if (rowLessMax && colGreaterMin 
        && board[row + 1][col - 1]) neighbors++;

    if (rowGreaterMin&& colGreaterMin 
        && board[row - 1][col - 1]) neighbors++;

    return neighbors;
}
