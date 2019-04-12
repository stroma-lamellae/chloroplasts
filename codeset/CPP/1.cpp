#include "assign1.hpp"
using namespace std;
//
// Creating a new PPM
//void store(fstream& fin){
//    int channel;
//    int height,width,maxVal;
//    string magicnumero;
//    fin >> magicnumero >> width >> height >> maxVal;
//    bap << magicnumero << "\n" << width << " " << height << "\n" << maxVal
//    << "\n";
//    if (val == 0 || val > capacity){
//      cout << "File invalid, or is too large, or nothing is stored." << endl;
//      return;
//    }
//    cout << "Stored: "<< val << endl;
//    string file = yoinkOut();
//    bap.open(file, ios::out);
//
// Files must be exchanged to write into the input instead;
//    while (!fin.eof()){
//        outByte = getByte(fin);
//        bap << outByte;
//    }
//
//    while (!fin.eof()){
//        for(int i = 0; i<21; i++){
//            fin>>channel;
//            channel = channel >>1;
//            channel = channel <<1;
//            bap<<channel<<" ";
//        }
//        bap<<"\n";
//    }
//    fin.close();
//    bap.close();
//}


// Returns width/height/capacity/possible storage
void inspect(fstream& fin) {
    unsigned int val;
    string magicNum;
    int width, height, capacity;
    // outputting values
    fin >> magicNum >> width >> height;
    // Check if it's a PPM
    if(magicNum == "P3"){
        capacity = getCapacity(height, width);
        cout << "Width: " << width << "\nHeight: " << height << "\nCapacity:"
        << capacity << "\n";
    } else {
        cout << "Invalid Magic Number\n";
    }
    // check if there is something stored
    val = checkStored(fin, capacity);
    if (val == 0 || val > capacity){
      cout << "Stored: None\n";
    } else {
      cout << "Stored: " << val << "\n";
    }
}
// function to calculate capacity
int getCapacity (int width, int height) {
  int val;
  val = ((width*height*3)/8) - 4;
  return val;
}

// function to check possible storage
int checkStored(std::fstream& fin, int capacity) {
  unsigned int val, ugh;
  for(int i = 0; i < 32; i++) {
      fin >> ugh;
      if(ugh % 2 == 0) {
          val = val|0;
      } else {
          val = val | 1;
      }
      val = val << 1;
  }
  return val;
}

//this doesn't work
void getLength(string file) {
	int length;
	char *buffer;
	fstream fin(file, ios::binary);
	fin.seekg(0, ios::end);
	length = fin.tellg();
	cout<<length;
}

// retrieve last bit from each byte
// also i'm sorry that this is super ugly, i had to match the assignment output
// last minute. :<
void retrieve(fstream& fin) {
  int pHolder, channel, height, width, capacity, val;
  char outByte;
  string magicNum;
  ofstream bap;
  fin >> magicNum >> width >> height;
  capacity = getCapacity(width, height);
  val = checkStored(fin, capacity);
  if (val == 0 || val > capacity){
    cout << "File invalid, or is too large, or nothing is stored." << endl;
    return;
  }
  //move file to where channels start
  fin >> pHolder;
  cout << "Stored: "<< val << endl;
  string file = yoinkOut();
  bap.open(file, ios::out);
  while (!fin.eof()){
    outByte = getByte(fin);
    bap << outByte;
  }
  fin.close();
  bap.close();
}

// Retrieves the hidden file byte by byte
char getByte(fstream& fin) {
	int pHolder;
	unsigned int val;
  int channel;
	val = 0;
	for(int i = 0; i < 8; i++){
      val = val << 1;
      fin >> channel;
      if (channel % 2 == 1) {
          val = val | 1;
      } else {
        val = val |0;
      }
    }
    return val;
}

// Prompts for input file name
void yoinkInOut(string &first, string &out) {
  cout << "Image filename: ";
  cin >> first;
}

// Prompts for output file name
string yoinkOut() {
  string out;
  cout << "Image output name: ";
  cin >> out;
  return out;
}

//Grabs the correct values.
void scrub(fstream& fin, ofstream& bap) {
  int channel;
  int height,width,maxVal;
  string magicnumero;
  fin >> magicnumero >> width >> height >> maxVal;
  bap << magicnumero << "\n" << width << " " << height << "\n" << maxVal
  << "\n";
  while (!fin.eof()){
    for(int i = 0; i<21; i++){
      fin>>channel;
      channel = channel >> 1;
      channel = channel << 1;
      bap<<channel<<" ";
    }
    bap<<"\n";
  }
  bap.close();
}

// Prints the menu
void printMenu() {
  cout<<"Menu:\n-----\n";
  cout<<"1. Store Data into Image\n";
  cout<<"2. Retrieve Data from Image\n";
  cout<<"3. Inspect Image\n";
  cout<<"4. Scrub Image\n";
  cout<<"0. Quit\n";
}

//Where the magic happens
int main(int argc, char** argv) {
    string firstFile, outFile;
    int choice = -1;
    fstream fin;
    ofstream bap;
    //non-interactive mode
    if(argc == 2){
      fin.open(argv[1], ios::in);
      inspect(fin);
      fin.close();
      return 0;
    }
    // Interactive Mode (I'm sorry my switch cases are so ugly)
    while(choice) {
      printMenu();
      cin >> choice;
      switch(choice) {
          case 1: //this doesn't work I'm so sorry
            cout << "Input file image name: \n";
            cin >> firstFile;
            //fin.open(firstFile, ios::in);
            //cout << "Image output name: ";
            //cin >> outFile;
            //storage(firstFile);
            break;
          case 2: //Retrieve
            yoinkInOut(firstFile, outFile);
            fin.open(firstFile, ios::in);
            retrieve(fin);
            break;
          case 3: //inspect
            cout << "Image filename: ";
            cin >> firstFile;
            fin.open(firstFile, ios::in);
            inspect(fin);
            fin.close();
            break;
          case 4://Scrub
            cout << "Image filename: ";
            cin >> firstFile;
            fin.open(firstFile, ios::in);
            cout << "Image output name: ";
            cin >> outFile;
            bap.open(outFile, ios::out);
            scrub(fin, bap);
            break;
          case 0:
            exit(0);
          default:
            cout<<"Don't do that." << endl;
            break;
      }
    }
}
