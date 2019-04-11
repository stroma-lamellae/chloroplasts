public class IntListMethods {
    public static String getAuthorName() {
        return "Yap, Calvin"; // This is my name
    }

    public static String getRyersonID() {
        return "500825267"; // This is my Student id
    }

    public static int removeIfDivisible(int n, int k) {
        int temp = 0; // to keep for switching
        int first = n; // keep reference to first element
        int counter = 0; // counter to see when first element is removed or not
        if(n == 0){
            return  0; // list empty
        }
        while (IntList.getNext(n) != 0) {
            if(IntList.getKey(n) % k != 0){
                counter++;
            }
            if (counter < 1 && IntList.getKey(n) % k == 0) {
                temp = IntList.setNext(n, 0);
                IntList.release(n);
                n = temp;
                first = n;
            } else if (counter >= 1 && IntList.getNext(n) != 0) {
                int temp1 = IntList.getNext(n);
                if (IntList.getKey(temp1) % k == 0) {
                    IntList.setNext(n, IntList.setNext(temp1, 0));
                    IntList.release(temp1);
                    temp1 = IntList.getNext(n);
                } else {
                    n = temp1;
                    temp1 = IntList.getNext(temp1);
                }
            }
        }
        return first;
    }
    static int[] arrNodes;
    public static int sort(int n) {
        if(n == 0 || IntList.getNext(n) == 0){
            return n;
        }
       int arrKeys[]= new int [IntList.getAllocatedNodeCount()]; // new array to hold keys
        arrNodes = new int[IntList.getAllocatedNodeCount()]; // new array to hold nodes
       for(int x = 0; x < arrNodes.length;x++) { // for loop to fill contents
        arrKeys[x] = IntList.getKey(n);
        arrNodes[x] = n;
        n = IntList.getNext(n);
       }
        buildHeap(arrKeys);// implement the sort
       int count = 0;
       for(int i = 0; i < arrNodes.length-1; i++){
           IntList.setNext(arrNodes[i], arrNodes[i+1]);
           count++;
       }
       IntList.setNext(arrNodes[count], 0); // building chain
        return arrNodes[0]; // returning first element of the chain
    }

    public static void buildHeap(int keys[])
    {
        int GetfloorDiv =2;
        int heapSize = keys.length;
        // Build heap (rearrange array)
        for (int i = heapSize / GetfloorDiv - 1; i >= 0; i--) // set floor down to 1
            heapify(keys, heapSize, i); // heapify

        int i=heapSize-1;
        while (i>=0) // extracting elements
        {
            int grabber = keys[0]; //
            keys[0] = keys[i]; // swapping current node
            keys[i] = grabber;  // to end

            int grabberNodes = arrNodes[0]; // moving array for noedes
            arrNodes[0] = arrNodes[i]; // swapping for current node
            arrNodes[i] = grabberNodes; // to end

            heapify(keys, i, 0); // removing elements in heap to make it smaller
            i--;
        }
    }
    public static void heapify(int keys[], int length, int index) {   // don't have to subtract 1 because of previously did in for loop
        int LgRoot = index;  // largest element
        int left = 2 * index + 1; // left
        int right =left + 1 ; //right

        if (left < length && keys[left] > keys[LgRoot]) { //left Child is larger than largest
            LgRoot = left;
        }
        if (right < length && keys[right] > keys[LgRoot]){ // right Child is larger than largest
            LgRoot = right;
        }
        if (LgRoot != index) // not equal
        {
            int swappingLg = keys[index]; // shift elements
            keys[index] = keys[LgRoot];
            keys[LgRoot] = swappingLg;

            int swapNode = arrNodes[index]; // shifts nodes
            arrNodes[index] = arrNodes[LgRoot];
            arrNodes[LgRoot] = swapNode;

            heapify(keys, length, LgRoot);
        }
    }
}