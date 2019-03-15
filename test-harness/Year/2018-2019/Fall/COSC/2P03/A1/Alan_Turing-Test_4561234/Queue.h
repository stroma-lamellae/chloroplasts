//This uses a generic typename, but also an expression parameter

/**
    * @author  Alan Turing-Test
    * @studentNum 4561234
    */

template <typename T, int capacity>
class Queue {
private:
T arr[capacity]; //Always the desired size!
int topIdx;
int endIdx;
public:
Queue() : topIdx(0), endIdx(0) {}
void enter(const T item) {
arr[endIdx++%capacity]=item;
}
T leave() {
return arr[topIdx++%capacity];
}
T top() {
return arr[topIdx%capacity];
}
bool isEmpty() {
return topIdx<=0;
}
};
