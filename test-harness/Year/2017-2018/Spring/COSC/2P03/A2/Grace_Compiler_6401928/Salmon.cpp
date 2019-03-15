#include "Salmon.h"

// constructor

/**
    @author  Admiral Grace Compiler
     @studentNum 6401928
*/

Salmon::Salmon(int numPts, int Population, int survival, float mem, float beta) {
    this->POPULATION = Population;
    this->SURVIVAL = survival;
    this->MEMORY = mem;
    this->BETA = beta;
    this->size = numPts;
    this->tabu = new int[this->size];
    this->memory = new int[this->size];
    this->sortedMemory = new int[this->size];
    this->setRandomPath();

} // end constructor()


// destructor

Salmon::~Salmon() {

    delete[] this->tabu;
    delete[] this->memory;
    delete[] this->sortedMemory;

} // end destructor()



// This function scans the tabu list of this salmon to see if vertex
// n is in the list. Returns true if it is found.

bool Salmon::scanTabu(int n) {

    for (int i = 0; i < this->size; i++) {
        if (this->tabu[i] == n) {
            return true;
        }
    }
    return false;

} // end scanTabu()




// This function calculates the normalization constant (the total of
// all flows in all edges connected to the current vertex), not counting
// those in the tabu list.

double Salmon::calcNormalization(FlowNetwork* fnet) {

    double total = 0.0;
    double flow;


    for (int i = 0; i < this->size; i++) {
        if (!this->scanTabu(i)) {
            flow = fnet->getAverageFlow(this->tabu[this->currentPointer], i);
            flow = pow(flow, BETA);
            total = total + flow;
        }
    }
    return total;

} // end of calcNormalization()




// This function returns the length of this salmon's tour

double Salmon::getPathLength() {

    return this->pathLength;

} // end of getPathLength()

void Salmon::setPathLength(double** adjMat) {

    double length = 0;

    for (int i = 0; i < this->size - 1; i++) {

        length = length + adjMat[this->tabu[i]][this->tabu[i + 1]];
    }

    // Add in distance back to start vertex

    length = length + adjMat[tabu[this->size - 1]][tabu[0]];
    this->pathLength = length;

} // end of setPathLength()



// This method resets the tabu list

void Salmon::resetTabu() {

    // copy tabu list to memory

    for (int i = 0; i < this->size; i++) {
        this->memory[i] = this->tabu[i];
    }

    // recalculate sorted memory

    for (int i = 0; i < this->size - 1; i++) {
        this->sortedMemory[this->memory[i]] = this->memory[i + 1];
    }
    this->sortedMemory[this->memory[size - 1]] = this->memory[0];


    // set tabu list to -1

    for (int i = 0; i < this->size; i++) {
        this->tabu[i] = -1;
    }

    // Start the salmon where its parent started

    this->tabu[0] = this->memory[0];
    this->currentPointer = 0;

} // end of resetTabu()



// This method sets a random path in the salmon's memory to begin
// the algorithm.

void Salmon::setRandomPath() {

    int random;
    int temp;

    for (int i = 0; i < this->size; i++) this->tabu[i] = i;

    for (int i = 0; i < this->size; i++) {
        random = randomInt(i, this->size - 1);
        temp = this->tabu[random];
        this->tabu[random] = this->tabu[i];
        this->tabu[i] = temp;
    }

} // end of setRandomMemory()



// This method moves a salmon to the next vertex based on vertex selection
// rules.

void Salmon::move(FlowNetwork* fnet) {
    double r1 = randomDbl();
    double r2 = randomDbl();
    int mem;
    double denominator;
    double numerator;
    double total = 0.0;

    if (r1 < MEMORY) { // if r1 < MEMORY & memory vertex is not in tabu list, move to it
        mem = this->sortedMemory[this->tabu[this->currentPointer]];
        if (!this->scanTabu(mem)) {
            this->currentPointer++;
            tabu[this->currentPointer] = mem;
            return;
        }
    }
    // Otherwise move to next vertex stochastically based on flows
    denominator = this->calcNormalization(fnet);
    for (int i = 0; i < this->size; i++) {
        if (!this->scanTabu(i)) {
            numerator = fnet->getAverageFlow(this->tabu[this->currentPointer], i);
            numerator = pow(numerator, BETA);
            total = total + numerator / denominator;
            if (total + SMALL_NUMBER >= r2) {
                this->currentPointer++;
                this->tabu[this->currentPointer] = i;
                return;
            }
        }
    }
} // end of move()



// This method copies the contents of the source salmon into this salmon.

void Salmon::copy(Salmon* source) {

    for (int i = 0; i < this->size; i++) {
        this->tabu[i] = source->tabu[i];
        this->memory[i] = source->memory[i];
        this->sortedMemory[i] = source->sortedMemory[i];
        this->currentPointer = source->currentPointer;
        this->pathLength = source->pathLength;
    }

} // end of copy()


// This function copies the salmon's path into an array then returns this array

int* Salmon::copyPath() {

    int* pathCopy = new int[this->size];

    for (int i = 0; i < this->size; i++) {
        pathCopy[i] = this->tabu[i];
    }

    return pathCopy;

} // end of copyPath()



// to be removed later

void Salmon::setPath(int* newPath) {

    for (int i = 0; i < this->size; i++) {
        this->tabu[i] = newPath[i];
    }
}
