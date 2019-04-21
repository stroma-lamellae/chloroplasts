#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>

using namespace std;

const int maxChoice = 10;//# of numchoice max
int numchoice = 0;//# of numchoice we count
string names [maxChoice];//numchoice name list
int numVotes [maxChoice] = {0,0,0,0,0,0,0,0,0,0};//vote list 
int tempVotes [maxChoice] = {0,0,0,0,0,0,0,0,0,0};//temp vote list b4 check its validVotes or not
int totalVotes = 0;//totalVotes   vote
int validVotes = 0;//validVotes vote
int spoiledVote = 0;//spoiledVote vote
int allowedVotes = 0;//vote allowed each person
int incCount = 0;//temp vote count up
int isFlag = 0;//check if theres a argument or not
int startVote = 0;//a boolean tells we done with names lets begin with count votes

// This fucntion reads valid votes and counts them
void readValidVotes() {
  for(int i = 0; i < numchoice; i++) {
    numVotes[i]+=tempVotes[i];
    tempVotes[i]=0;
  }
  incCount=0;
  totalVotes++;
  validVotes++;
}
//This function reads votes and counts spoiled votes
void spoiledVoteCount() {
  for(int i=0; i<10; i++) {
    tempVotes[i]=0;
  }
  incCount=0;
  spoiledVote++;
  totalVotes++;
}

//This function checks if votes are valid
void validVoteCheck(string t) {
   int voteVoter=0;
   int incCount=0;
   stringstream stream(t);
   int n;
   while (stream >> n) {
     voteVoter++;
     tempVotes[voteVoter-1]+=n;
     incCount+=n;
   }
  if ((incCount>allowedVotes) || (voteVoter != numchoice))
    spoiledVoteCount();
  else
    readValidVotes();
}
// this function stores names into the name list.
void addchoice(string name) {
  if(numchoice<10) {
    names[numchoice]=name;
    numchoice++;
    if(isFlag==0) allowedVotes++;
  }
}

//function checks if string is name or vote
void checkNameVote(string s) {
   stringstream stream(s);
   int n;
   if(startVote==1)
     validVoteCheck(s);
   else {
     if(stream >> n) {
       validVoteCheck(s);
       startVote=1;
     }
     else
       addchoice(s);
   }
}
//this function reads inputs and calls checkNameVote to decide if it's a name or a vote
void readVotes() {
  int voteVoter=0;
  string s;
  getline(cin,s);
  while(!cin.eof()) {
    checkNameVote(s);
    getline(cin,s);
  }
}
//this function prints all info
void printResults() {
  cout << "# of votes = " << totalVotes << endl;
  cout << "# of valid votes: " << validVotes << endl;
  cout << "# of spoiled votes: " << spoiledVote << endl << endl;
  cout << left << setw(15) << "numchoice" << right << setw(3) << "Score" << endl << endl;
  for(int i=0; i<numchoice; i++) {
    cout << left << setw(15) << names[i] << right << setw(3) << numVotes[i] << endl;
  }
}

int main(int argc, char *argv[]) {
  int result = 1;
  if(argc == 2) {
    stringstream maArg(argv[1]);
    maArg >> allowedVotes;
    isFlag = 1;
  }
  readVotes();
  printResults();
  return result;
}