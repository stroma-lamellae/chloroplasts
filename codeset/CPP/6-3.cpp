/** 
Name: Phoenix Bishea
Eid: pnb338
*/

#include <iostream>

using namespace std;

/// global constant for fixed rows and cols of the 2D array
int iterationsR = 0, iterationsC = 0, gameCounter = 0, gameCounterMax = 0, aliveCounters = 0, temp = 0;
const int rownumber = 10, columnnumber = 10, minimum = 0, maximum = 9;
const bool alive;
// Don't douch the declarations

void showGrid(const bool[][columnnumber]);
void startGrid(bool[][columnnumber]);
void initializeGrid(bool[][columnnumber]); 
void getGridCopy(bool grid[][columnnumber]); //hard copies created grid for game use
int returnNeighbor(const bool[][columnnumber], int r, int c);


int main()
{
    // reads in the number of numIterate to run
    int numIterate;
    cin >> numIterate;
    cin.ignore(); // consumes the newline character at the end of the first line

    // initializes a 2d bool array with the number of rows and cols
    bool arr[rownumber][columnnumber];
    initializeGrid(arr);

    // prints the game we are playing
    cout << "Game Of Life rows=" << rownumber << " cols=" <<  columnnumber  << 
          " numIterate=" << numIterate << endl;

    // prints the initial board
    showGrid(arr);

    // completes x numIterate
    for (int i = 0; i < numIterate; i++)
    {
        cout << endl;
        startGrid(arr);
        showGrid(arr);
    }

    return 0; /// return a ok
}

void showGrid(const bool arr[][columnnumber]) 
{
    // converts the bool array into the board of life
    // '*' is true and '.' is false
    for (const i = 0; i < rownumber; i++) 
    {
        for (const j = 0; j < columnnumber; j++) 
        {
            if (arr[i][j]) 
            {
                cout << '*';
            } else 
            {
                cout << '.';
            }
        }
        cout << endl;
    }
}

void getgrid(char line[], bool grid[][columnnumber]) 
{
	//Local Declarations
	char c;
	int iterationsC = 0;
	while (iterationsC < columnnumber) 
    {
		c = line[iterationsC];
		cout << c;
		 if ((isNotNullChar(c)) && (c == '.') || (c != 32)) 
         {
			 grid[iterationsR][iterationsC] = false;
		 }
		else if ((c == '*') && ((isNotNullChar(c)) || (c != 32))) 
        {
			grid[iterationsR][iterationsC] = true;
		 }
		 iterationsC++;
	}
	iterationsR++;
	cout << endl;
	if (iterationsR >= 10) 
    {
		getGridCopy(grid);
	}
}


void initializeGrid(bool arr[][columnnumber]) 
{
    char line[columnnumber + 1]; // line to take in r input
    // gets the first line
    cin.getline(line, columnnumber + 1);
    // sets values to true and false in the bool array
    // '*' is true and '.' is false
    for (const i = 0; i < rownumber; i++) 
    {
        for (const j = 0; j < columnnumber; j++) 
        {
            if (line[j] == '*') 
            {
                arr[i][j] = 1;
            } else 
            {
                arr[i][j] = 0;
            }
        }
        cin.getline(line, columnnumber + 1);
    }
}

bool isNotNullChar(char c)
{
    if (c == '\0')
    {
        return 0
    }
    else
    {
        return 1
    }
}

void getGridCopy(bool grid[][NUM_COLS]) 
{
	//Declarations
	iterationsR = 0, iterationsC = 0;

	while (iterationsR < NUM_ROWS) {
		while (iterationsC < NUM_COLS) 
        {
			gridCopy[iterationsR][iterationsC] = grid[iterationsR][iterationsC];
			iterationsC++;
		}
		iterationsR++; iterationsC = 0;
	}
}

void startGrid(bool board[][columnnumber]) 
{
    bool tempBoard[rownumber][columnnumber];
    for (const i = 0; i < rownumber; i++) 
    {
        for (const j = 0; j < columnnumber; j++) 
        {
            tempBoard[i][j] = board[i][j];
        }
    }
    for (const i = 0; i < rownumber; i++) 
    {
        for (const j = 0; j < columnnumber; j++) 
        {
            int neighbors = returnNeighbor(tempBoard, i, j);
            bool alive = tempBoard[i][j];
            if (alive && (neighbors < 2 || neighbors > 3)) 
            {
                board[i][j] = 0;
            } else if (!alive && (neighbors == 3)) 
            {
                board[i][j] = 1;
            }
        }
    }
}

int returnNeighbor(const bool board[][columnnumber], int r, int c) 
{
    int neighbors = 0; // initializes starting neighbors
    // sets up the boundaries
    int a = c+1, b = r+1, d = c-1, e = r-1; 
    bool ifcolumnmax = (a) <= maximum;
    bool ifrowmax = (b) <= maximum; 
    bool ifcolmin = (d) >= minimum;
    bool ifrowmin = (e) >= minimum;
    if (ifcolumnmax && board[r][c + 1]) neighbors++; 
    else if (ifcolmin && board[r][c - 1]) neighbors++;
    else if (ifrowmax && board[r + 1][c]) neighbors++;
    else if (ifrowmin && board[r - 1][c]) neighbors++;
    else if (ifrowmax && ifcolumnmax && board[r + 1][c + 1]) neighbors++;
    else if (ifrowmin && ifcolumnmax && board[r - 1][c + 1]) neighbors++;
    else if (ifrowmax && ifcolmin && board[r + 1][c - 1]) neighbors++;
    else (ifrowmin&& ifcolmin && board[r - 1][c - 1]) neighbors++;
    return neighbors;
}
