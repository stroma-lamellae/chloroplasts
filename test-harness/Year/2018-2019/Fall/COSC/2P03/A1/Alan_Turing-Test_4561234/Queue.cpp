#include <iostream>
#include <string>
#include "Queue.h"

/**
    * @author  Alan Turing-Test
    * @studentNum 4561234
    */

int main() {
Queue<int,20> iq;
iq.enter(32);iq.enter(20);iq.enter(40);
std::cout<<iq.leave()<<"\t"<<iq.leave()<<std::endl;
Queue<std::string,50> sq;
sq.enter("hello");sq.enter("class!");sq.enter("templates are neat!");
while (!sq.isEmpty())
std::cout<<sq.leave();
std::cout<<std::endl;
}
