public class IntListMethods {
    public static String getName() {
        return "John Smith";
    }

    public static String getBrockID() {
        return "4862154";
    }

    public static int removeIfDivisible(int n, int k) {
        int temp = 0;
        int first = n;
        int counter = 0;
        if (n == 0) {
            return 0;
        }
        while (IntList.getNext(n) != 0) {
            if (IntList.getKey(n) % k != 0) {
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

    public static int sort(int n) {
        if (n == 0 || IntList.getNext(n) == 0) {
            return n;
        }
        int keys[] = new int[IntList.getAllocatedNodeCount()];
        int[] nodes = new int[IntList.getAllocatedNodeCount()];
        for (int x = 0; x < nodes.length; x++) {
            keys[x] = IntList.getKey(n);
            nodes[x] = n;
            n = IntList.getNext(n);
        }
        createHeap(keys, nodes);
        int count = 0;
        for (int i = 0; i < nodes.length - 1; i++) {
            IntList.setNext(nodes[i], nodes[i + 1]);
            count++;
        }
        IntList.setNext(nodes[count], 0);
        return nodes[0];
    }

    public static void createHeap(int keys[], int[] nodes) {
        for (int i = keys.length / 2 - 1; i >= 0; i--)
            heapify(keys, keys.length, i, nodes);

        int i = keys.length - 1;
        while (i >= 0) {
            int grabber = keys[0];
            keys[0] = keys[i];
            keys[i] = grabber;

            int grabberNodes = nodes[0];
            nodes[0] = nodes[i];
            nodes[i] = grabberNodes;

            heapify(keys, i, 0, nodes);
            i--;
        }
    }

    public static void heapify(int keys[], int len, int idx, int[] nodes) {
        int root = idx;
        int l = 2 * idx + 1;
        int r = l + 1;

        if (l < len && keys[l] > keys[root]) {
            root = l;
        }
        if (r < len && keys[r] > keys[root]) {
            root = r;
        }
        if (root != idx) {
            int swappingLg = keys[idx];
            keys[idx] = keys[root];
            keys[root] = swappingLg;

            int swapNode = nodes[idx];
            nodes[idx] = nodes[root];
            nodes[root] = swapNode;

            heapify(keys, len, root, nodes);
        }
    }
}