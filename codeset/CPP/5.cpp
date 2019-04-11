/*
 * Project: Ragnorok tbRpg
 * Medium: Source Code, C++
 * Version:  0.6.7a (working, non-stable) [bounds checking still not working 100%] Needs to be cleaned Up.
 * Usage: See main function
 * License:
    <Programmed by Admin, this work is for an on going project called Ragnorok tbRpg>
    Copyright (C) <2010>  <Admin>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
//TODO: Add more error checking, stop out of bounds with vector! Add remove entity!
//TODO: Do something for inventory! Clean code, replace shitty code with better code!
//USAGE: file_write, the first arguemnt is the entity name, second is what to change, if third arguemnt is n it doesnt overwrite anything but
//USAGE: one that you specify on arugment 2. If it is y it will overwrite everything. always load, find, write, then clear. and new entity is the
//USAGE: same as the write, expect it appends to the file, and the two options are void in this one.

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

template <class T>
std::string int2str(T x) {
    std::stringstream buffer;
    std::string s;
    buffer << x;
    s = buffer.str();
    return s;
}
//usage:

class file_io {
public:

    bool has_ran;
    bool has_ran_write;
    char * File_name;
    std::vector<std::string> values;
    file_io(const char[]);
    ~file_io();
    inline bool file_load();
    inline std::string file_find(const char[], const std::string, const char, const unsigned int inventory = 0);
    inline bool file_write(const char * name = "default", char option = 'a', char option_n = 'n', const short location = 0, const short health = 100,
            const short defense = 5, const short attack = 5, const short karma = 3,
            const long gold = 0, const bool alive = true);

    bool file_new_entity(const char * name = "default", const short location = 0, const short health = 100,
            const short defense = 5, const short attack = 5, const short karma = 3,
            const long gold = 0, const bool alive = true);

private:
    std::vector <std::string> file_info;
};

file_io::file_io(const char file_name[]) {
    File_name = (char*) file_name;
    has_ran = false;
    has_ran_write = false;
}

file_io::~file_io() {

}

int main() {

    file_io *File = new file_io("test.txt"); //filename into buffers and create usable object
    //load file into buffers
    //File->file_write("golbin", 'n', 999);

    File->file_load();
    File->file_find("hobbit", "", '0');
    File->file_write("hobbit", '!', 'y', 555, 555, 555, 555, 555, 555);

    File->file_load();
    std::cout << "HERE " << File->values.at(6);


    delete File; //destructs the object
    return 0;

}

inline std::string file_io::file_find(const char find[], const std::string entity, const char option, const unsigned int inventory) {
    if (has_ran) {
        values.clear();
        switch (file_info.size()) {
            case 0:
                std::cerr << "vector did not get filled propely" << std::endl;
                break;
            default:
                unsigned int i;
                //unsigned int x = 0;
                std::string temp;
                std::string tmp;
                unsigned position[3]; //line is 0, pos is 1
                for (i = 0; i < file_info.size(); ++i) {
                    if (file_info.at(i).find(find) < 999) {
                        position[0] = file_info.at(i).find(find); //the number @ it starts
                        position[1] = i; //the line number
                        temp = file_info.at(i).c_str();
                        std::cout << temp << std::endl;

                    }
                }

                std::istringstream bufferss(temp);
                i = 0;
                while (getline(bufferss, tmp, ':')) {
                    values.push_back(tmp);
                    std::cout << values.at(i) << std::endl;
                    ++i;
                }
                break;
        }; //(const char * name, short location = 0, short health = 100, short defense = 7, short attack = 10, short karma = 3, long gold = 200, bool alive = true)
        switch (option) {
            case 'n':
                    return values.at(0);
                break;
            case 'l':
                if (values.size() >= 1) {
                    return values.at(1);
                } else return "error, oob";
                break;
            case 'h':
                if (values.size() >= 2) {
                    return values.at(2);
                } else return "error, oob";
                break;
            case 'd':
                if (values.size() >= 3) {
                    return values.at(3);
                } else return "error, oob";
                break;
            case 'a':
                if (values.size() >= 4) {
                    return values.at(4);
                } else return "error, oob";
                break;
            case 'k':
                if (values.size() >= 5) {
                    return values.at(5);
                } else return "error, oob";
                break;
            case 'g':
                if (values.size() >= 6) {
                    return values.at(6);
                } else return "error, oob";
                break;
            case 'i':
                if (values.size() >= inventory) {
                    return values.at(inventory);
                } else return "error, oob";
                break;
            default:
                return "";
                break;
        };
    } else return "error, run file_load first!";
}

inline bool file_io::file_load() {
    const char * file_name = File_name;
    short line = 0;
    if (has_ran) {
        file_info.clear();
    }
    std::string local_buffer;
    std::ifstream file_in(file_name, std::ios::in | std::ios::binary);

    if (file_in.is_open()) {
        while (getline(file_in, local_buffer)) {
            file_info.push_back(local_buffer);
            std::cout << file_info.at(line) << std::endl;
            ++line;
        }
        has_ran = true;
        return true;
    } else {
        std::cerr << "file_io error, could not open" << std::endl;
        has_ran = true;
        return false;
    }
}

inline bool file_io::file_write(const char * name, char option, char option_n, const short location, const short health,
        const short defense, const short attack, const short karma,
        const long gold, const bool alive) {

    std::cout << "size of vector " << file_info.size() << std::endl;


    char * file_name = File_name;
    std::ofstream file_out;
    short line = -1, i = 0;
    std::string data;

    if ((has_ran == true) && (file_info.size() > 0)) {

        while (i < file_info.size()) {
            if (file_info.at(i).find(name) < 999) {
                line = i;
                break;
            }
            ++i;
        }

        if (line != -1) {

            std::string stats[8] = {name, int2str(location), int2str(health), int2str(defense), int2str(attack), int2str(karma), int2str(gold), int2str(alive)};
            file_info.at(line) = "";

            if (option_n == 'n') {
                for (i = 0; i < 8; ++i) {
                    stats[i] = values.at(i);
                    if (option == 'l') {
                        stats[1] = int2str(location);
                    } else if (option == 'h') {
                        stats[2] = int2str(location);
                    } else if (option == 'd') {
                        stats[3] = int2str(location);
                    } else if (option == 'a') {
                        stats[4] = int2str(location);
                    } else if (option == 'k') {
                        stats[5] = int2str(location);
                    } else if (option == 'g') {
                        stats[6] = int2str(location);
                    } else if (option == 'A') {
                        stats[7] = int2str(location);
                    }
                    file_info.at(line) += stats[i] + ":";
                    std::cout << "values " << stats[i] << std::endl;
                }
            }
            if (option_n == 'y') {
                for (i = 0; i < 8; ++i) {
                    file_info.at(line) += stats[i] + ":";
                }
            }



            std::cout << "file_info.at(" << line << ") " << file_info.at(line) << std::endl;
            file_out.open(file_name, std::ios::out | std::ios::trunc);

            i = 0;
            while (file_info.size() > i) {
                std::cout << "there" << std::endl;
                file_out << file_info.at(i) << std::endl;
                ++i;
            }

            return true;
        } else return false;
    }
}

bool file_io::file_new_entity(const char * name, const short location, const short health,
        const short defense, const short attack, const short karma,
        const long gold, const bool alive) {
    std::string stats[8] = {name, int2str(location), int2str(health), int2str(defense), int2str(attack), int2str(karma), int2str(gold), int2str(alive)};
    std::ofstream file_out;
    const char * file_name = File_name;
    int i;
    file_info.at(0) = "";
    for (i = 0; i < 8; ++i) {
        file_info.at(0) += stats[i] + ":";
    }
    file_out.open(file_name, std::ios::out | std::ios::app);
    if (file_out.is_open()) {
        file_out << file_info.at(0);
        return true;
    } else return false;
}


