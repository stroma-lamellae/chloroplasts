#include <iostream>
#include<fstream>
#include<string>
#include "PPMImg.h"
using namespace std;

/**
     @author al-Khwārizmī Muḥammad ibn Mūsā
     @studentNum  1235623
    */


//PPM class
PPMImg::PPMImg(std::ifstream& infile)
	:infile(infile)
{
	this->magic_number="P3";
	int w,h,c;
	infile>>w>>h>>c;
	this->width = w;
	this->height = h;
	this->chval = c;
	this->capacity =w*h*3/8-4;
	data = new channel[width*height*3];	//stores image channels
	for(int i=0; i<width*height*3; i++){
		infile>>data[i].c;
	}
	unsigned int bits = 0;		//unsigned char holds hidden file size if exists
    for (int i=0; i<32; i++){
            bits = bits<<1;
            bits |=  (data[i].c&0x1);
    }
	this->storage = bits;
}

PPMImg::~PPMImg(){		//destructor
	delete[] data;
}

std::string PPMImg::getMagic() const{
	return magic_number;
}

int PPMImg::getWidth() const{
	return width;
}

int PPMImg::getHeight() const{
	return height;
}

int PPMImg::getCapacity() const{
	return capacity;
}

int PPMImg::getCh() const{
	return chval;
}

void PPMImg::scrub() const{		//sets the last bit in each channel to 0
	for(int i=0; i<width*height*3; i++){
		data[i].c = data[i].c&254;
	}
	std::cout<<"Scrubbed."<<std::endl;

}

void PPMImg::secret() const {	//outputs secret data to a file
	ofstream outfile;
	string outfname;
    std::cout<<"Output image filename:"<<std::endl;
    cin>>outfname;
    outfile.open(outfname.c_str());
	unsigned char sec = 0;
	for (int i=32; i<=(storage*8)+32; i++){
			if(i>32&&i%8==0){	//when sec has 1 byte of data, it is written to user defined file
             	outfile<<sec;
 	            sec = 0;
			}
			sec = sec<<1;
			sec |= (data[i].c&0x1); //copies last bit in each channel to sec
		}
}

void PPMImg::store(ifstream &intext) {
 	    intext.seekg (0, intext.end);
	    unsigned int length = intext.tellg();	//length of file to store
	    intext.seekg(0, intext.beg);
        std::cout<<length<<" bytes to store"<<std::endl;
		int count = 0;
		for (int i=31; i>=0; i--){
				if(((length>>i)&1) == 1){	//if bit from file is set to 1, last bit in channel is set to 1
					data[count].c |= 1;	//stores unsigned char containing size of hidden data
				}
			count++;
		}

		char c;
		while (intext.get(c)){
    		for (int i = 7; i >= 0; i--){
				if(((c>>i)&1) == 1){	//sets bytes to 1 where required, writes out bytes to file
					data[count].c |=1;
				}
				count++;
			}
		}
}

int PPMImg::getStorage() const{
	int s =((storage>capacity | storage ==0)?0:storage);
	return s;
}

channel PPMImg::getChannel(int i) const{
	return data[i];
}


