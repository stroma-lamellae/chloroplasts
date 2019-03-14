#include "GridBuilder.h"

using namespace std;


/**
 * @author  Richard GNU-Linux
 * @studentNum 5012386
*/

GridBuilder::GridBuilder(){};

GridBuilder::~GridBuilder(){};

double** GridBuilder::buildAdjacencyMatrix(ifstream* inFile, int& size){
	double ** vertexPoints;  // The array of x,y coordinates of the points
	char currentLine[20];    // For file input
	int i,j;
	int num;
	double tmp;
	double** adjacent;     // The adjacency matrix
        double xDif, yDif;

	// Read the first line of the file. ie the number of vertices in
	// the graph.

	if(!inFile->eof())	*inFile >> currentLine;
	else {
		cout << "Premature EOF reached. Program aborted.\n";
		return NULL;
	}

        size = atoi(currentLine);  // convert to an integer
	if (size==0){
		cout << "Invalid number of vertices. Program aborted!\n";
		return NULL;
	}

	// Build the dynamic array to hold the set of points

	vertexPoints = new double*[size];
	for(i=0;i<size;i++) vertexPoints[i] = new double[2];

	// Read the set of points into the array vertexPoints[n][2]
	// Note: None of the points can be zero, since inFile returns
	// a zero on a read failure.

	for(i=0;i<size;i++){

		*inFile >> currentLine;     // We are not using the num number
		num = atoi(currentLine);  // Just read it and throw it away
		if((num < SMALL_NUMBER)||(num > BIG_NUMBER)){
			cout << "Invalid data in line number "
				 << i+1 << ". Program aborted.\n";
			return NULL;
		}

		*inFile >> currentLine;
		tmp = atof(currentLine);
               		if((tmp < SMALL_NUMBER)||(tmp > BIG_NUMBER)){
			cout << "Invalid data in line number "
				 << i+1 << ". Program aborted.\n";
			return NULL;
		}
		else vertexPoints[i][0] = tmp;
		*inFile >> currentLine;
		tmp = atof(currentLine);
		if((tmp < SMALL_NUMBER)||(tmp > BIG_NUMBER)){
			cout << "Invalid data in line number "
				 << i+1 << ". Program aborted.\n";
			return NULL;
		}
		else vertexPoints[i][1] = tmp;
               }

	adjacent = new double*[size];
	for(i=0;i<size;i++) adjacent[i] = new double[size];

	for(i=0;i<size;i++){
		for (j=0;j<size;j++){
                  		xDif = vertexPoints[i][0] - vertexPoints[j][0];
			yDif = vertexPoints[i][1] - vertexPoints[j][1];

			adjacent[i][j] = sqrt((xDif*xDif) + (yDif*yDif));

		}
	}

	inFile->close();
	for(i=0;i<size;i++) delete[] vertexPoints[i];
	delete[] vertexPoints;

	return adjacent;

}  // end of buildAdjacencyMatrix()


