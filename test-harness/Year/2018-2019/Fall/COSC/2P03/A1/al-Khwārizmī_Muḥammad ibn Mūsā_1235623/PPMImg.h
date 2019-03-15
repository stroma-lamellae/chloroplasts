#include<iostream>
#include<fstream>
#include<string>

struct channel {
 unsigned short c;
};

class PPMImg {
private:
	std::ifstream& infile;
	int width, height, capacity, chval;
	std::string magic_number;
	unsigned int storage;
	channel *data;

public:
	PPMImg(std::ifstream&);
	~PPMImg();
	std::string  getMagic() const;
	int getWidth() const;
	int getHeight() const;
	int getCh() const;
	int getCapacity() const;
	void scrub() const;
	void secret() const;
	void store(std::ifstream &intext);
	int getStorage() const;
	channel getChannel(int i) const;
};

